
# Find the dependencies

find_package(Boost REQUIRED)

# Configure test target

NestingFileSearch (STUN_TESTING_UTILS_HEADERS
    EXTENSIONS ".h"
    DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

NestingFileSearch (STUN_TESTING_UTILS_SOURCES
    EXTENSIONS ".cc"
    DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

add_library (testing_utils STATIC)

target_sources(testing_utils
    PRIVATE
        ${STUN_TESTING_UTILS_HEADERS}
        ${STUN_TESTING_UTILS_SOURCES}
)

target_include_directories(testing_utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries (testing_utils stun Boost::boost)


if(WIN32)
    set_target_properties(testing_utils PROPERTIES
        FOLDER Tests
    ) 
endif()