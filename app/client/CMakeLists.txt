# Create and configure a client app target

find_package(Threads REQUIRED)
find_package(Boost REQUIRED)

add_executable (stun_client main.cc)
target_link_libraries(stun_client PRIVATE stun Threads::Threads Boost::boost)