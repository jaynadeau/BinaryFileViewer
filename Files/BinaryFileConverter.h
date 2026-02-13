//
// Created by jnadeau on 2/12/2026.
//

#ifndef FILES_BINARYFILECONVERTER_H
#define FILES_BINARYFILECONVERTER_H

#include <string>
#include <unordered_map>
#include <vector>

namespace files {

    enum class DataType {
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

    class BinaryFileConverter {
    public:
        BinaryFileConverter() = delete;
        explicit BinaryFileConverter(DataType type);
        explicit BinaryFileConverter(std::string_view type);
        virtual ~BinaryFileConverter() = default;

        BinaryFileConverter(const BinaryFileConverter&) = default;
        BinaryFileConverter& operator=(const BinaryFileConverter&) = default;
        BinaryFileConverter(BinaryFileConverter&&) = default;
        BinaryFileConverter& operator=(BinaryFileConverter&&) = default;

        void convert(const std::vector<unsigned char>& data) const;
    private:
        DataType mType;
        static std::unordered_map<std::string_view, DataType> mDataTypeMap;
    };

}

#endif //FILES_BINARYFILECONVERTER_H
