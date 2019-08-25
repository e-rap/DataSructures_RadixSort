#include <iostream>
#include <algorithm>
#include "Employee.h"
#include "CountingSort.h"
#include "RadixSort.h"
#include "RandomGenerators.h"
#include "ExecutionTime.h"


using EmployeeContainer = std::vector<Employee>;
using Iterator = std::vector<Employee>::iterator;
using CompareFunc = std::function<int(const Employee& a, const Employee& b)>;

/**
 * Utility function to return YearsWithinCompany from an employee object
 * @param employee[in] employee object input
 */
int GetYearsWithinCompany(const Employee& employee)
{
  return employee.YearsWithinCompany;
}

/**
 * Utility function to return BirthYear from an employee object
 * @param employee[in] employee object input
 */
int GetBirthYear(const Employee& employee)
{
  return employee.BirthYear;
}

/**
 * Utility function to print all empolyees within an STL container
 * @param employees[in] STL Container of Employee objects
 */
template<typename Container>
void PrintEmployees(Container& employees)
{
  using DataType = Employee;
  for (auto& employee : employees)
  {
    std::cout << "Birth Year: " << employee.BirthYear << ", ";
    std::cout << "Years Within Company: " << employee.YearsWithinCompany << ", ";
    std::cout << "Name: " << employee.Name << " \n";
  }
}

//class EmployeeComparator
//{
//public:
//  EmployeeComparator(std::function<int(const Employee&)> func)
//    : func(std::move(func))
//  {
//  }
//  bool operator()(const Employee& a, const Employee& b) const
//  {
//    return (func(a) < func(b));
//  }
//private:
//  std::function<int(const Employee&)> func;
//};

template<typename FunctionType>
std::function<int(const Employee& a, const Employee& b)> EmployeeComparator(FunctionType func)
{
  auto comp{ [](const Employee& a, const Employee& b) { return GetBirthYear(a) < GetBirthYear(b); } };
  return comp;
}

/** Main Test Function */
int main()
{


  const int num_employees{ 20 };
  const int min_years{ 0 };
  const int max_years{ 10 };

  const int min_birth{ 1980 };
  const int max_birth{ 1990 };

  EmployeeContainer employees{};

  RandomGenerator rg{};

  /*******************************************
   *              Counting Sort              *
   *******************************************/

   // generate random vector of employees
  for (size_t i{ 0 }; i < num_employees; ++i)
  {
    employees.push_back(
      { rg.GetRandomInt(min_years, max_years),
        rg.GetRandomInt(min_birth,max_birth),
        rg.GetRandomName() }
    );
  }

  std::cout << "___Counting Sort___" << "\n";
  std::cout << "Original Unsorted Input\n";
  PrintEmployees(employees);

  CountingSort(employees, GetYearsWithinCompany);
  std::cout << "\n";
  std::cout << "Sort by Years within company\n";
  PrintEmployees(employees);

  CountingSort(employees, GetBirthYear);
  std::cout << "\n";
  std::cout << "Sort by Birth Years\n";
  PrintEmployees(employees);

  /******************************************
    *              Radix Sort               *
    *****************************************/

    // generate random vector of employees
  employees.clear();
  for (size_t i{ 0 }; i < num_employees; ++i)
  {
    employees.push_back(
      { rg.GetRandomInt(min_years, max_years),
        rg.GetRandomInt(min_birth,max_birth),
        rg.GetRandomName() }
    );
  }

  std::cout << "\n\n";

  std::cout << "___Radix Sort___" << "\n";
  std::cout << "Original Unsorted Input\n";
  PrintEmployees(employees);

  RadixSort(employees, GetYearsWithinCompany);
  std::cout << "\n";
  std::cout << "Sort by Years within company\n";
  PrintEmployees(employees);

  RadixSort(employees, GetBirthYear);
  std::cout << "\n";
  std::cout << "Sort by Birth Years\n";
  PrintEmployees(employees);

  /******************************************
   *         Profile Counting Sort          *
   *****************************************/

  const int num_employees_profile{ 200000 };

  // generate random set of employees 
  employees.clear();
  for (size_t i{ 0 }; i < num_employees_profile; ++i)
  {
    employees.push_back(
      { rg.GetRandomInt(min_years, max_years),
        rg.GetRandomInt(min_birth,max_birth),
        rg.GetRandomName() }
    );
  }

  EmployeeContainer employees2{};
  employees2.resize(num_employees_profile);

  std::copy(employees.begin(), employees.end(), employees2.begin());

  auto birth_year_comp{ EmployeeComparator(GetBirthYear) };
  auto years_employed_comp{ EmployeeComparator(GetYearsWithinCompany) };

  auto count_time{ ProfileFunction(CountingSort<EmployeeContainer>, employees, GetBirthYear) };
  auto stl_time{ ProfileFunction(std::sort<Iterator,CompareFunc>, employees2.begin(),employees2.end(), birth_year_comp) };

  auto count_sorted{ std::is_sorted(employees.cbegin(),employees.cend(),birth_year_comp) };
  auto stl_sorted{ std::is_sorted(employees2.cbegin(), employees2.cend(),birth_year_comp) };

  std::cout << "\n";
  std::cout << "counting sort time: " << count_time << " sorted?: " << count_sorted << "\n";
  std::cout << "std::sort time: " << stl_time << " sorted?: " << stl_sorted << "\n";

  /******************************************
   *           Profile Radix Sort           *
   *****************************************/

  employees.clear();
  for (size_t i{ 0 }; i < num_employees_profile; ++i)
  {
    employees.push_back(
      { rg.GetRandomInt(min_years, max_years),
        rg.GetRandomInt(min_birth,max_birth),
        rg.GetRandomName() }
    );
  }
  employees2.clear();
  employees2.resize(num_employees_profile);
  std::copy(employees.begin(), employees.end(), employees2.begin());

  auto radix_time{ ProfileFunction(CountingSort<EmployeeContainer>, employees, GetBirthYear) };
  stl_time = ProfileFunction(std::sort<Iterator, CompareFunc>, employees2.begin(), employees2.end(), birth_year_comp);

  auto radix_sorted{ std::is_sorted(employees.cbegin(),employees.cend(),birth_year_comp) };
  stl_sorted = std::is_sorted(employees2.cbegin(), employees2.cend(), birth_year_comp);

  std::cout << "\n";
  std::cout << "radix sort time: " << radix_time << " sorted?: " << radix_sorted << "\n";
  std::cout << "std::sort time: " << stl_time << " sorted?: " << stl_sorted << "\n";


}
