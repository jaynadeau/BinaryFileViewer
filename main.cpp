#include "Application.h"
#include "Returns/CStdError.h"
#include "Returns/ApplicationError.h"
#include "Utils/ArgParser.h"
#include "Returns/Exceptions/ArgParserException.h"


#include <iostream>
#include <string>

using namespace bfv;

int main(int argc, char* argv[])
{
    std::cout << "Welcome to the binary file viewer app." << std::endl;
//    static Application& app = Application::getInstance();
    static utils::ArgParser& parser = utils::ArgParser::getInstance();
    parser.addArgument("--input_filename", true, false, "Path to the binary file to be viewed.", utils::ArgParser::TYPE::STRING);
    parser.addArgument("--output_filename", false, false, "Path to the output text file to convert the binary file to.", utils::ArgParser::TYPE::STRING);
    parser.addArgument("--output_type", true, false, "The format to output/interpret the binary file as. Can be one of [UINT8_T, UINT16_T, UINT32_T, INT8_T, INT16_T, INT32_T, FLOAT32, HEX, CHAR, BINARY]", utils::ArgParser::TYPE::STRING);
    try {
        const utils::ArgParser::Arguments args = parser.Parse(argc, argv);
        for(const auto& arg : args)
        {
            // get the std::any value...need helper method or methods...
            std::cout << arg.name << " " << static_cast<int>(arg.type) << std::endl;

            // << std::get<static_cast<int>(arg.type)>(arg.value) <<
            std::cout << std::endl;
        }
    }
    catch (const returns::exceptions::ArgParserException& exception) {
        std::cout << exception.what() << std::endl;
    }



//    returns::CStdError myCError;
//    std::cout << "CStdError: ";
//    std::cout << myCError.getErrorAsString() << " " << myCError.getErrorMessage() << " " << myCError.getErrorNumber() << "\n";
//    returns::ApplicationError myAppError;
//    std::cout << "ApplicationError: ";
//    std::cout << myAppError.getErrorAsString() << " " << myAppError.getErrorMessage() << " " << myAppError.getErrorNumber() << "\n";

    return 0;
}
