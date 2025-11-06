//
// Created by jnadeau on 10/4/2022.
//

#include "CStdError.h"

#include <cerrno>
// Use the POSIX version of strerror_r instead of the GNU-specific version...
#define __USE_XOPEN2K 1
#undef __USE_GNU
#include <string.h>

namespace bfv::returns {

    CStdError::CStdError()
    : ErrorBase(errno)
    {
        char tmpBuf[TMP_BUF_SIZE];
        int result = strerror_r(mErrorNumber, tmpBuf, TMP_BUF_SIZE);
        switch (result) {
            case 0:
                mErrorMessage.assign(tmpBuf);
                break;
            case EINVAL:
                mErrorMessage.assign("strerror_r: The value of errno is not a valid error number.");
                break;
            case ERANGE:
                mErrorMessage.assign("strerror_r: Insufficient storage was supplied to contain the error description string.");
                break;
            default:
                mErrorMessage.assign("strerror_r: Call to strerror_r returned an unknown error.");
                break;
        }
    }

}   // namespace bfv::utils::returns
