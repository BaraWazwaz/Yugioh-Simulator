cmake_minimum_required(VERSION 3.19) # Required for advanced JSON features
project(MyProgram CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/dist)

include(FetchContent)

if(EXISTS "${CMAKE_SOURCE_DIR}/packages.json")
    file(READ "${CMAKE_SOURCE_DIR}/packages.json" JSON_DATA)

    string(JSON DEPS_LENGTH LENGTH "${JSON_DATA}" "dependencies")
    math(EXPR LOOP_MAX "${DEPS_LENGTH} - 1")

    set(DEPENDENCY_TARGETS "")

    foreach(INDEX RANGE ${LOOP_MAX})
        string(JSON DEP_NAME GET "${JSON_DATA}" "dependencies" ${INDEX} "name")
        string(JSON DEP_URL  GET "${JSON_DATA}" "dependencies" ${INDEX} "url")
        string(JSON DEP_TAG  GET "${JSON_DATA}" "dependencies" ${INDEX} "tag")

        FetchContent_Declare(
            ${DEP_NAME}
            GIT_REPOSITORY ${DEP_URL}
            GIT_TAG        ${DEP_TAG}
        )
        FetchContent_MakeAvailable(${DEP_NAME})
        
        list(APPEND DEPENDENCY_TARGETS ${DEP_NAME})
    endforeach()
else()
    message(FATAL_ERROR "packages.json file not found in root directory!")
endif()

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.hpp")

add_executable(program ${SOURCES} ${HEADERS})
target_include_directories(program PRIVATE include)

foreach(DEP IN LISTS DEPENDENCY_TARGETS)
    if(DEP STREQUAL "json")
        target_link_libraries(program PRIVATE nlohmann_json::nlohmann_json)
    elseif(DEP STREQUAL "fmt")
        target_link_libraries(program PRIVATE fmt::fmt)
    else()
        target_link_libraries(program PRIVATE ${DEP})
    endif()
endforeach()
