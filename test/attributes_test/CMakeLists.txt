
# Find the dependencies

find_package(GTest REQUIRED)
find_package(Boost REQUIRED)

# Configure test target

add_executable (attributes_test
    main.cc
    change_request.cc
    changed_address.cc
    error_code.cc
    mapped_address.cc
    message_integrity.cc
    password.cc
    reflected_from.cc
    response_address.cc
    source_address.cc
    unknown_attributes.cc
    username.cc
)

target_link_libraries (attributes_test stun testing_utils GTest::GTest GTest::Main Boost::boost)

add_test (
    NAME attributes_test
    COMMAND $<TARGET_FILE:attributes_test>
)

if(WIN32)
    set_target_properties(attributes_test PROPERTIES
        FOLDER Tests
    ) 
endif()