#pragma once

#include <vector>
#include <functional>
#include <algorithm>

template<typename Container>
void CountingSort(Container& employees, std::function<int(const typename Container::value_type&)> value_func)
{
  using DataType = Container::value_type;
  // find the minimum and maximum value of the employees
  auto comp{ [value_func](const DataType& a, const DataType& b) {return value_func(a) < value_func(b); } };
  auto min_max_iters{ std::minmax_element(employees.cbegin(), employees.cend(), comp) };
  auto min_value = value_func(*min_max_iters.first);
  auto max_value = value_func(*min_max_iters.second);

  // calculate offset for arbitrary range of values
  int offset{ (min_value >= 0) ? (min_value) : (-min_value) };
  int size{ max_value - offset + 1 };

  // initialize value count vector
  std::vector<int> value_counts{};
  value_counts.resize(size);

  // initialize new_positions vector
  std::vector<size_t> new_positions{};
  new_positions.resize(employees.size());

  // count occurrences of each value
  for (auto& employee : employees)
  {
    auto value = value_func(employee);
    value_counts[value - offset] += 1;
  }

  // accumulate sum with previous elements
  for (size_t i{ 1 }; i < value_counts.size(); ++i)
  {
    value_counts[i] += value_counts[i - 1];
  }

  //shift all elements to the right
  std::rotate(value_counts.rbegin(), value_counts.rbegin() + 1, value_counts.rend());
  value_counts[0] = 0;

  // find new positions for original employees
  for (size_t i{ 0 }; i < employees.size(); ++i)
  {
    auto value = value_func(employees[i]);
    auto index = value_counts[value - offset];
    value_counts[value - offset] += 1;
    new_positions[i] = index;
  }

  // update employees with new positions
  for (size_t i{ 0 }; i < employees.size(); ++i)
  {
    auto new_i = new_positions[i];
    std::swap(employees[i], employees[new_i]);
    std::swap(new_positions[i], new_positions[new_i]);
  }
}

//template<typename Container>
//void CountingSort(Container& employees);

//template<typename Container>
//void CountingSort(Container& employees)
//{
//  CountingSort(employees, [](const typename Container::value_type & val) {return val; };)
//}