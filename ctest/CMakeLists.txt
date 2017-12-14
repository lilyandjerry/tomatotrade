PROJECT(apitest)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
INCLUDE_DIRECTORIES("/usr/include")
INCLUDE_DIRECTORIES("/usr/include/python2.7/")
INCLUDE_DIRECTORIES("../ctpinterface")

LINK_DIRECTORIES("/usr/lib/")

AUX_SOURCE_DIRECTORY(. DIR_SRCS)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./../bin)
SET(LIBRARY_OUTPUT_PATH ./../)
add_executable(apitest ${DIR_SRCS})
TARGET_LINK_LIBRARIES(apitest -lpython2.7 libthostmduserapi.so libthosttraderapi.so libtomatotrade.so )
