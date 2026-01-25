//
// Created by jnadeau on 11/18/2022.
//

#ifndef CONFIGURATION_BFV_CONFIGURATION_H
#define CONFIGURATION_BFV_CONFIGURATION_H

#include "IConfiguration.h"

#include <string>

namespace bfv::configuration {

    class BfvConfiguration : public ::configuration::IConfiguration {
    public:
        ::configuration::ConfigurationPtr getConfiguration() override;
    private:
        std::string mInputFilename;
        std::string mOutputFilename;
    };

}

#endif // CONFIGURATION_BFV_CONFIGURATION_H
