//
// Created by jnadeau on 10/4/2022.
//

#ifndef APPLICATION_APPLICATION_MANAGER_H
#define APPLICATION_APPLICATION_MANAGER_H

#include "ApplicationError.h"
#include "IApplication.h"
#include "../Returns/Expected.h"
#include "../Utils/SingletonBase.h"

#include <memory>
#include <string>
#include <unordered_map>


namespace application {

    class ApplicationManager final : public utils::SingletonBase<ApplicationManager>
    {
        public:
            using ApplicationPtr = std::unique_ptr<IApplication>;
            using ExpectedApplicationName = returns::expected<std::string_view, returns::ApplicationError>;

            ApplicationManager(const ApplicationManager&) = delete;
            ApplicationManager(ApplicationManager&&) = delete;
            ApplicationManager&operator=(const ApplicationManager&) = delete;
            ApplicationManager&operator=(ApplicationManager&&) = delete;
            ~ApplicationManager() override = default;

            ExpectedApplicationName addApplication(std::string_view name, ApplicationPtr application);

            ExpectedApplicationName start(std::string_view name);
            ExpectedApplicationName stop(std::string_view name);
            ExpectedApplicationName restart(std::string_view name);
            ExpectedApplicationName pause(std::string_view name);

        private:
            ApplicationManager() = default;
            friend class SingletonBase<ApplicationManager>;

            using Applications = std::unordered_map<std::string, ApplicationPtr>;
            Applications mApplications;
        };
}

#endif // APPLICATION_APPLICATION_MANAGER_H
