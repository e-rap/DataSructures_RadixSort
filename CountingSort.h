#pragma once

#include <string>
#include <vector>

using Year = int;

struct Employee
{
  int YearsWithinCompany;
  int BirthYear;
  std::string Name;
};

template <typename DataType>
class ISpecification
{
public:
  virtual bool is_satisfied(DataType *Item){};
};

template <typename ObjectType, typename OutputType>
class IFilter
{
public:
  virtual std::vector<OutputType> filter(
      std::vector<ObjectType> &items = 0;
};

class YearsWithinCompanyFilter : IFilter<Employee, Year>
{
public:
  typedef std::vector<Employee> Employees;
  typedef std::vector<Year> Years;
  Years filter(Employees &items) override
  {
    Years result;
    for (auto &p : items)
    {
      result.push_back(p.YearsWithinCompany);
      return result;
    }
  }
};

// class YearsWithinCompanySpec : ISpecification<Employee>
// {
// private:
//   Year years_within_company;

// public:
//   explicit YearsWithinCompanySpec(const Year years_within_company)
//       : years_within_company{years_within_company} {}
//   bool is_satisfied(Employee *item) override
//   {
//     return item->YearsWithinCompany == years_within_company;
//   }
// };

// class BirthYearSpec : ISpecification<Employee>
// {
// private:
//   Year birth_year;

// public:
//   explicit BirthYearSpec(const Year birth_year)
//       : birth_year{birth_year} {}
//   bool is_satisfied(Employee *item) override
//   {
//     return item->BirthYear == birth_year;
//   }
// };

// class NameSpec : ISpecification<Employee>
// {
// private:
//   std::string name;

// public:
//   explicit NameSpec(const std::string name)
//       : name{name} {}
//   bool is_satisfied(Employee *item) override
//   {
//     return item->Name == name;
//   }
// };

void CountingSort(std::vector<int> container, int min_value, int max_value)
{
  // calculate offset for arbitrary range of values
  int offset{(min_value >= 0) ? (min_value) : (-min_value)};
  int size{max_value - offset};

  std::vector<int> count{};
  count.resize(size);

  // count occurrences of each value
  for (auto &value : container)
  {
    count[value - offset] += 1;
  }

  // sum with previous elements
  for (size_t i{1}; i <= container.size(); ++i)
  {
    count[i] += count[i - 1];
  }
}

void CountingSort(std::vector<Employee> employees, int maxYear)
{
  YearsWithinCompanyFilter yf;
  auto years_array = yf.filter(employees);
  CountingSort(years_array, 1990, 2020);
}
