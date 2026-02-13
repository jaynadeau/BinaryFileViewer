//
// Created by jnadeau on 11/16/2022.
//
/**
 * @file ArgParser.h
 * @brief Header file for the ArgParser utility class.
 *
 * This file contains the definition of the ArgParser class, which provides
 * functionality for defining, parsing, and validating command-line arguments
 * in a type-safe manner.
 */
#ifndef ARGPARSER_ARGPARSER_H
#define ARGPARSER_ARGPARSER_H


#include <cstdint>
#include <optional>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

#include "../../Returns/Expected.h"
#include "ParseError.h"

namespace utils {

    /**
     * @class ArgParser
     * @brief A utility class for parsing command-line arguments.
     *
     * The ArgParser class allows users to define expected arguments, specify their types,
     * indicate whether they are required or flags, and then parse the raw command-line
     * input (argc/argv) to validate and retrieve these values.
     */
    class ArgParser final
    {
    public:
        /**
         * @enum TYPE
         * @brief Enumeration of supported argument data types.
         */
        enum class TYPE
        {
            STRING,
            BOOL,
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
        /**
         * @struct ArgumentType
         * @brief A type-safe wrapper for argument values using std::variant.
         *
         * This internal structure holds the parsed value of an argument. It supports
         * assignment and retrieval using templates to ensure type safety.
         */
        struct ArgumentType {
            using argValue_t = std::variant<std::string, bool, std::int8_t, std::int16_t, std::int32_t, std::int64_t,
                    std::uint8_t, std::uint16_t, std::uint32_t, std::uint64_t, float, double, long double>;

            /**
             * @brief Retrieves the value if it matches the requested type.
             * @tparam T The expected type of the value.
             * @return std::optional<T> containing the value if successful, or std::nullopt.
             */
            template<typename T>
            std::optional<T> get() const {
                // Map common types to the actual variant types
                if constexpr (std::is_same_v<T, int>) {
                    if (auto* ptr = std::get_if<std::int32_t>(&value)) {
                        return static_cast<T>(*ptr);
                    }
                } else if constexpr (std::is_same_v<T, unsigned int>) {
                    if (auto* ptr = std::get_if<std::uint32_t>(&value)) {
                        return static_cast<T>(*ptr);
                    }
                } else if constexpr (std::is_same_v<T, long>) {
                    if (auto* ptr = std::get_if<std::int64_t>(&value)) {
                        return static_cast<T>(*ptr);
                    }
                } else if constexpr (std::is_same_v<T, long long>) {
                    if (auto* ptr = std::get_if<std::int64_t>(&value)) {
                        return static_cast<T>(*ptr);
                    }
                } else if constexpr (std::is_same_v<T, unsigned long>) {
                    if (auto* ptr = std::get_if<std::uint64_t>(&value)) {
                        return static_cast<T>(*ptr);
                    }
                } else if constexpr (std::is_same_v<T, unsigned long long>) {
                    if (auto* ptr = std::get_if<std::uint64_t>(&value)) {
                        return static_cast<T>(*ptr);
                    }
                } else if constexpr (std::is_same_v<T, bool>) {
                    if (auto* ptr = std::get_if<bool>(&value)) {
                        return static_cast<T>(*ptr);
                    }
                } else {
                    // For exact type matches
                    if (auto* ptr = std::get_if<T>(&value)) {
                        return *ptr;
                    }
                }
                return std::nullopt;
            }
            /**
             * @brief Assigns a value to the underlying variant.
             * @tparam T The type of the value being assigned.
             * @param val The value to assign.
             * @return Reference to this ArgumentType.
             */
            template<typename T>
            requires std::assignable_from<argValue_t&, T>
            ArgumentType& operator=(T&& val) {
                value = std::forward<T>(val);
                return *this;
            }

            /**
             * @brief Retrieves the value or returns a default if the type does not match.
             * @tparam T The expected type of the value.
             * @param default_val The default value to return if the retrieval fails.
             * @return The stored value or the provided default.
             */
            template<typename T>
            T get_or(T&& default_val) const {
                return get<T>().value_or(std::forward<T>(default_val));
            }

            /// The actual variant holding the data.
            argValue_t value;
        };

        /**
         * @struct Argument
         * @brief Represents the definition and state of a single command-line argument.
         */
        struct Argument {
            Argument() = default;
            /**
             * @brief Constructs an Argument.
             * @param name The name of the argument (e.g., "--help").
             * @param isRequired True if the argument is mandatory.
             * @param isFlag True if the argument is a flag (boolean) and takes no value.
             * @param description Description of what the argument does.
             * @param type The expected data type of the argument.
             */
            Argument(std::string_view name, bool isRequired, bool isFlag, std::string_view description, TYPE type);
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
            ArgumentType value{};
        };

