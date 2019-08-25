#pragma once

#include <random>
#include <string>
#include <array>
class RandomGenerator
{
public:
  RandomGenerator();
  virtual ~RandomGenerator() = default;

  int GetRandomInt(int min, int max);
  std::string GetRandomName();

private:
  std::mt19937 gen;

  static std::array<std::string, 100> names;

};