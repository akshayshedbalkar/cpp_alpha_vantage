cmake_minimum_required(VERSION 3.13)

##Project name and type
project(curl_stocks)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_INCLUDES OFF)

find_package(Boost COMPONENTS filesystem system iostreams)

##Define executables, libraries here with relative path
add_executable(curl_stocks src/main.cpp)

##Subdirectories which are part of the project
add_subdirectory(src)
add_subdirectory(extern)

##Compiler defines, options and features
target_compile_features(curl_stocks 
    PRIVATE 
        cxx_std_20
)

##Linker options, external libraries/objects to link against
target_link_libraries(curl_stocks 
     PRIVATE 
     ${CMAKE_CURRENT_SOURCE_DIR}/extern/lib/libcurl.a
     ${CMAKE_CURRENT_SOURCE_DIR}/extern/lib/libcurl.dll.a
     ${CMAKE_CURRENT_SOURCE_DIR}/extern/lib/libutility.a
     Boost::filesystem 
     Boost::system
     Boost::iostreams
 )

##Set target properties
set_target_properties(curl_stocks
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)


add_custom_command(TARGET curl_stocks POST_BUILD        
    COMMAND ${CMAKE_COMMAND} -E copy_if_different  
        "${PROJECT_SOURCE_DIR}/extern/lib/libcurl-x64.dll"      
        $<TARGET_FILE_DIR:curl_stocks>)                 
