//
// Created by jnadeau on 11/18/2022.
//

#ifndef BINARYFILEVIEWER_BFVCONFIGURATION_H
#define BINARYFILEVIEWER_BFVCONFIGURATION_H

#include "IConfiguration.h"

#include <list>
#include <string>

namespace qti::aisw::bfv::configuration {

    class BfvConfiguration : public IConfiguration {
    public:
        ConfigurationPtr getConfiguration() override;
    private:
        std::string mInputFilename;
        std::string mOutputFilename;
    };

}   // qti::aisw::bfv::configuration

#endif //BINARYFILEVIEWER_BFVCONFIGURATION_H
