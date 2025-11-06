//
// Created by jnadeau on 11/30/2023.
//

#ifndef BINARYFILEVIEWER_PARSEERROR_H
#define BINARYFILEVIEWER_PARSEERROR_H

#include "ErrorBase.h"

#include <iostream>
#include <string>
#include <unordered_map>

namespace bfv::returns {

    class ParseError : public ErrorBase
    {

    public:
        enum class TYPE : int
        {
            INCOMPATIBLE_TYPE,
            RANGE_ERROR,
            MISSING_REQD_ARG,
        };

        ParseError() = default;
        explicit ParseError(TYPE errorType);
        ParseError(TYPE errorType, const std::string& argumentName);
        ParseError(const ParseError& other) = default;
        ParseError(ParseError&& other) = default;
        ~ParseError() override = default;

        ParseError& operator=(const ParseError& rhs) = default;
        ParseError& operator=(ParseError&& rhs) = default;

    protected:
        using ErrorDescription = std::unordered_map<TYPE, std::string>;
        static const inline ErrorDescription ERROR_DESCRIPTION{{TYPE::INCOMPATIBLE_TYPE, "Could not convert argument to the specified type"},
                                                               {TYPE::RANGE_ERROR,       "The value of the argument cannot be represented by the specified type"},
                                                               {TYPE::MISSING_REQD_ARG,  "Missing required argument"}};
    };

    static const inline ParseError INCOMPATIBLE_TYPE{ParseError::TYPE::INCOMPATIBLE_TYPE};
    static const inline ParseError RANGE_ERROR{ParseError::TYPE::RANGE_ERROR};
    static const inline ParseError MISSING_REQUIRED_ARGUMENT{ParseError::TYPE::MISSING_REQD_ARG};

}   // namespace bfv::utils::returns

#endif //BINARYFILEVIEWER_PARSEERROR_H
