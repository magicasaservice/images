#include "trim.h"

#include "../utils/utility.h"

namespace weserv::api::processors {

using parsers::Color;

VImage Trim::process(const VImage &image) const {
    auto threshold = query_->get_if<int>(
        "trim",
        [](int t) {
            // Threshold must be in [1, 254], or -1 to use the default
            return t == -1 || (t >= 1 && t <= 254);
        },
        0);

    // Make sure that trimming is required
    if (threshold == 0 || image.width() < 3 || image.height() < 3) {
        // We could use shrink-on-load for the next thumbnail processor
        query_->update("trim", false);

        return image;
    }

    // Use default threshold of 10 if none is given
    if (threshold == -1) {
        threshold = 10;
    }

    std::vector<double> trim_background;
    if (query_->exists("tbg")) {
        trim_background = query_->get<Color>("tbg").to_rgba();

        if (utils::is_16_bit(image.interpretation())) {
            for (auto &i : trim_background) {
                i *= 256.0;
            }
        }

        if (image.bands() < 3) {
            // Convert sRGB to greyscale
            trim_background = {0.2126 * trim_background[0] +
                               0.7152 * trim_background[1] +
                               0.0722 * trim_background[2]};
        } else {
            auto bands = image.has_alpha() ? image.bands() - 1 : image.bands();
            trim_background.resize(bands, trim_background[3]);
        }
    } else {
        // Top-left pixel provides the default background color if none is given
        auto background = image.extract_area(0, 0, 1, 1);

        // Note: If the image has alpha, we'll need to flatten before `getpoint`
        // to get a correct background value
        if (image.has_alpha()) {
            background = background.flatten();
        }

        trim_background = background(0, 0);
    }

    // Scale up 8-bit values to match 16-bit input image
    if (utils::is_16_bit(image.interpretation())) {
        threshold = threshold * 256;
    }

    int left, top, width, height;
    left = image.find_trim(&top, &width, &height,
                           VImage::option()
                               ->set("threshold", threshold)
                               ->set("background", trim_background));

    // Sanity check, this usually happens when a high tolerance is specified
    if (width == 0 || height == 0) {
        // We could use shrink-on-load for the next thumbnail processor
        query_->update("trim", false);

        // Just return the original image
        return image;
    }

    // Skip shrink-on-load for the next thumbnail processor
    query_->update("trim", true);

    // Don't trim the height in toilet-roll mode
    if (query_->get<int>("n") > 1) {
        top = 0;
        height = image.height();
    }

    // And crop the original image
    return image.extract_area(left, top, width, height);
}

}  // namespace weserv::api::processors
