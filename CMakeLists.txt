cmake_minimum_required(VERSION 3.23)

set(PATCH_VERSION "1" CACHE STRING "Patch version provided by GitHub")

project(containers
    VERSION 1.0.${PATCH_VERSION}
    LANGUAGES CXX)

add_executable(containers
    src/main.cpp)

target_include_directories(containers PRIVATE
    include)

set_target_properties(containers PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

set(CPACK_PACKAGE_NAME "containers")
set(CPACK_PACKAGE_VENDOR "nom4")
set(CPACK_PACKAGE_CONTACT "nom4@tpu.ru")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Containers C++ application")

if(APPLE)
    set(CPACK_GENERATOR "DragNDrop")
elseif(UNIX)
    set(CPACK_GENERATOR "DEB")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "nom4@tpu.ru")
endif()

include(CPack)