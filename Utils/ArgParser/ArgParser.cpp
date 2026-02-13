//
// Created by jnadeau on 11/16/2022.
//

#include "ArgParser.h"

#include <algorithm>
#include <cctype>

#include "../../Returns/Exceptions/ArgParserException.h"

namespace utils {

    ArgParser::Argument::Argument(std::string_view name, bool isRequired, const bool isFlag, std::string_view description, const ArgParser::TYPE type)
    : name{name}
    , isRequired{isRequired}
    , isFlag{isFlag}
    , description{description}
    , type{type}
    {}

    ArgParser& ArgParser::addArgument(std::string_view name, bool isRequired, bool isFlag, std::string_view description, ArgParser::TYPE type) {
        mUserSpecifiedArguments.emplace_back(std::string(name), isRequired, isFlag, std::string(description), type);
        return *this;
    }

    ArgParser& ArgParser::addString(const std::string& name, bool required, const std::string& help,
        const std::string& defaultValue) {
        return addArgument(name, required, false, help, TYPE::STRING);
        // if (!required && !defaultValue.empty()) {
        //     setDefaultValue(name, defaultValue);
        // }
    }

    std::vector<std::string> ArgParser::parseCommandLineArgs(const std::string& arg) {
        std::vector<std::string> parsedArgs;
        if (const auto it = arg.find_first_of("="); it != std::string::npos) {
            std::string key   = arg.substr(0, it);
            std::string value = arg.substr(it + 1);
            parsedArgs.emplace_back(key);
            parsedArgs.emplace_back(value);
        }
        else {
            parsedArgs.emplace_back(arg);
        }
        return parsedArgs;
    }

    ArgParser::ExpectedNamedArguments ArgParser::parseInternal(const int argc, char **argv) {
        mArgumentCount = argc;
        mOriginalArguments.reserve(mArgumentCount);
        for(int argCount = 1; argCount < mArgumentCount; ++argCount)
        {
            const std::string arg = argv[argCount];
            std::vector<std::string> parsedArgs = parseCommandLineArgs(arg);
            mOriginalArguments.insert(mOriginalArguments.end(), parsedArgs.begin(), parsedArgs.end());
        }
        mValidatedArguments = validateArguments(mOriginalArguments);
        if(!mValidatedArguments) {
            return returns::unexpected(mValidatedArguments.error());
        }
        return mValidatedArguments;
    }

    ArgParser::ExpectedParseResult ArgParser::parse(int argc, char** argv) {
        auto result = parseInternal(argc, argv);
        if (!result.has_value())
            return returns::unexpected(result.error());
        return ParseResult(std::move(result.value()));
    }

    ArgParser::ExpectedNamedArguments ArgParser::validateArguments(const std::vector<std::string>& argumentsToValidate) {
        NamedArguments validatedArguments;
        for(auto& specifiedArgument : mUserSpecifiedArguments) {
            if(auto foundArg = std::find(argumentsToValidate.begin(), argumentsToValidate.end(), specifiedArgument.name); foundArg != argumentsToValidate.end()) {
                if (ExpectedArgument argument = validateArgumentType(foundArg, specifiedArgument); argument.has_value()) {
                    // validatedArguments.emplace_back(argument.value());
                    if (bool isAdded = validatedArguments.emplace(specifiedArgument.name, argument.value()).second; !isAdded) {
                        return returns::unexpected{returns::ParseError{returns::ParseError::TYPE::ARGUMENT_EXISTS, specifiedArgument.name}};
                    }
                }
                else {
                    return returns::unexpected(argument.error());
                }
            }
            else if (specifiedArgument.isRequired) {
                return returns::unexpected{returns::ParseError{returns::ParseError::TYPE::MISSING_REQD_ARG, specifiedArgument.name}};
            }
        }
        return validatedArguments;
    }

    bool ArgParser::looksLikeAFlag(const std::vector<std::string>::const_iterator &iterator, const ArgParser::Argument &argument) {
        if (iterator->rfind("--", 0) == 0) { // Starts with "--"
            return true;
        }
        else if (iterator->rfind("-", 0) == 0) {
            if (argument.type == ArgParser::TYPE::STRING) {
                return true;
            }
            else {
                if (iterator->size() > 1 && !std::isdigit(static_cast<unsigned char>((*iterator)[1])) && (*iterator)[1] != '.') {
                    return true;
                }
            }
        }
        return false;
    }

    ArgParser::ExpectedArgument ArgParser::validateArgumentType(std::vector<std::string>::const_iterator& iterator, Argument& argument) {
        // argument is not a flag and so should have a value in the next element...
        if(!argument.isFlag) {
            // increment the iterator to get the value
            if(++iterator == mOriginalArguments.end()) {
                return returns::unexpected{returns::ParseError{returns::ParseError::TYPE::MISSING_VALUE, argument.name}};
            }

            // check to see if the value looks like a flag...also checking for negative values as well
            if (looksLikeAFlag(iterator, argument)) {
                return returns::unexpected{returns::ParseError{returns::ParseError::TYPE::MISSING_VALUE, argument.name}};
            }

            try {
                switch (argument.type) {
                    case ArgParser::TYPE::STRING:
                        argument.value = std::string{*iterator};
                        break;
                    case ArgParser::TYPE::BOOL:
                        argument.value = (std::string{*iterator} == "true");
                        break;
                    case ArgParser::TYPE::INT8:
                        argument.value = static_cast<std::int8_t>(std::stoi(*iterator));
                        break;
                    case ArgParser::TYPE::INT16:
                        argument.value = static_cast<std::int16_t>(std::stoi(*iterator));
                        break;
                    case ArgParser::TYPE::INT32:
                        argument.value = static_cast<std::int32_t>(std::stol(*iterator));
                        break;
                    case ArgParser::TYPE::INT64:
                        argument.value = static_cast<std::int64_t>(std::stoll(*iterator));
                        break;
                    case ArgParser::TYPE::UINT8:
                        argument.value = static_cast<std::uint8_t>(std::stoul(*iterator));
                        break;
                    case ArgParser::TYPE::UINT16:
                        argument.value = static_cast<std::uint16_t>(std::stoul(*iterator));
                        break;
                    case ArgParser::TYPE::UINT32:
                        argument.value = static_cast<std::uint32_t>(std::stoul(*iterator));
                        break;
                    case ArgParser::TYPE::UINT64:
                        argument.value = static_cast<std::uint64_t>(std::stoull(*iterator));
                        break;
                    case ArgParser::TYPE::FLOAT:
                        argument.value = std::stof(*iterator);
                        break;
                    case ArgParser::TYPE::DOUBLE:
                        argument.value = std::stod(*iterator);
                        break;
                    case ArgParser::TYPE::LONG_DOUBLE:
                        argument.value = std::stold(*iterator);
                        break;
                }
            } catch(const std::invalid_argument& ia) {
                // could not convert argument to specified type, incompatible type
                return returns::unexpected{returns::ParseError{returns::ParseError::TYPE::INCOMPATIBLE_TYPE, argument.name}};
            } catch(const std::out_of_range& oor) {
                // the value of the argument does not match the type specified, range error
                return returns::unexpected{returns::ParseError{returns::ParseError::TYPE::RANGE_ERROR, argument.name}};
            }
        }
        return argument;
    }
}
