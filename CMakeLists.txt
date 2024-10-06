cmake_minimum_required(VERSION 3.16)

project(hashing LANGUAGES CXX)
cmake_policy(SET CMP0167 NEW)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_TOOLCHAIN_FILE "path/to/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

find_package(OpenSSL REQUIRED)
find_package(unofficial-argon2 CONFIG REQUIRED)
find_package(cryptopp CONFIG REQUIRED)

add_executable(hashing main.cpp hashing.h)

target_link_libraries(hashing PRIVATE
    cryptopp::cryptopp
    ws2_32
    OpenSSL::SSL
    OpenSSL::Crypto
    Threads::Threads
    unofficial::argon2::libargon2
)

include(GNUInstallDirs)
install(TARGETS hashing
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