    public:
        using Arguments = std::vector<Argument>;
        using NamedArguments = std::unordered_map<std::string, Argument>;
        using ExpectedArguments = returns::expected<Arguments, returns::ParseError>;
        using ExpectedNamedArguments = returns::expected<NamedArguments, returns::ParseError>;
        using ExpectedArgument = returns::expected<Argument, returns::ParseError>;

        // New: Result type with clean accessors
        class ParseResult {
        public:
            explicit ParseResult(NamedArguments args) : args(std::move(args)) {}

            // Type-safe accessors
            std::string getString(const std::string& name, const std::string& defaultValue = "") const {
                if (auto val = getValue<std::string>(name))
                    return *val;
                return defaultValue;
            }

            // TODO: add all the types

            bool getBool(const std::string& name, bool defaultValue = false) const {
                if (auto val = getValue<bool>(name))
                    return *val;
                return defaultValue;
            }

            std::int8_t getInt8(const std::string& name, std::int8_t defaultValue = 0) const {
                if (auto val = getValue<std::int8_t>(name))
                    return *val;
                return defaultValue;
            }

            std::int16_t getInt16(const std::string& name, std::int16_t defaultValue = 0) const {
                if (auto val = getValue<std::int16_t>(name))
                    return *val;
                return defaultValue;
            }

            std::int32_t getInt32(const std::string& name, std::int32_t defaultValue = 0) const {
                if (auto val = getValue<std::int32_t>(name))
                    return *val;
                return defaultValue;
            }

            std::int64_t getInt64(const std::string& name, std::int64_t defaultValue = 0) const {
                if (auto val = getValue<std::int64_t>(name))
                    return *val;
                return defaultValue;
            }

            std::uint8_t getUInt8(const std::string& name, std::uint8_t defaultValue = 0) const {
                if (auto val = getValue<std::uint8_t>(name))
                    return *val;
                return defaultValue;
            }

            std::uint16_t getUInt16(const std::string& name, std::uint16_t defaultValue = 0) const {
                if (auto val = getValue<std::uint16_t>(name))
                    return *val;
                return defaultValue;
            }

            std::uint32_t getUInt32(const std::string& name, std::uint32_t defaultValue = 0) const {
                if (auto val = getValue<std::uint32_t>(name))
                    return *val;
                return defaultValue;
            }

            std::uint64_t getUInt64(const std::string& name, std::uint64_t defaultValue = 0) const {
                if (auto val = getValue<std::uint64_t>(name))
                    return *val;
                return defaultValue;
            }

            float getFloat(const std::string& name, float defaultValue = 0.0f) const {
                if (auto val = getValue<float>(name))
                    return *val;
                return defaultValue;
            }

            double getDouble(const std::string& name, double defaultValue = 0.0) const {
                if (auto val = getValue<double>(name))
                    return *val;
                return defaultValue;
            }

            long double getLongDouble(const std::string& name, long double defaultValue = 0.0) const {
                if (auto val = getValue<long double>(name))
                    return *val;
                return defaultValue;
            }

            // Check if argument was provided
            bool hasArgument(const std::string& name) const {
                return args.find(name) != args.end();
            }
        private:
            NamedArguments args;

            // Helper to get a value with type conversion
            template<typename T>
            std::optional<T> getValue(const std::string& name) const {
                const auto it = args.find(name);
                if (it == args.end()) {
                    return std::nullopt;
                }

                return it->second.value.get<T>();
            }

        };
        using ExpectedParseResult = returns::expected<ParseResult, returns::ParseError>;
        /**
         * @brief Default constructor.
         */
        ArgParser() = default;
        // Copy and Move operations are deleted to prevent accidental duplication of the parser state.
        ArgParser(const ArgParser&) = delete;
        ArgParser(ArgParser&&) = delete;
        ArgParser& operator=(const ArgParser&) = delete;
        ArgParser& operator=(ArgParser&&) = delete;
        /**
         * @brief Default destructor.
         */
        ~ArgParser() = default;

