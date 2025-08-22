cmake_minimum_required(VERSION 3.10)
project(feather)

# ---- MODIFY THIS PATH ----
# Point this to where you extracted CEF. It must contain "include" and "libcef_dll_wrapper"
set(CEF_ROOT "C:/cef_binary")

# Add CEF headers
include_directories(${CEF_ROOT}/include)

# Add your source files
file(GLOB_RECURSE SRC_FILES 
    "${PROJECT_SOURCE_DIR}/*.cpp"
    "${PROJECT_SOURCE_DIR}/*.h"
)

add_executable(feather ${SRC_FILES})

# Link to CEF lib
# This assumes CEF lib files are in ${CEF_ROOT}/Release or ${CEF_ROOT}/Debug
if (WIN32)
    set(CEF_LIB "${CEF_ROOT}/Release/libcef.lib")
    if (EXISTS "${CEF_LIB}")
        target_link_libraries(feather "${CEF_LIB}")
    else()
        message(FATAL_ERROR "CEF lib not found at ${CEF_LIB}")
    endif()
endif()

# Copy necessary DLLs (for runtime)
add_custom_command(TARGET feather POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CEF_ROOT}/Release/libcef.dll"
    $<TARGET_FILE_DIR:feather>
)
