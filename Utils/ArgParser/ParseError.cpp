//
// Created by jnadeau on 11/30/2023.
//

#include "ParseError.h"

namespace returns {

    ParseError::ParseError(TYPE errorType)
    : ErrorBase{static_cast<int>(errorType), ERROR_DESCRIPTION.at(errorType)}
    {
    }

    ParseError::ParseError(TYPE errorType, const std::string& argumentName)
    : ErrorBase{static_cast<int>(errorType), ERROR_DESCRIPTION.at(errorType) + " (" + argumentName + ")"}
    {
    }
}