        /**
         * @brief Parses the command-line arguments.
         *
         * This function processes the arguments passed to the program and parses their values.
         *
         * @param argc The count of arguments.
         * @param argv The array of argument strings.
         * @return ExpectedParseResult containing the parsed arguments on success, or a ParseError on failure.
         */
        ExpectedParseResult parse(int argc, char** argv);
        /**
         * @brief Adds a new expected argument to the parser.
         *
         * @param name The name of the argument (e.g., "--input").
         * @param isRequired Whether the argument must be present for parsing to succeed.
         * @param isFlag Whether the argument is a flag (no value expected) or takes a parameter.
         * @param description A brief description of the argument for help text.
         * @param type The expected data type of the argument value.
         */
        ArgParser& addArgument(std::string_view name, bool isRequired, bool isFlag, std::string_view description,
            TYPE type);

        template<typename T>
        ArgParser& add(const std::string& name, bool required = true,
               const std::string& help = "", T defaultValue = T{}) {
            TYPE type = getTypeEnum<T>();
            addArgument(name, required, false, help, type);
            // Store default value if needed
            if (!required) {
                auto& arg = mUserSpecifiedArguments.back();
                arg.value = defaultValue;
            }
            return *this;
        }

        ArgParser& addString(const std::string& name, bool required = true, const std::string& help = "",
            const std::string& defaultValue = "");

    private:
        template<typename T>
        struct always_false : std::false_type {};

        template<typename T>
        static TYPE getTypeEnum() {
            if constexpr (std::is_same_v<T, std::string>) return TYPE::STRING;
            else if constexpr (std::is_same_v<T, bool>) return TYPE::BOOL;
            else if constexpr (std::is_same_v<T, std::int8_t>) return TYPE::INT8;
            else if constexpr (std::is_same_v<T, std::int16_t>) return TYPE::INT16;
            else if constexpr (std::is_same_v<T, std::int32_t>) return TYPE::INT32;
            else if constexpr (std::is_same_v<T, std::int64_t>) return TYPE::INT64;
            else if constexpr (std::is_same_v<T, std::uint8_t>) return TYPE::UINT8;
            else if constexpr (std::is_same_v<T, std::uint16_t>) return TYPE::UINT16;
            else if constexpr (std::is_same_v<T, std::uint32_t>) return TYPE::UINT32;
            else if constexpr (std::is_same_v<T, std::uint64_t>) return TYPE::UINT64;
            else if constexpr (std::is_same_v<T, float>) return TYPE::FLOAT;
            else if constexpr (std::is_same_v<T, double>) return TYPE::DOUBLE;
            else if constexpr (std::is_same_v<T, long double>) return TYPE::LONG_DOUBLE;
            else {
                static_assert(always_false<T>::value, "Unsupported type");
            }
        }
        /**
         * @brief Parses the command-line arguments.
         *
         * This function processes the arguments passed to the program, validates them against
         * the defined expected arguments, and parses their values.
         *
         * @param argc The count of arguments.
         * @param argv The array of argument strings.
         * @return ExpectedNamedArguments containing a map of the parsed arguments on success, or a ParseError on failure.
         */
        ExpectedNamedArguments parseInternal(int argc, char* argv[]);
        /**
         * @brief Validates the presence and types of all expected arguments.
         * @param argumentsToValidate The list of raw string arguments to validate.
         * @return ExpectedNamedArguments on success, or ParseError on failure.
         */
        ExpectedNamedArguments validateArguments(const std::vector<std::string>& argumentsToValidate);
        /**
         * @brief Validates and extracts the value for a specific argument.
         * @param iterator Iterator to the current position in the raw argument list.
         * @param argument The argument definition to validate against.
         * @return ExpectedArgument containing the populated argument on success, or ParseError.
         */
        ExpectedArgument validateArgumentType(std::vector<std::string>::const_iterator& iterator, Argument& argument);

        /**
         * @brief Helper function to parse specific command line string formats.
         * Handles cases like "--key=value" by splitting them.
         * @param arg The single argument string to parse.
         * @return A vector containing the split parts (or the original if no split occurred).
         */
        static std::vector<std::string> parseCommandLineArgs(const std::string& arg);
        /**
         * @brief Checks if the current iterator position looks like a flag.
         * Used to prevent consuming the next flag as a value for the current argument.
         * @param iterator Iterator to the potential value.
         * @param argument The argument currently being processed.
         * @return True if the value looks like a flag/option, False otherwise.
         */
        static bool looksLikeAFlag(const std::vector<std::string>::const_iterator &iterator, const Argument &argument);

        std::uint32_t mArgumentCount{0};
        std::vector<std::string> mOriginalArguments;
        Arguments mUserSpecifiedArguments;
        ExpectedNamedArguments mValidatedArguments;
    };

}

#endif //ARGPARSER_ARGPARSER_H
