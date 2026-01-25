//
// Created by jnadeau on 10/4/2022.
//

#include "ApplicationError.h"

#include <utility>

namespace returns {

    ApplicationError::ApplicationError(TYPE errorType)
    : ErrorBase{static_cast<int>(errorType), ERROR_DESCRIPTION.at(errorType)}
    {
    }

    ApplicationError::ApplicationError(TYPE errorType, std::string_view applicationName)
    : ErrorBase{static_cast<int>(errorType), ERROR_DESCRIPTION.at(errorType) + " (" + std::string{applicationName} + ")"}
    {
    }

}
