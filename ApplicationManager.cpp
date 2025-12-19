//
// Created by jnadeau on 10/4/2022.
//
#include <iostream>

#include "ApplicationManager.h"

namespace bfv {

    ApplicationManager::ApplicationManager(utils::IApplication& application)
        : mApplication(&application)
    {}

    void ApplicationManager::Start() {
        std::cout << "Starting application..." << std::endl;
        mApplication->Start();
    }

    void ApplicationManager::Stop() {
        std::cout << "Stopping application..." << std::endl;
        mApplication->Stop();
    }

    void ApplicationManager::Restart() {
        ApplicationManager::getInstance().Stop();
        ApplicationManager::getInstance().Start();
    }

    void ApplicationManager::Pause() {
        std::cout << "Pausing application..." << std::endl;
        mApplication->Pause();
    }


}   // namespace bfv
