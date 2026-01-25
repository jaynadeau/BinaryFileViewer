//
// Created by jnadeau on 11/18/2022.
//

#ifndef CONFIGURATION_ICONFIGURATION_H
#define CONFIGURATION_ICONFIGURATION_H

#include <memory>

namespace configuration {

    class IConfiguration;
    using ConfigurationPtr = std::shared_ptr<IConfiguration>;

    class IConfiguration
    {
    public:
        virtual ConfigurationPtr getConfiguration() = 0;
        virtual ~IConfiguration() = default;
    };
}

#endif //CONFIGURATION_ICONFIGURATION_H
