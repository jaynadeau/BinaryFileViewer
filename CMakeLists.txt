cmake_minimum_required(VERSION 3.22)
project(BinaryFileViewer)

set(CMAKE_CXX_STANDARD 20)

add_executable(BinaryFileViewer
               main.cpp
               Application/ApplicationManager.cpp
               Application/ApplicationManager.h
               Returns/Status.h
               Returns/CStdError.cpp
               Returns/CStdError.h
               Application/ApplicationError.cpp
               Application/ApplicationError.h
               Returns/IError.h
               Returns/ErrorBase.cpp
               Returns/ErrorBase.h
               Files/IFile.h
               Utils/ArgParser/ArgParser.cpp
               Utils/ArgParser/ArgParser.h
               Utils/SingletonBase.h
               Configuration/IConfiguration.h
               Configuration/BfvConfiguration.cpp
               Configuration/BfvConfiguration.h
               Utils/ArgParser/ParseError.h
               Utils/ArgParser/ParseError.cpp
               Returns/Expected.h
               Returns/Exceptions/ArgParserException.h
               Application/IApplication.h
               BinaryFileViewerApplication.h
               BinaryFileViewerApplication.cpp
               Utils/Threads/JoinableThread.h
               Utils/Threads/JoinableThread.cpp
               Utils/Threads/DeferredJoinableThread.h
               Application/ApplicationBase.cpp
               Application/ApplicationBase.h
)
