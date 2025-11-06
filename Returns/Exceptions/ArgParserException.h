//
// Created by jnadeau on 12/6/2023.
//

#ifndef BINARYFILEVIEWER_ARGPARSEREXCEPTION_H
#define BINARYFILEVIEWER_ARGPARSEREXCEPTION_H

#include <stdexcept>

namespace bfv::returns::exceptions {

    class ArgParserException : public std::logic_error {
            using std::logic_error::logic_error;
        };

    } // exceptions

#endif //BINARYFILEVIEWER_ARGPARSEREXCEPTION_H
