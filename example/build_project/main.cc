#include <wormhole/wormhole.h>

#include <iostream>

int main() {
  wh::TestBuild tb{};

  std::cout << tb.TestFunc() << std::endl;

  return 0;
}
