#include "Application/ApplicationManager.h"
#include "BinaryFileViewerApplication.h"
#include "Returns/Exceptions/ArgParserException.h"
#include "Utils/ArgParser/ArgParser.h"
#include "Utils/Threads/DeferredJoinableThread.h"


#include <iostream>
#include <string>

using namespace bfv;

int main(int argc, char* argv[])
{
    std::cout << "Welcome to the binary file viewer app." << std::endl;
//    static ApplicationManager& app = ApplicationManager::getInstance();
    auto result = utils::ArgParser().addString("--input_filename", true, "Input file path")
        .addString("--output_type", true, "Output format")
        .addString("--output_filename", false, "Output file path", "output.txt")
        .parseAndApply(argc, argv,
              "--input_filename",
              "--output_type",
              "--output_filename");

    if (!result) {
        std::cerr << result.error().getErrorAsString() << std::endl;
        return 1;
    }
    auto [inputFilename, outputType, outputFilename] = *result;
    BinaryFileViewerApplication app{inputFilename, outputType, outputFilename};
    app.start();
    // parser.addArgument("--input_filename", true, false, "Path to the binary file to be viewed.", utils::ArgParser::TYPE::STRING);
    // parser.addArgument("--output_filename", false, false, "Path to the output text file to convert the binary file to.", utils::ArgParser::TYPE::STRING);
    // parser.addArgument("--output_type", true, false, "The format to output/interpret the binary file as. Can be one of [UINT8_T, UINT16_T, UINT32_T, INT8_T, INT16_T, INT32_T, FLOAT32, HEX, CHAR, BINARY]", utils::ArgParser::TYPE::STRING);

    // utils::ArgParser::ExpectedNamedArguments args = parser.Parse(argc, argv);
    // if (args.has_value()) {
    //     for(const auto&[fst, snd] : args.value())
    //     {
    //         std::cout << "Argument name: " << fst << " Argument value: " << snd.value.get<std::string>().value()
    //         << " Argument type: " << static_cast<int>(snd.type) << std::endl;
    //
    //         std::cout << std::endl;
    //     }
    //     // utils::ArgParser::NamedArguments namedArgs = args.value();
    //     BinaryFileViewerApplication app{args.value()["--input_filename"].value.get<std::string>().value(), args.value()["--output_type"].value.get<std::string>().value(), args.value()["--output_filename"].value.get<std::string>().value()};
    //     app.start();
    // }
    // else {
    //     std::cout << "Parsing error has occurred: " << args.error().getErrorAsString() << std::endl;
    // }



    // std::cout << "Testing JoinableThread class..." << std::endl;


    // // 1. Basic usage
    // std::cout << "Test 1. Basic usage" << std::endl;
    // utils::threads::DeferredJoinableThread thread([]{ std::cout << "Hello\n"; });
    // thread.start();
    // thread.join();
    //
    // // 2. Reset after completion
    // std::cout << "Test 2. Reset after completion" << std::endl;
    // thread.reset([]{ std::cout << "World\n"; });
    // thread.start();
    // thread.join();
    //
    // // 3. Move semantics - move BEFORE starting
    // utils::threads::DeferredJoinableThread thread3([]{ std::cout << "Move before start\n"; });
    // auto thread4 = std::move(thread3);  // Move before start
    // thread4.start();  // ✅ Works - start the moved-to object
    // thread4.join();
    //
    // // 4. Move semantics - move AFTER completion
    // utils::threads::DeferredJoinableThread thread5([]{ std::cout << "Move after complete\n"; });
    // thread5.start();
    // thread5.join();
    //
    // auto thread6 = std::move(thread5);  // Move after completion
    // thread6.reset([]{ std::cout << "After move reset\n"; });  // Reset the moved-to object
    // thread6.start();  // ✅ Should work with custom move constructor
    // thread6.join();
    //
    // 5. Member function helper
    // std::cout << "Test 5. Member function helper" << std::endl;
    // class MyClass {
    // public:
    //     void method(int x) { std::cout << x << '\n'; }
    // };
    // MyClass obj;
    // auto memberThread = utils::threads::makeDeferredMemberThread(&obj, &MyClass::method, 42);
    // memberThread.start();

    std::cout << "Test 6. Member function helper but thread also member" << std::endl;
    class MyClass {
    public:
        MyClass() {
            mMainThread = utils::threads::makeDeferredMemberThread(this, &MyClass::method, 42);
        }
        void method(int x) { std::cout << x << '\n'; }
        void start() { mMainThread.start(); }
    private:
        utils::threads::DeferredJoinableThread mMainThread;
    };
    MyClass obj;
    obj.start();

    //
    // // 7. Exception cases
    // std::cout << "Test 7. Exception cases" << std::endl;
    // try {
    //     thread.start();
    //     thread.start();  // Should throw
    // } catch (const std::logic_error& e) {
    //     // Expected
    // }




    return 0;
}
