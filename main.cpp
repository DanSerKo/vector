#include "vector.h"

#include <iostream>
#include <string>

int main() {
  Vector<std::string> a = {"1kdfsj", "kjdjkf"};
  for (int i = 0; i < a.Size(); i++) {
    std::cout << a[i] << std::endl;
  }
  a.Clear();
  a.PushBack("2048");
  a.PushBack("2047");
  // a.Resize(10);
  a.PushBack("1a");
  a.PushBack("b");
  a.PopBack();
  a.PushBack("1");
  for (int i = 0; i < a.Size(); i++) {
    std::cout << a[i] << std::endl;
  }
}
