cmake_minimum_required(VERSION 3.20)
project(c++ForComputer)
add_compile_options(-std=c++14)
add_compile_options(-std=-lstdc++)
include_directories(include)
aux_source_directory(src DIR_SRCS)
include_directories(/opt/homebrew/Cellar/boost/1.75.0_2/include)
link_directories(/opt/homebrew/Cellar/boost/1.75.0_2/lib)
set(CMAKE_OSX_SYSROOT /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX11.3.sdk)
set(CMAKE_CXX_STANDARD 14)
add_executable(${PROJECT_NAME} src/utils/utils.cpp src/utils/main.cpp include/utils/utils.h
        include/DataStruct/Array.h include/DataStruct/RBTree.h include/Networks/boostHttp.h
        include/Networks/boostUDPServer.h include/DataStruct/LinkList.h
        include/os/pool.h src/utils/logger.cpp include/utils/logger.h
        include/os/pageSchedule.h include/utils/config.h
        )
target_link_libraries(${PROJECT_NAME} m)