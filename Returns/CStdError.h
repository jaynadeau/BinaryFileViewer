//
// Created by jnadeau on 10/4/2022.
//

#ifndef BINARYFILEVIEWER_CSTDERROR_H
#define BINARYFILEVIEWER_CSTDERROR_H

#include "ErrorBase.h"

#include <iostream>

namespace qti::aisw::bfv::returns {

    class CStdError : public ErrorBase
    {
    public:
        CStdError();
        CStdError(const CStdError& other) = default;
        ~CStdError() override {std::cout << "~CStdError()\n";};

        CStdError& operator=(const CStdError& rhs) = default;
    private:
        static const int TMP_BUF_SIZE = 256;
    };

}   // namespace qti::aisw::bfv::utils::returns

#endif //BINARYFILEVIEWER_CSTDERROR_H
