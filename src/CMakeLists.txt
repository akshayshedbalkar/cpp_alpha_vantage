##Following subdirectories are part of the project
add_subdirectory(stock)
add_subdirectory(api)
add_subdirectory(plot)
add_subdirectory(config)

##All .h files in this directory are to be included
target_include_directories(curl_stocks 
    PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    )

#List here the source files in current directory (Good way to include sources)
target_sources(curl_stocks 
    PRIVATE 
    main.cpp
    )

##All .cpp files in this directory are source files (Quick and dirty way to include sources)
# file(GLOB SOURCES "*.cpp")
# target_sources(curl_stocks PRIVATE ${SOURCES})
