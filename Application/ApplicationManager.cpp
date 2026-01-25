//
// Created by jnadeau on 10/4/2022.
//

#include "ApplicationManager.h"

#include "ApplicationError.h"

#include <iostream>

namespace application {

    ApplicationManager::ExpectedApplicationName ApplicationManager::addApplication(std::string_view name, ApplicationPtr application) {
        std::cout << "Adding application " << name << " to manager..." << std::endl;
        if (application) {
            if (bool isAdded = mApplications.emplace(std::string(name), std::move(application)).second; !isAdded) {
                return returns::unexpected{
                    returns::ApplicationError{returns::ApplicationError::TYPE::APPLICATION_EXISTS, name}};
            }
            return name;
        }
        else {
            return returns::unexpected{
                returns::ApplicationError{returns::ApplicationError::TYPE::APPLICATION_UNINITIALIZED, name}};
        }
    }

    ApplicationManager::ExpectedApplicationName ApplicationManager::start(std::string_view name) {
        std::cout << "Starting application " << name << std::endl;
        if (const auto& it = mApplications.find(std::string{name}); it != mApplications.end()) {
            it->second.get()->start();
            return name;
        }
        else {
            return returns::unexpected{
                returns::ApplicationError{returns::ApplicationError::TYPE::APPLICATION_NOT_FOUND, name}
            };
        }
    }

    ApplicationManager::ExpectedApplicationName ApplicationManager::stop(std::string_view name) {
        std::cout << "Stopping application " << name << std::endl;
        if (const auto& it = mApplications.find(std::string{name}); it != mApplications.end()) {
            it->second.get()->stop();
            return name;
        }
        else {
            return returns::unexpected{
                returns::ApplicationError{returns::ApplicationError::TYPE::APPLICATION_NOT_FOUND, name}};
        }
    }

    ApplicationManager::ExpectedApplicationName ApplicationManager::restart(std::string_view name) {
        std::cout << "Restarting application " << name << std::endl;
        if (ExpectedApplicationName stopResult = stop(name); stopResult.has_value()) {
            if (ExpectedApplicationName startResult = start(name); startResult.has_value()) {
                return name;
            }
            else {
                return startResult;
            }
        }
        else {
            return stopResult;
        }
    }

    ApplicationManager::ExpectedApplicationName ApplicationManager::pause(std::string_view name) {
        std::cout << "Pausing application " << name << std::endl;
        if (const auto& it = mApplications.find(std::string{name}); it != mApplications.end()) {
            it->second.get()->pause();
            return name;
        }
        else {
            return returns::unexpected{
                returns::ApplicationError{returns::ApplicationError::TYPE::APPLICATION_NOT_FOUND, name}};
        }
    }


}
