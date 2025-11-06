//
// Created by jnadeau on 11/18/2022.
//

#ifndef BINARYFILEVIEWER_ICONFIGURATION_H
#define BINARYFILEVIEWER_ICONFIGURATION_H

#include <memory>

namespace bfv::configuration {

    class IConfiguration;
    using ConfigurationPtr = std::shared_ptr<IConfiguration>;

    class IConfiguration
    {
    public:
        virtual ConfigurationPtr getConfiguration() = 0;
        virtual ~IConfiguration() = default;
    };
}   // bfv::configuration

#endif //BINARYFILEVIEWER_ICONFIGURATION_H
