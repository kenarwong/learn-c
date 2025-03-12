#include <iostream>

int count() {
    static int x = 0; // only accessible here, but persists
    return ++x;
}

int main() {
  std::cout << count() << std::endl;
  std::cout << count() << std::endl;
  std::cout << count() << std::endl;

  return 0;
}
