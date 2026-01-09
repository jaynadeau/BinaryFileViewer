//
// Created by jnadeau on 11/18/2022.
//

#ifndef BFV_CONFIGURATION_H
#define BFV_CONFIGURATION_H

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

#endif // BFV_CONFIGURATION_H
