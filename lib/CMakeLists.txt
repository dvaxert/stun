# Create and configure a library target

# Find the dependencies

find_package(Boost REQUIRED)

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

target_link_libraries(stun 
    PRIVATE
        Boost::boost
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