//
// Created by jnadeau on 10/4/2022.
//

#ifndef BINARYFILEVIEWER_APPLICATION_H
#define BINARYFILEVIEWER_APPLICATION_H

#include "Utils/SingletonBase.h"

namespace bfv {

    class Application final : public utils::SingletonBase<Application>
    {
        public:
            Application(const Application&) = delete;
            Application(Application&&) = delete;
            Application& operator=(const Application&) = delete;
            Application& operator=(Application&&) = delete;
            ~Application() final = default;

            void Start();
            void Stop();
            void Restart();

        private:
            Application() = default;
            friend class SingletonBase<Application>;
        };
}   // namespace bfv

#endif //BINARYFILEVIEWER_APPLICATION_H
