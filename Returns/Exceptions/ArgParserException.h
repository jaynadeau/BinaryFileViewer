//
// Created by jnadeau on 12/6/2023.
//

#ifndef EXCEPTIONS_ARGPARSEREXCEPTION_H
#define EXCEPTIONS_ARGPARSEREXCEPTION_H

#include <stdexcept>

namespace returns::exceptions {

    class ArgParserException : public std::logic_error {
            using std::logic_error::logic_error;
        };

}

#endif //EXCEPTIONS_ARGPARSEREXCEPTION_H
