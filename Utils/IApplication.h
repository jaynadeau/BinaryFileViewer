//
// Created by jnadeau on 11/11/2025.
//

#ifndef BINARYFILEVIEWER_IAPPLICATION_H
#define BINARYFILEVIEWER_IAPPLICATION_H

#include <atomic>

namespace bfv::utils {
    enum class APPLICATION_STATE {
        STARTED,
        STOPPED,
        PAUSED,
        UNKNOWN
    };

    class IApplication {
    public:
        IApplication() = default;
        virtual ~IApplication() = default;

        virtual void Start() = 0;
        virtual void Stop() = 0;
        virtual void Restart() = 0;
        virtual void Pause() = 0;
        // optional
        virtual void ApplicationMain(void* arg, std::atomic<bool>& stopFlag) {}
    };
}

#endif //BINARYFILEVIEWER_IAPPLICATION_H
