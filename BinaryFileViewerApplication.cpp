//
// Created by jnadeau on 11/11/2025.
//

#include "BinaryFileViewerApplication.h"

#include <iostream>

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
        mMainThread.start();
    }

    void BinaryFileViewerApplication::stop() {

    }

    void BinaryFileViewerApplication::restart() {

    }

    void BinaryFileViewerApplication::pause() {

    }

    void BinaryFileViewerApplication::applicationMain() {
        sleep(2);

        std::cout << "Opening file: " << mInputFilename << std::endl;
        std::cout << "Opening file: " << mInputFilename << std::endl;
        std::cout << "Opening file: " << mInputFilename << std::endl;
        std::cout << "Opening file: " << mInputFilename << std::endl;
        std::cout << "Opening file: " << mInputFilename << std::endl;
        std::cout << "Opening file: " << mInputFilename << std::endl;
        std::cout << "Opening file: " << mInputFilename << std::endl;
        std::cout << "Opening file: " << mInputFilename << std::endl;
        std::cout << "Opening file: " << mInputFilename << std::endl;
        std::cout << "Opening file: " << mInputFilename << std::endl;
        std::cout << "Opening file: " << mInputFilename << std::endl;
        std::cout << "Opening file: " << mInputFilename << std::endl;
        std::cout << "Opening file: " << mInputFilename << std::endl;
        std::cout << "Opening file: " << mInputFilename << std::endl;
        std::cout << "Opening file: " << mInputFilename << std::endl;
        std::cout << "Opening file: " << mInputFilename << std::endl;
    }


}
