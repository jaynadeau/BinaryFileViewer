//
// Created by jnadeau on 11/11/2025.
//

#ifndef BINARYFILEVIEWER_BINARYFILEVIEWERAPPLICATION_H
#define BINARYFILEVIEWER_BINARYFILEVIEWERAPPLICATION_H

#include "Application/ApplicationBase.h"
#include "Utils/Threads/DeferredJoinableThread.h"

namespace bfv {

    class BinaryFileViewerApplication : public application::ApplicationBase {
    public:
        BinaryFileViewerApplication(std::string_view inputFilename, std::string_view outputType, std::string_view outputFilename = "default.out");
        ~BinaryFileViewerApplication() = default;

        void start()   override;
        void stop()    override;
        void restart() override;
        void pause()   override;
    private:
        void applicationMain();

        std::string mInputFilename;
        std::string mOutputFilename;
        std::string mOutputType;
    };
}

#endif //BINARYFILEVIEWER_BINARYFILEVIEWERAPPLICATION_H
