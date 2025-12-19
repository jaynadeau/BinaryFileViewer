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

namespace bfv::utils {

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
        struct ArgumentType {
            using argValue_t = std::variant<std::string, std::int8_t, std::int16_t, std::int32_t, std::int64_t,
                    std::uint8_t, std::uint16_t, std::uint32_t, std::uint64_t, float, double, long double>;

            ArgumentType() = default;
            explicit ArgumentType(std::string value)
                : value{std::move(value)}
            {}
            explicit ArgumentType(std::int8_t value)
                : value{value}
            {}
            explicit ArgumentType(std::int16_t value)
                : value{value}
            {}
            explicit ArgumentType(std::int32_t value)
                : value{value}
            {}
            explicit ArgumentType(std::int64_t value)
                : value{value}
            {}
            explicit ArgumentType(std::uint8_t value)
                : value{value}
            {}
            explicit ArgumentType(std::uint16_t value)
                : value{value}
            {}
            explicit ArgumentType(std::uint32_t value)
                : value{value}
            {}
            explicit ArgumentType(std::uint64_t value)
                : value{value}
            {}
            explicit ArgumentType(float value)
                : value{value}
            {}
            explicit ArgumentType(double value)
                : value{value}
            {}
            explicit ArgumentType(long double value)
                : value{value}
            {}
            ArgumentType& operator=(const ArgumentType& other) = default;
            ArgumentType& operator=(std::string other) {value = other; return *this;}
            ArgumentType& operator=(std::int8_t other) {value = other; return *this;}
            ArgumentType& operator=(std::int16_t other) {value = other; return *this;}
            ArgumentType& operator=(std::int32_t other) {value = other; return *this;}
            ArgumentType& operator=(std::int64_t other) {value = other; return *this;}
            ArgumentType& operator=(std::uint8_t other) {value = other; return *this;}
            ArgumentType& operator=(std::uint16_t other) {value = other; return *this;}
            ArgumentType& operator=(std::uint32_t other) {value = other; return *this;}
            ArgumentType& operator=(std::uint64_t other) {value = other; return *this;}
            ArgumentType& operator=(float other) {value = other; return *this;}
            ArgumentType& operator=(double other) {value = other; return *this;}
            ArgumentType& operator=(long double other) {value = other; return *this;}

            operator std::string() const {return std::get<std::string>(value);}
            operator std::int8_t() const {return std::get<std::int8_t>(value);}
            operator std::int16_t() const {return std::get<std::int16_t>(value);}
            operator std::int32_t() const {return std::get<std::int32_t>(value);}
            operator std::int64_t() const {return std::get<std::int64_t>(value);}
            operator std::uint8_t() const {return std::get<std::uint8_t>(value);}
            operator std::uint16_t() const {return std::get<std::uint16_t>(value);}
            operator std::uint32_t() const {return std::get<std::uint32_t>(value);}
            operator std::uint64_t() const {return std::get<std::uint64_t>(value);}
            operator float() const {return std::get<float>(value);}
            operator double() const {return std::get<double>(value);}
            operator long double() const {return std::get<long double>(value);}

            argValue_t value;
        };

        struct Argument {
            Argument() = delete;
            Argument(std::string name, bool required, bool isFlag, std::string description, TYPE type);
            Argument(const Argument &other) = default;
            Argument(Argument &&other) noexcept = default;
            Argument& operator=(const Argument &other) = default;
            Argument& operator=(Argument &&other) noexcept = default;
            ~Argument() = default;

            std::string name;
            bool isRequired{false};
            bool isFlag{false};
            std::string description;
            ArgParser::TYPE type;
            ArgumentType value;
        };

    public:
        using Arguments = std::vector<Argument>;

        ArgParser(const ArgParser&) = delete;
        ArgParser(ArgParser&&) = delete;
        ArgParser& operator=(const ArgParser&) = delete;
        ArgParser& operator=(ArgParser&&) = delete;
        ~ArgParser() override = default;

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

        [[nodiscard]] returns::expected<Arguments, returns::ParseError> getRequiredArguments(const std::vector<std::string> &argumentsToValidate) const;
    };

}   // bfv::utils

#endif //BINARYFILEVIEWER_ARGPARSER_H
