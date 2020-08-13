#include <chrono>
#include <iostream>
#include <memory>

#include "Base.hpp"
#include "Derived1.hpp"
#include "Derived2.hpp"
#include "Pure.hpp"

auto benchmark(auto & ptr, uint iterations) {
  auto start = std::chrono::system_clock::now();
  for (uint i = 0; i < iterations; ++i) {
    ptr->foo();
  }
  auto end = std::chrono::system_clock::now();
  return std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
}

int main(int argc, char** argv) {
  uint iterations = std::stoi(argv[1]);

  std::unique_ptr<Base> base;
  if (argc > 2) {
    base = std::make_unique<Derived1>();
  } else {
    base = std::make_unique<Derived2>();
  }

  auto pure = std::make_unique<Pure>();

  auto durationVirt = benchmark(base, iterations);
  auto durationPure = benchmark(pure, iterations);

  std::cout << "Virtual: " << durationVirt.count()  << " ms\n";
  std::cout << "Pure: " << durationPure.count()  << " ms\n";
  std::cout << "Overhead: " << (static_cast<float>(durationVirt.count()) / durationPure.count() - 1.) * 100 << " %\n";
}