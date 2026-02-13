//
// Created by jnadeau on 2/12/2026.
//

#include "BinaryFile.h"

namespace files {

BinaryFile::BinaryFile(std::string_view filename)
: mFilename(filename)
{
    mFile.open(mFilename, std::ios::binary);
    if (!mFile.is_open()) {
        throw std::runtime_error("Failed to open file: " + mFilename);
    }
    // get file size...
    mFile.seekg(0, std::ios::end);
    mFileSize = mFile.tellg();
    mFile.seekg(0, std::ios::beg);

    // Check for seek errors
    if (!mFile) {
        throw std::runtime_error("Failed to determine file size: " + mFilename);
    }

    // do not bother reading file data if file is empty...
    if (mFileSize == 0) {
        return;
    }
    mFileData.resize(static_cast<size_t>(mFileSize));
    mFile.read(reinterpret_cast<char*>(mFileData.data()), mFileSize);

    if (!mFile || mFile.gcount() != static_cast<std::streamsize>(mFileSize)) {
        throw std::runtime_error("Failed to read contents of file: " + mFilename);
    }
}

bool BinaryFile::isOpen() {
    return mFile.is_open();
}

} // files
