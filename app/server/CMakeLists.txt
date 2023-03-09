# Create and configure a client app target

add_executable (stun_server main.cc)
target_link_libraries(stun_server PRIVATE stun)