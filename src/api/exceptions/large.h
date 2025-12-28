#pragma once

#include <stdexcept>

namespace weserv::api::exceptions {

/**
 * Exception when a provided image is too large for processing.
 */
class TooLargeImageException : public std::runtime_error {
 public:
    using std::runtime_error::runtime_error;
};

}  // namespace weserv::api::exceptions
