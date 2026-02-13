//
// Created by jnadeau on 10/5/2022.
//

#ifndef FILES_IFILE_H
#define FILES_IFILE_H

namespace files {

    class IFile {
        explicit IFile(std::string_view filename);
        virtual ~IFile();


    };

}

#endif //FILES_IFILE_H
