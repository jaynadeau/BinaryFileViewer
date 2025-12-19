//
// Created by jnadeau on 11/16/2022.
//

#include "ArgParser.h"

#include <algorithm>
#include <iostream>
#include <utility>

#include "../Returns/Exceptions/ArgParserException.h"

namespace bfv::utils {

    ArgParser::Argument::Argument(std::string name, bool isRequired, const bool isFlag, std::string description, const ArgParser::TYPE type)
    : name{std::move(name)}
    , isRequired{isRequired}
    , isFlag{isFlag}
    , description{std::move(description)}
    , type{type}
    {}

    void ArgParser::addArgument(std::string name, bool isRequired, bool isFlag, std::string description, ArgParser::TYPE type) {
        mExpectedArguments.emplace_back(std::move(name), isRequired, isFlag, std::move(description), type);
    }

    ArgParser::Arguments ArgParser::Parse(const int argc, char **argv) {
        mArgumentCount = argc;
        mOriginalArguments.reserve(mArgumentCount);
        for(int argCount = 0; argCount < mArgumentCount; ++argCount)
        {
            mOriginalArguments.emplace_back(argv[argCount]);
        }
        mValidatedArguments = validateArguments(mOriginalArguments);
        if(!mValidatedArguments) {
            throw returns::exceptions::ArgParserException(mValidatedArguments.error().getErrorAsString());
        }
        return mValidatedArguments.value();
    }

    returns::expected<ArgParser::Arguments, returns::ParseError> ArgParser::validateArguments(const std::vector<std::string>& argumentsToValidate) {
        if(returns::expected<Arguments, returns::ParseError> requiredArguments = getRequiredArguments(argumentsToValidate))
            return validateArgumentTypes(requiredArguments.value());
        else
            return requiredArguments;
    }

    returns::expected<ArgParser::Arguments, returns::ParseError> ArgParser::getRequiredArguments(const std::vector<std::string> &argumentsToValidate) const {
        Arguments requiredArguments;
        for(const auto& expectedArgument : mExpectedArguments) {
            // foundArg has the right type based on the vector, I would like to do the same with the argument
            // NOTE: use the fact that arguments start with -- and values do not
            if(auto foundArg = std::find(argumentsToValidate.begin(), argumentsToValidate.end(), expectedArgument.name); foundArg != argumentsToValidate.end()) {
                requiredArguments.emplace_back(expectedArgument);
            }
            else {
                if(expectedArgument.isRequired) {
                    return returns::unexpected{returns::ParseError{returns::ParseError::TYPE::MISSING_REQD_ARG, expectedArgument.name}};
                }
            }
        }
        return requiredArguments;
    }

    returns::expected<ArgParser::Arguments, returns::ParseError> ArgParser::validateArgumentTypes(Arguments& requiredArguments) {
        for(auto& requiredArgument : requiredArguments) {
            auto foundArg = std::find(mOriginalArguments.begin(), mOriginalArguments.end(), requiredArgument.name);
            if(!requiredArgument.isFlag) {
                // the next argument is actually the current arguments value when not a flag argument
                if(++foundArg != mOriginalArguments.end()) {
                    try {
                        switch (requiredArgument.type) {
                            case ArgParser::TYPE::STRING:
                                requiredArgument.value = std::string{*foundArg};
                                break;
                            case ArgParser::TYPE::INT8:
                                requiredArgument.value = static_cast<std::int8_t>(std::stoi(*foundArg));
                                break;
                            case ArgParser::TYPE::INT16:
                                requiredArgument.value = static_cast<std::int16_t>(std::stoi(*foundArg));
                                break;
                            case ArgParser::TYPE::INT32:
                                requiredArgument.value = static_cast<std::int32_t>(std::stol(*foundArg));
                                break;
                            case ArgParser::TYPE::INT64:
                                requiredArgument.value = static_cast<std::int64_t>(std::stoll(*foundArg));
                                break;
                            case ArgParser::TYPE::UINT8:
                                requiredArgument.value = static_cast<std::uint8_t>(std::stoul(*foundArg));
                                break;
                            case ArgParser::TYPE::UINT16:
                                requiredArgument.value = static_cast<std::uint16_t>(std::stoul(*foundArg));
                                break;
                            case ArgParser::TYPE::UINT32:
                                requiredArgument.value = static_cast<std::uint32_t>(std::stoul(*foundArg));
                                break;
                            case ArgParser::TYPE::UINT64:
                                requiredArgument.value = static_cast<std::uint64_t>(std::stoull(*foundArg));
                                break;
                            case ArgParser::TYPE::FLOAT:
                                requiredArgument.value = static_cast<float>(std::stof(*foundArg));
                                break;
                            case ArgParser::TYPE::DOUBLE:
                                requiredArgument.value = static_cast<double>(std::stod(*foundArg));
                                break;
                            case ArgParser::TYPE::LONG_DOUBLE:
                                requiredArgument.value = static_cast<long double>(std::stold(*foundArg));
                                break;
                        }
                    } catch(const std::invalid_argument& ia) {
                        // could not convert argument to specified type, incompatible type
                        return returns::unexpected{returns::ParseError{returns::ParseError::TYPE::INCOMPATIBLE_TYPE, requiredArgument.name}};
                        // return returns::unexpected{returns::INCOMPATIBLE_TYPE};
                    } catch(const std::out_of_range& oor) {
                        // the value of the argument does not match the type specified, range error
                        return returns::unexpected{returns::ParseError{returns::ParseError::TYPE::RANGE_ERROR, requiredArgument.name}};
                        // return returns::unexpected{returns::RANGE_ERROR};
                    }
                }
            }
        }
        return requiredArguments;
    }

}
