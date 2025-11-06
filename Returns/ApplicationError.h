//
// Created by jnadeau on 10/4/2022.
//

#ifndef BINARYFILEVIEWER_APPLICATIONERROR_H
#define BINARYFILEVIEWER_APPLICATIONERROR_H

#include "ErrorBase.h"

#include <string>

namespace bfv::returns {

    class ApplicationError : public ErrorBase
    {
    public:
        ApplicationError() = default;
        ApplicationError(int errorNumber, std::string errorMessage);
        ~ApplicationError() override = default;
    };

}   // bfv::returns

#endif //BINARYFILEVIEWER_APPLICATIONERROR_H
