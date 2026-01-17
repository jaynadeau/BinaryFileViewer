//
// Created by jnadeau on 11/30/2023.
//

#ifndef BINARYFILEVIEWER_PARSEERROR_H
#define BINARYFILEVIEWER_PARSEERROR_H

#include "ErrorBase.h"

#include <iostream>
#include <string>
#include <unordered_map>

namespace returns {

    class ParseError : public ErrorBase
    {

    public:
        enum class TYPE : int
        {
            INCOMPATIBLE_TYPE,
            RANGE_ERROR,
            MISSING_REQD_ARG,
            MISSING_VALUE,
            UNEXPECTED_TYPE,
            UNKNOWN_ARGUMENT,
            UNSUPPORTED_ARGUMENT,
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
        static const inline ErrorDescription ERROR_DESCRIPTION{{TYPE::INCOMPATIBLE_TYPE,    "Could not convert argument to the specified type"},
                                                               {TYPE::RANGE_ERROR,          "The value of the argument cannot be represented by the specified type"},
                                                               {TYPE::MISSING_REQD_ARG,     "Missing required argument"},
                                                               {TYPE::MISSING_VALUE,        "Argument has no value"},
                                                               {TYPE::UNEXPECTED_TYPE,      "The Argument does not have the expected argument type"},
                                                               {TYPE::UNKNOWN_ARGUMENT,     "The Argument does not match the expected arguments"},
                                                               {TYPE::UNSUPPORTED_ARGUMENT, "Positional arguments are not supported"},
        };
    };

    static const inline ParseError INCOMPATIBLE_TYPE{ParseError::TYPE::INCOMPATIBLE_TYPE};
    static const inline ParseError RANGE_ERROR{ParseError::TYPE::RANGE_ERROR};
    static const inline ParseError MISSING_REQUIRED_ARGUMENT{ParseError::TYPE::MISSING_REQD_ARG};
    static const inline ParseError HAS_NO_VALUE{ParseError::TYPE::MISSING_VALUE};
    static const inline ParseError UNEXPECTED_TYPE{ParseError::TYPE::UNEXPECTED_TYPE};
    static const inline ParseError UNKNOWN_ARGUMENT{ParseError::TYPE::UNKNOWN_ARGUMENT};
    static const inline ParseError UNSUPPORTED_ARGUMENT{ParseError::TYPE::UNSUPPORTED_ARGUMENT};

}

#endif //BINARYFILEVIEWER_PARSEERROR_H
