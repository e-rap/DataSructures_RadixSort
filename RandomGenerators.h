#pragma once

#include <random>
#include <string>
#include <array>

/**
 * Generates random integers and names
 */
class RandomGenerator
{
public:
  RandomGenerator();
  virtual ~RandomGenerator() = default;
  /**
   * returns a random integer within the range [min,max]
   * @param min[in] minimum integer value
   * @param max[in] maximum integer value
   */

  int GetRandomInt(int min, int max);
  /**
   * returns a random name
   */
  std::string GetRandomName();

private:
  std::mt19937 gen;                          ///< random generator
  static std::array<std::string, 100> names; ///< array of possible names

};