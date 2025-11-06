//
// Created by jnadeau on 10/4/2022.
//
#include <iostream>

#include "Application.h"

namespace qti::aisw::bfv {

    void Application::Start() {
        std::cout << "Starting application..." << std::endl;
    }

    void Application::Stop() {
        std::cout << "Stopping application..." << std::endl;
    }

    void Application::Restart() {
        Application::getInstance().Stop();
        Application::getInstance().Start();
    }
}   // namespace qti::aisw::bfv
