//
// Created by jnadeau on 10/4/2022.
//

#ifndef BINARYFILEVIEWER_ERRORBASE_H
#define BINARYFILEVIEWER_ERRORBASE_H

#include "IError.h"

#include <iostream>

namespace qti::aisw::bfv::returns {

    class ErrorBase : public IError
    {
    public:
        ErrorBase() = default;
        explicit ErrorBase(int errorNumber);
        ErrorBase(int errorNumber, std::string errorMessage);
        ErrorBase(const ErrorBase& other) = default;
        ~ErrorBase() override {std::cout << "~ErrorBase\n";};

        [[nodiscard]] std::string getErrorAsString() const override;
        [[nodiscard]] std::string getErrorMessage() const override;
        [[nodiscard]] int getErrorNumber() const override;
    protected:
        int mErrorNumber{0};
        std::string mErrorMessage;
    };

}   // namespace qti::aisw::bfv::utils::returns

#endif //BINARYFILEVIEWER_ERRORBASE_H
