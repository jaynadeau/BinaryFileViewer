//
// Created by jnadeau on 2/12/2026.
//

#ifndef FILES_BINARYFILE_H
#define FILES_BINARYFILE_H

#include <fstream>
#include <string>
#include <vector>

namespace files {

    class BinaryFile {
    public:
        explicit BinaryFile(std::string_view filename);
        ~BinaryFile() = default;
        // Delete copy operations (file streams aren't copyable)
        BinaryFile(const BinaryFile&) = delete;
        BinaryFile& operator=(const BinaryFile&) = delete;
        // Enable move operations
        BinaryFile(BinaryFile&&) noexcept = default;
        BinaryFile& operator=(BinaryFile&&) noexcept = default;

        bool isOpen();
        size_t getSizeOfData() const { return mFileData.size(); }
        // Provide access to the data
        const std::vector<unsigned char>& getData() const { return mFileData; }
        const unsigned char* data() const { return mFileData.data(); }
    private:
        std::string mFilename;
        std::ifstream mFile;
        std::streampos mFileSize;
        std::vector<unsigned char> mFileData;
    };

} // files

#endif //FILES_BINARYFILE_H
