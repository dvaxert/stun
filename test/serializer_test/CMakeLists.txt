
# Find the dependencies

find_package(GTest REQUIRED)
find_package(Boost REQUIRED)

# Configure test target

add_executable (serializer_test main.cc serializer_test.cc)

target_link_libraries (serializer_test stun testing_utils GTest::GTest GTest::Main Boost::boost)

add_test (
    NAME serializer_test
    COMMAND $<TARGET_FILE:serializer_test>
)

if(WIN32)
    set_target_properties(serializer_test PROPERTIES
        FOLDER Tests
    ) 
endif()