//
// Created by jnadeau on 10/4/2022.
//

#ifndef APPLICATION_APPLICATION_ERROR_H
#define APPLICATION_APPLICATION_ERROR_H

#include "../Returns/ErrorBase.h"

#include <string>
#include <unordered_map>

namespace returns {

    class ApplicationError : public ErrorBase
    {
    public:
        enum class TYPE
        {
            APPLICATION_EXISTS,
            APPLICATION_UNINITIALIZED,
            APPLICATION_NOT_FOUND,
        };

        ApplicationError() = default;
        explicit ApplicationError(TYPE errorType);
        ApplicationError(TYPE errorType, std::string_view applicationName);
        ApplicationError(const ApplicationError& other) = default;
        ApplicationError(ApplicationError&& other) = default;
        ~ApplicationError() override = default;

        ApplicationError& operator=(const ApplicationError& rhs) = default;
        ApplicationError& operator=(ApplicationError&& rhs) = default;

    protected:
        using ErrorDescription = std::unordered_map<TYPE, std::string>;
        static const inline ErrorDescription ERROR_DESCRIPTION{{TYPE::APPLICATION_EXISTS,        "Application already exists"},
                                                               {TYPE::APPLICATION_UNINITIALIZED, "Application uninitialized or is nullptr"},
                                                               {TYPE::APPLICATION_NOT_FOUND,     "Application is not found or does not exist"},
        };
    };

    static const inline ApplicationError APPLICATION_EXISTS{ApplicationError::TYPE::APPLICATION_EXISTS};

}

#endif //APPLICATION_APPLICATION_ERROR_H
