cmake_minimum_required(VERSION 3.13)

##Project name and type
project(curl_stocks)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_INCLUDES OFF)
set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE include-what-you-use)

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
target_compile_options(curl_stocks
    PRIVATE
    -O3
    # -fsanitize=address
    # -fsanitize=undefined
    )

##Linker options, external libraries/objects to link against
find_package(Boost COMPONENTS filesystem system iostreams)
target_link_libraries(curl_stocks 
    PRIVATE
    Boost::filesystem 
    Boost::system
    Boost::iostreams
    )

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    target_link_libraries(curl_stocks 
        PRIVATE 
        -lcurl
        # -fsanitize=address
        # -fsanitize=undefined
        )
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    target_link_libraries(curl_stocks 
        PRIVATE
        ${CMAKE_SOURCE_DIR}/extern/lib/libcurl.a
        ${CMAKE_SOURCE_DIR}/extern/lib/libcurl.dll.a
        ${CMAKE_SOURCE_DIR}/extern/lib/libutility.a
        )
endif()

##Set target properties
set_target_properties(curl_stocks
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    )

#Copy required files to binary directory
add_custom_command(TARGET curl_stocks POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink
    "${CMAKE_SOURCE_DIR}/stocks.config"
    "${CMAKE_BINARY_DIR}/bin/stocks.config")

add_custom_command(TARGET curl_stocks POST_BUILD        
    COMMAND ${CMAKE_COMMAND} -E copy_if_different  
    "${CMAKE_SOURCE_DIR}/extern/lib/libcurl-x64.dll"      
    $<TARGET_FILE_DIR:curl_stocks>)                 

#Doxygen configuration
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(DOXYGEN_HTML_OUTPUT  "${CMAKE_SOURCE_DIR}/docs")
    set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "README.md")
    set(DOXYGEN_HAVE_DOT "YES")
    set(DOXYGEN_CALL_GRAPH "YES")
    set(DOXYGEN_CALLER_GRAPH "YES")
    doxygen_add_docs(
        doc
        ${CMAKE_SOURCE_DIR}
        )
endif()
