//
// Created by jnadeau on 11/30/2023.
//

#include "ParseError.h"

namespace qti::aisw::bfv::returns {

//    ParseError::ErrorDescription ParseError::mErrorDescription{{0, "Could not convert argument to the specified type."},
//                                                                     {1,       "The value of the argument cannot be represented by the specified type."},
//                                                                     {2,  "Missing required argument."}};

    ParseError::ParseError(TYPE errorType)
    : ErrorBase{static_cast<int>(errorType), ERROR_DESCRIPTION.at(errorType)}
    {
    }
}
