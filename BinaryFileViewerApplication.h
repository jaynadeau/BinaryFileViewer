//
// Created by jnadeau on 11/11/2025.
//

#ifndef BINARYFILEVIEWER_BINARYFILEVIEWERAPPLICATION_H
#define BINARYFILEVIEWER_BINARYFILEVIEWERAPPLICATION_H

#include "Utils/IApplication.h"
#include "Utils/Threads/DeferredJoinableThread.h"

namespace bfv {

    class BinaryFileViewerApplication : public utils::IApplication {
    public:
        void Start() override;
        void Stop() override;
        void Restart() override;
        void Pause() override;
    private:
        // std::atomic<bool>& mStopFlag;
        utils::threads::DeferredJoinableThread mMainThread;
        void ApplicationMain(void* arg, std::atomic<bool>& stopFlag) override;
    };
}

#endif //BINARYFILEVIEWER_BINARYFILEVIEWERAPPLICATION_H
