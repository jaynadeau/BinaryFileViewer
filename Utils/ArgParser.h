//
// Created by jnadeau on 11/16/2022.
//

#ifndef BINARYFILEVIEWER_ARGPARSER_H
#define BINARYFILEVIEWER_ARGPARSER_H

#include "SingletonBase.h"

#include <cstdint>
#include <string>
#include <variant>
#include <vector>

#include "../Returns/Expected.h"
#include "../Returns/ParseError.h"

namespace qti::aisw::bfv::utils {

    class ArgParser final : public SingletonBase<ArgParser>
    {
    public:
        enum class TYPE
        {
            STRING,
            INT8,
            INT16,
            INT32,
            INT64,
            UINT8,
            UINT16,
            UINT32,
            UINT64,
            FLOAT,
            DOUBLE,
            LONG_DOUBLE,
        };

    private:
        struct Argument
        {
            using argValue_t = std::variant<std::string, std::int8_t, std::int16_t, std::int32_t, std::int64_t, std::uint8_t,
                    std::uint16_t, std::uint32_t, std::uint64_t, float, double, long double>;
            Argument() = delete;
            Argument(std::string name, bool required, bool isFlag, std::string description, TYPE type);
            Argument(const Argument &other) = default;
            Argument(Argument &&other) noexcept = default;
            Argument& operator=(const Argument &other) = default;
            Argument& operator=(Argument &&other) noexcept = default;
            ~Argument() = default;

//            std::string getString();
//            std::uint8_t getUint8();
//            float getFloat();

            std::string name;
            bool isRequired{false};
            bool isFlag{false};
            std::string description;
            ArgParser::TYPE type;
            argValue_t value;
        };

    public:
        using Arguments = std::vector<Argument>;

        ArgParser(const ArgParser&) = delete;
        ArgParser(ArgParser&&) = delete;
        ArgParser& operator=(const ArgParser&) = delete;
        ArgParser& operator=(ArgParser&&) = delete;
        ~ArgParser() final = default;

        Arguments Parse(int argc, char* argv[]);
        void addArgument(std::string name, bool required, bool isFlag, std::string description, TYPE type);
    private:
        ArgParser() = default;
        friend class SingletonBase<ArgParser>;

        returns::expected<Arguments, returns::ParseError> validateArguments(const std::vector<std::string>& argumentsToValidate);
        returns::expected<Arguments, returns::ParseError> validateArgumentTypes(Arguments& requiredArguments);

        std::uint32_t mArgumentCount{0};
        std::vector<std::string> mOriginalArguments;
        Arguments mExpectedArguments;
        returns::expected<Arguments, returns::ParseError> mValidatedArguments;

        returns::expected<Arguments, returns::ParseError> getRequiredArguments(const std::vector<std::string> &argumentsToValidate);
    };

}   // qti::aisw::bfv::utils

#endif //BINARYFILEVIEWER_ARGPARSER_H
