#include "ApplicationManager.h"
#include "Returns/CStdError.h"
#include "Returns/ApplicationError.h"
#include "Returns/Exceptions/ArgParserException.h"
#include "Utils/ArgParser.h"
#include "Utils/Threads/DeferredJoinableThread.h"

#include <chrono>
#include <thread>
#include <iostream>
#include <string>


using namespace bfv;

void workerMethod(int a, int b) {
    for (int i = 0; i < 10; ++i) {
        std::cout << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << a + b << std::endl;
    }
}


int main(int argc, char* argv[])
{
    std::cout << "Welcome to the binary file viewer app." << std::endl;
//    static ApplicationManager& app = ApplicationManager::getInstance();
    static utils::ArgParser& parser = utils::ArgParser::getInstance();
    parser.addArgument("--input_filename", true, false, "Path to the binary file to be viewed.", utils::ArgParser::TYPE::STRING);
    parser.addArgument("--output_filename", false, false, "Path to the output text file to convert the binary file to.", utils::ArgParser::TYPE::STRING);
    parser.addArgument("--output_type", true, false, "The format to output/interpret the binary file as. Can be one of [UINT8_T, UINT16_T, UINT32_T, INT8_T, INT16_T, INT32_T, FLOAT32, HEX, CHAR, BINARY]", utils::ArgParser::TYPE::STRING);
    try {
        const utils::ArgParser::Arguments args = parser.Parse(argc, argv);
        for(const auto& arg : args)
        {
            // get the std::any value...need helper method or methods...
            std::string argValue = arg.value;
            std::cout << arg.name << " " << static_cast<int>(arg.type) <<
                " " << argValue << std::endl;

            // << std::get<static_cast<int>(arg.type)>(arg.value) <<
            std::cout << std::endl;
        }
    }
    catch (const returns::exceptions::ArgParserException& exception) {
        std::cout << exception.what() << std::endl;
    }

    // std::cout << "Testing JoinableThread class..." << std::endl;

    int a = 5;
    int b = 10;
    // utils::threads::JoinableThread jThread(workerMethod, std::ref(a), std::ref(b));


    // std::cout << "Testing ControllableThread class..." << std::endl;
    // utils::threads::ControllableThread controllableThread(workerMethod, std::ref(a), std::ref(b));

    // 1. Basic usage
    std::cout << "Test 1. Basic usage" << std::endl;
    utils::threads::DeferredJoinableThread thread([]{ std::cout << "Hello\n"; });
    thread.start();
    thread.join();

    // 2. Reset after completion
    std::cout << "Test 2. Reset after completion" << std::endl;
    thread.reset([]{ std::cout << "World\n"; });
    thread.start();
    thread.join();

    // 3. Move semantics - move BEFORE starting
    utils::threads::DeferredJoinableThread thread3([]{ std::cout << "Move before start\n"; });
    auto thread4 = std::move(thread3);  // Move before start
    thread4.start();  // ✅ Works - start the moved-to object
    thread4.join();

    // 4. Move semantics - move AFTER completion
    utils::threads::DeferredJoinableThread thread5([]{ std::cout << "Move after complete\n"; });
    thread5.start();
    thread5.join();

    auto thread6 = std::move(thread5);  // Move after completion
    thread6.reset([]{ std::cout << "After move reset\n"; });  // Reset the moved-to object
    thread6.start();  // ✅ Should work with custom move constructor
    thread6.join();

    // 5. Member function helper
    std::cout << "Test 5. Member function helper" << std::endl;
    class MyClass {
    public:
        void method(int x) { std::cout << x << '\n'; }
    };
    MyClass obj;
    auto memberThread = utils::threads::makeDeferredMemberThread(&obj, &MyClass::method, 42);
    memberThread.start();

    // 6. Exception cases
    std::cout << "Test 6. Exception cases" << std::endl;
    try {
        thread.start();
        thread.start();  // Should throw
    } catch (const std::logic_error& e) {
        // Expected
    }

//    returns::CStdError myCError;
//    std::cout << "CStdError: ";
//    std::cout << myCError.getErrorAsString() << " " << myCError.getErrorMessage() << " " << myCError.getErrorNumber() << "\n";
//    returns::ApplicationError myAppError;
//    std::cout << "ApplicationError: ";
//    std::cout << myAppError.getErrorAsString() << " " << myAppError.getErrorMessage() << " " << myAppError.getErrorNumber() << "\n";

    return 0;
}
