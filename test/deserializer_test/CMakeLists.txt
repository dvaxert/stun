
# Find the dependencies

find_package(GTest REQUIRED)
find_package(Boost REQUIRED)

# Configure test target

add_executable (deserializer_test main.cc deserializer_test.cc)

target_link_libraries (deserializer_test stun testing_utils GTest::GTest GTest::Main Boost::boost)

add_test (
    NAME deserializer_test
    COMMAND $<TARGET_FILE:deserializer_test>
)

if(WIN32)
    set_target_properties(deserializer_test PROPERTIES
        FOLDER Tests
    ) 
endif()