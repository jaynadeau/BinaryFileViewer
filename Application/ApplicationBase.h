//
// Created by jnadeau on 1/24/2026.
//

#ifndef APPLICATION_APPLICATIONBASE_H
#define APPLICATION_APPLICATIONBASE_H

#include <atomic>

#include "IApplication.h"
#include "../Utils/Threads/DeferredJoinableThread.h"

namespace application {

    class ApplicationBase : public IApplication {
    public:
        ApplicationBase();
        ~ApplicationBase() override = default;

        void start() override;
        void stop() override;
        void restart() override;
        void pause() override;
        void resume() override;
    protected:
        std::atomic<APPLICATION_STATE> mStateFlag{APPLICATION_STATE::UNKNOWN};
        utils::threads::DeferredJoinableThread mMainThread;
    };

} // application

#endif //APPLICATION_APPLICATIONBASE_H
