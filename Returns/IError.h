//
// Created by jnadeau on 10/4/2022.
//

#ifndef BINARYFILEVIEWER_IERROR_H
#define BINARYFILEVIEWER_IERROR_H

#include <iostream>
#include <string>

namespace qti::aisw::bfv::returns {

    class IError
    {
    public:
        virtual ~IError() {std::cout <<"~IError()\n";};

        [[nodiscard]] virtual std::string getErrorAsString() const = 0;
        [[nodiscard]] virtual std::string getErrorMessage() const = 0;
        [[nodiscard]] virtual int getErrorNumber() const = 0;
    };

}   // namespace qti::aisw::bfv::utils::returns

#endif //BINARYFILEVIEWER_IERROR_H
