//
// Created by jnadeau on 10/4/2022.
//

#include "ErrorBase.h"

#include <sstream>
#include <utility>

namespace bfv::returns {

    ErrorBase::ErrorBase(const int errorNumber)
    : mErrorNumber{errorNumber}
    , mErrorMessage{}
    {}

    ErrorBase::ErrorBase(const int errorNumber, std::string errorMessage)
        : mErrorNumber{errorNumber}
        , mErrorMessage{std::move(errorMessage)}
    {}

    std::string ErrorBase::getErrorAsString() const {
        std::stringstream ss;
        ss << "Error number: " << mErrorNumber << " Error message: " << mErrorMessage;
        return ss.str();
    }

    std::string ErrorBase::getErrorMessage() const {
        return mErrorMessage;
    }

    int ErrorBase::getErrorNumber() const {
        return mErrorNumber;
    }

}   // namespace bfv::utils::returns
