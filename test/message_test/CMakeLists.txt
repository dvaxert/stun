
# Find the dependencies

find_package(GTest REQUIRED)
find_package(Boost REQUIRED)

# Configure test target

add_executable (message_test 
    main.cc 
    binding_request.cc
    binding_response.cc
    binding_error_response.cc
    shared_secret_request.cc
    shared_secret_response.cc
    shared_secret_error_response.cc
)

target_link_libraries (message_test stun testing_utils GTest::GTest GTest::Main Boost::boost)

add_test (
    NAME message_test
    COMMAND $<TARGET_FILE:message_test>
)

if(WIN32)
    set_target_properties(message_test PROPERTIES
        FOLDER Tests
    ) 
endif()