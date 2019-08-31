#pragma once

#include <vector>
#include <functional>
#include <algorithm>
#include <tuple>

/******************************************************************************
 * sorts a container of objects by the output of function value_func using the
 * counting sort algorithm
 *
 * Time complexity O(n + m)
 * n = number of objects
 * m = max int value - min int value + 1 (number of mapped values)
 *
 * @param objects[in,out] STL container of objects to be sorted.
 * @param value_func[in] a function which returns int value to be sorted
 *                       from an object within the container objects.
 *****************************************************************************/
template<typename Container>
void CountingSort(Container& objects,
                  const int min_value,
                  const int max_value,
                  std::function<int(const typename Container::value_type&)> value_func)
{
  using DataType = Container::value_type;

  // calculate offset for arbitrary range of values
  int offset{ (min_value >= 0) ? (min_value) : (-min_value) };
  int size{ max_value - offset + 1 };

  // initialize value count vector
  std::vector<int> value_counts{};
  value_counts.resize(size);

  // initialize new_positions vector
  std::vector<DataType> new_order{};
  new_order.resize(objects.size());

  // count occurrences of each value
  for (auto& object : objects)
  {
    int value{ value_func(object) };
    value_counts[static_cast<size_t>(static_cast<size_t>(value - offset))] += 1;
  }

  // accumulate sum with previous elements
  for (size_t i{ 1 }; i < value_counts.size(); ++i)
  {
    value_counts[i] += value_counts[i - 1];
  }

  // move elements to new positions in temp vector
  for (size_t i{ objects.size() }; i > 0; --i)
  {
    size_t j{ i - 1 };
    int value{ value_func(objects[j]) };
    int index{ value - offset };
    new_order[value_counts[index] - 1] = std::move(objects[j]);
    value_counts[index] -= 1;
  }

  // move to original vector
  objects = std::move(new_order);
}