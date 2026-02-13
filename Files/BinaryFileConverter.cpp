//
// Created by jnadeau on 2/12/2026.
//

#include "BinaryFileConverter.h"

#include <cstdint>
#include <iostream>
#include <utility>

namespace files {

std::unordered_map<std::string_view, DataType> BinaryFileConverter::mDataTypeMap
{
    {"INT8", DataType::INT8},
    {"INT16", DataType::INT16},
    {"INT32", DataType::INT32},
    {"INT64", DataType::INT64},
    {"UINT8", DataType::UINT8},
    {"UINT16", DataType::UINT16},
    {"UINT32", DataType::UINT32},
    {"UINT64", DataType::UINT64},
    {"FLOAT", DataType::FLOAT},
    {"DOUBLE", DataType::DOUBLE},
    {"LONG_DOUBLE", DataType::LONG_DOUBLE},
};

BinaryFileConverter::BinaryFileConverter(DataType type)
: mType{type}
{ }

BinaryFileConverter::BinaryFileConverter(std::string_view type)
: mType{mDataTypeMap[type]}
{ }

void BinaryFileConverter::convert(const std::vector<unsigned char>& data) const {
    switch (mType) {
        case DataType::UINT8: {
            const std::uint8_t* typedData = reinterpret_cast<const std::uint8_t*>(data.data());
            size_t count = data.size() / sizeof(std::uint8_t);
            std::cout << "UINT8 (" << count << " elements): ";
            for (size_t i = 0; i < count; ++i) {
                std::cout << static_cast<int>(typedData[i]) << " ";
            }
            std::cout << "\n";
            break;
        }
        case DataType::UINT16: {
            const std::uint16_t* typedData = reinterpret_cast<const std::uint16_t*>(data.data());
            size_t count = data.size() / sizeof(std::uint16_t);
            std::cout << "UINT16 (" << count << " elements): ";
            for (size_t i = 0; i < count; ++i) {
                std::cout << typedData[i] << " ";
            }
            std::cout << "\n";
            break;
        }
        case DataType::UINT32: {
            const std::uint32_t* typedData = reinterpret_cast<const std::uint32_t*>(data.data());
            size_t count = data.size() / sizeof(std::uint32_t);
            std::cout << "UINT32 (" << count << " elements): ";
            for (size_t i = 0; i < count; ++i) {
                std::cout << typedData[i] << " ";
            }
            std::cout << "\n";
            break;
        }
        case DataType::INT8: {
            const std::int8_t* typedData = reinterpret_cast<const std::int8_t*>(data.data());
            size_t count = data.size() / sizeof(std::int8_t);
            std::cout << "INT8 (" << count << " elements): ";
            for (size_t i = 0; i < count; ++i) {
                std::cout << static_cast<int>(typedData[i]) << " ";
            }
            std::cout << "\n";
            break;
        }
        case DataType::INT16: {
            const std::int16_t* typedData = reinterpret_cast<const std::int16_t*>(data.data());
            size_t count = data.size() / sizeof(std::int16_t);
            std::cout << "INT16 (" << count << " elements): ";
            for (size_t i = 0; i < count; ++i) {
                std::cout << typedData[i] << " ";
            }
            std::cout << "\n";
            break;
        }
        case DataType::INT32: {
            const std::int32_t* typedData = reinterpret_cast<const std::int32_t*>(data.data());
            size_t count = data.size() / sizeof(std::int32_t);
            std::cout << "INT32 (" << count << " elements): ";
            for (size_t i = 0; i < count; ++i) {
                std::cout << typedData[i] << " ";
            }
            std::cout << "\n";
            break;
        }
        case DataType::FLOAT: {
            const float* typedData = reinterpret_cast<const float*>(data.data());
            size_t count = data.size() / sizeof(float);
            std::cout << "Float (" << count << " elements): ";
            for (size_t i = 0; i < count; ++i) {
                std::cout << typedData[i] << " ";
            }
            std::cout << "\n";
            break;
        }
        case DataType::DOUBLE: {
            const double* typedData = reinterpret_cast<const double*>(data.data());
            size_t count = data.size() / sizeof(double);
            std::cout << "Double (" << count << " elements): ";
            for (size_t i = 0; i < count; ++i) {
                std::cout << typedData[i] << " ";
            }
            std::cout << "\n";
            break;
        }
        case DataType::INT64:
        {
            const std::int64_t* typedData = reinterpret_cast<const std::int64_t*>(data.data());
            size_t count = data.size() / sizeof(std::int64_t);
            std::cout << "Int64 (" << count << " elements): ";
            for (size_t i = 0; i < count; ++i) {
                std::cout << typedData[i] << " ";
            }
            std::cout << "\n";
            break;
        }
        case DataType::UINT64:
        {
            const std::uint64_t* typedData = reinterpret_cast<const std::uint64_t*>(data.data());
            size_t count = data.size() / sizeof(std::uint64_t);
            std::cout << "UInt64 (" << count << " elements): ";
            for (size_t i = 0; i < count; ++i) {
                std::cout << typedData[i] << " ";
            }
            std::cout << "\n";
            break;
        }
        case DataType::LONG_DOUBLE:
        {
            const long double* typedData = reinterpret_cast<const long double*>(data.data());
            size_t count = data.size() / sizeof(long double);
            std::cout << "LongDouble (" << count << " elements): ";
            for (size_t i = 0; i < count; ++i) {
                std::cout << typedData[i] << " ";
            }
            std::cout << "\n";
            break;
        }
    }
}

}
