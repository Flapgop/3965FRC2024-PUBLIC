#pragma once

#include <iostream>

namespace Error {
    enum ErrorCode {
        NO_ERROR = 0,
        UNSUPPORTED_OPERATION
    };

    std::string ErrorString(ErrorCode code) {
        switch (code) {
        case NO_ERROR:
            return "No error.";
            break;
        case UNSUPPORTED_OPERATION:
            return "Unsupported Operation.";
            break;

        default:
            break;
        }
    }
}