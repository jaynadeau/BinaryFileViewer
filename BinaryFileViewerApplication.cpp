//
// Created by jnadeau on 11/11/2025.
//

#include "BinaryFileViewerApplication.h"

#include <iostream>

#include "Files/BinaryFile.h"
#include "Files/BinaryFileConverter.h"

namespace bfv {

    BinaryFileViewerApplication::BinaryFileViewerApplication(std::string_view inputFilename, std::string_view outputType, std::string_view outputFilename)
    : mInputFilename{inputFilename}
    , mOutputFilename{outputFilename}
    , mOutputType{outputType}
    {
        mMainThread = utils::threads::makeDeferredMemberThread(this, &BinaryFileViewerApplication::applicationMain);
    }


    void BinaryFileViewerApplication::start() {
        std::cout << "starting app..." << std::endl;
        ApplicationBase::start();
        mMainThread.start();
    }

    void BinaryFileViewerApplication::stop() {
        std::cout << "stopping app..." << std::endl;
        ApplicationBase::stop();
    }

    void BinaryFileViewerApplication::restart() {

    }

    void BinaryFileViewerApplication::pause() {

    }

    void BinaryFileViewerApplication::resume() {

    }

    void BinaryFileViewerApplication::applicationMain() {
        mStateFlag.store(application::APPLICATION_STATE::RUNNING);

        std::cout << "Starting BinaryFileViewerApplication worker thread..." << std::endl;
        while (mStateFlag.load() != application::APPLICATION_STATE::STOPPED) {
            sleep(2);

            std::cout << "Opening file: " << mInputFilename << std::endl;
            std::cout << "Output file: " << mOutputFilename << std::endl;
            std::cout << "Output type: " << mOutputType << std::endl;

            // open input file in binary mode
            files::BinaryFile file{mInputFilename};
            // convert the type to the specified type
            files::BinaryFileConverter converter{mOutputType};
            converter.convert(file.getData());

            // output the file using the specified output filename
        }
        std::cout << "Thread worker stopped..." << std::endl;
    }


}
