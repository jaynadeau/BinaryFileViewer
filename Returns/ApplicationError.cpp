//
// Created by jnadeau on 10/4/2022.
//

#include "ApplicationError.h"

#include <utility>

namespace bfv::returns {

    ApplicationError::ApplicationError(int errorNumber, std::string errorMessage)
    {
        mErrorNumber = errorNumber;
        mErrorMessage = std::move(errorMessage);
    }

}   // bfv::utils::returns
