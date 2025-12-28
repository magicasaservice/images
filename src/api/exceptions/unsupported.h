#pragma once

#include <stdexcept>

namespace weserv::api::exceptions {

/**
 * Exception when a provided saver is not supported.
 */
class UnsupportedSaverException : public std::runtime_error {
 public:
    using std::runtime_error::runtime_error;
};

}  // namespace weserv::api::exceptions
