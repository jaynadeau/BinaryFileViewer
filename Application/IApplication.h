//
// Created by jnadeau on 11/11/2025.
//

#ifndef APPLICATION_IAPPLICATION_H
#define APPLICATION_IAPPLICATION_H

namespace application {

    enum class APPLICATION_STATE {
        STARTED,
        RUNNING,
        STOPPED,
        PAUSED,
        UNKNOWN
    };

    class IApplication {
    public:
        IApplication() = default;
        virtual ~IApplication() = default;

        virtual void start()   = 0;
        virtual void stop()    = 0;
        virtual void restart() = 0;
        virtual void pause()   = 0;
        virtual void resume()  = 0;
        // optional
        // template<typename... Args>
    protected:
    };
}

#endif // APPLICATION_IAPPLICATION_H
