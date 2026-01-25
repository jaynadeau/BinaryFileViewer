//
// Created by jnadeau on 10/4/2022.
//

#ifndef RETURNS_IERROR_H
#define RETURNS_IERROR_H

#include <iostream>
#include <string>

namespace returns {

    class IError
    {
    public:
        virtual ~IError() = default;

        [[nodiscard]] virtual std::string getErrorAsString() const = 0;
        [[nodiscard]] virtual std::string getErrorMessage() const = 0;
        [[nodiscard]] virtual int getErrorNumber() const = 0;
    };

}

#endif //RETURNS_IERROR_H
