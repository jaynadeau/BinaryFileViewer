//
// Created by jnadeau on 11/11/2025.
//

#ifndef UTILS_IAPPLICATION_H
#define UTILS_IAPPLICATION_H

#include <atomic>

namespace utils {

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

#endif // UTILS_IAPPLICATION_H
