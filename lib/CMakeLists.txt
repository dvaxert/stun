# Create and configure a library target

# Find the dependencies

find_package(Boost REQUIRED)
find_package(Fmt REQUIRED)      # TODO std 20
find_package(spdlog REQUIRED)

# Define the library type
if (STUN_BUILD_SHARED_LIBS)
    set (STUN_LIBRARY_TYPE SHARED)
else ()
    set (STUN_LIBRARY_TYPE STATIC)
endif ()

add_library (stun ${STUN_LIBRARY_TYPE})
add_library (wh::stun ALIAS stun)
message (STATUS "STUN_LIBRARY_TYPE - ${STUN_LIBRARY_TYPE}")

# Describing the list of source files

NestingFileSearch (STUN_HEADERS
    RECURSIVE
    EXTENSIONS ".h"
    DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

NestingFileSearch (STUN_SOURCES
    RECURSIVE
    EXTENSIONS ".cc"
    DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_sources(stun
    PUBLIC 
        ${STUN_HEADERS}
    PRIVATE
        ${STUN_SOURCES}
)

target_include_directories(stun
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

unset (STUN_ADDITIONAL_LIBRARIES)
if (WIN32)
    set(STUN_ADDITIONAL_LIBRARIES iphlpapi ws2_32)
endif()

target_link_libraries(stun 
    PRIVATE
        Boost::boost
        fmt::fmt        # TODO std 20
        spdlog::spdlog
        ${STUN_ADDITIONAL_LIBRARIES}
)

foreach(HEADER ${STUN_HEADERS})
    set_target_properties(stun
        PROPERTIES
            PUBLIC_HEADER ${HEADER}
    )
endforeach()

# Create an installation target

if(STUN_INSTALL)

    install(
        TARGETS stun
        EXPORT stun-targets
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_BINDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/stun
    )

endif()