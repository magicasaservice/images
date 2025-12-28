#pragma once

#include <stdexcept>

namespace weserv::api::exceptions {

/**
 * Exception when a provided image is not valid.
 */
class InvalidImageException : public std::runtime_error {
 public:
    using std::runtime_error::runtime_error;
};

}  // namespace weserv::api::exceptions
