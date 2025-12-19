//
// Created by jnadeau on 10/4/2022.
//

#ifndef BINARYFILEVIEWER_APPLICATION_MANAGER_H
#define BINARYFILEVIEWER_APPLICATION_MANAGER_H

#include "Utils/IApplication.h"
#include "Utils/SingletonBase.h"

#include <memory>

namespace bfv {

    class ApplicationManager final : public utils::SingletonBase<ApplicationManager>, public utils::IApplication
    {
        public:
            explicit ApplicationManager(IApplication& application);
            ApplicationManager(const ApplicationManager&) = delete;
            ApplicationManager(ApplicationManager&&) = delete;
            ApplicationManager& operator=(const ApplicationManager&) = delete;
            ApplicationManager& operator=(ApplicationManager&&) = delete;
            ~ApplicationManager() override = default;

            void Start() override;
            void Stop() override;
            void Restart() override;
            void Pause() override;

        private:
            ApplicationManager() = default;
            friend class SingletonBase<ApplicationManager>;

            using ApplicationPtr = std::unique_ptr<IApplication>;
            ApplicationPtr mApplication;
        };
}   // namespace bfv

#endif //BINARYFILEVIEWER_APPLICATION_MANAGER_H
