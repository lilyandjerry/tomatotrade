PROJECT(tomatotrade)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
INCLUDE_DIRECTORIES("/usr/include")
INCLUDE_DIRECTORIES("ctpinterface")

LINK_DIRECTORIES("/usr/lib/")

AUX_SOURCE_DIRECTORY(. DIR_SRCS)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin)
add_executable(tomatotrade  ${DIR_SRCS})
TARGET_LINK_LIBRARIES(tomatotrade thostmduserapi.so thosttraderapi.so)