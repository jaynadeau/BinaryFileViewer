cmake_minimum_required(VERSION 3.22)
project(BinaryFileViewer)

set(CMAKE_CXX_STANDARD 17)

add_executable(BinaryFileViewer main.cpp Application.cpp Application.h Returns/Status.h Returns/CStdError.cpp Returns/CStdError.h Returns/ApplicationError.cpp Returns/ApplicationError.h Returns/IError.h Returns/ErrorBase.cpp Returns/ErrorBase.h Files/IFile.h Utils/ArgParser.cpp Utils/ArgParser.h Utils/SingletonBase.h Configuration/IConfiguration.h Configuration/BfvConfiguration.cpp Configuration/BfvConfiguration.h Returns/ParseError.h Returns/ParseError.cpp Returns/Expected.h Returns/Exceptions/ArgParserException.h)
