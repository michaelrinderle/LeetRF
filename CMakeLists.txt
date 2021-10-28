cmake_minimum_required (VERSION 3.8)
project (leetrf)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_TOOLCHAIN_FILE "c:/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(DCMAKE_TOOLCHAIN_FILE "c:/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(VCPKG_TARGET_TRIPLET x64-windows)

set(Boost_INCLUDE_DIR "C:/vcpkg/installed/x64-windows/include")

option (enable-wasapi "compile Windows WASAPI support (if it is available)" on )


add_subdirectory ("src")
add_subdirectory("test")

add_subdirectory("external/gtest")


