#include <iostream>
#include "Employee.h"
#include "CountingSort.h"
#include "RadixSort.h"
#include "RandomGenerators.h"


// Utility function to return YearsWithinCompany from an employee object
int GetYearsWithinCompany(const Employee& employee)
{
  return employee.YearsWithinCompany;
}

// Utility function to return BirthYear from an employee object
int GetBirthYear(const Employee& employee)
{
  return employee.BirthYear;
}

// Utility function for printing out employees
void PrintEmployees(std::vector<Employee>& employees)
{
  for (auto& employee : employees)
  {
    std::cout << "Birth Year: " << employee.BirthYear << ", ";
    std::cout << "Years Within Company: " << employee.YearsWithinCompany << ", ";
    std::cout << "Name: " << employee.Name << " \n";
  }
}

// Testing Assignment Functions
int main()
{
  const int num_employees{ 20 };
  const int min_years{ 0 };
  const int max_years{ 10 };

  const int min_birth{ 1980 };
  const int max_birth{ 1990 };

  std::vector<Employee> employees{};

  RandomGenerator rg{};

  for (size_t i{ 0 }; i < num_employees; ++i)
  {
    employees.push_back(
      { rg.GetRandomInt(min_years, max_years),
        rg.GetRandomInt(min_birth,max_birth),
        rg.GetRandomName() }
    );
  }

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

  std::vector<Employee> employees2{};
  for (size_t i{ 0 }; i < num_employees; ++i)
  {
    employees2.push_back(
      { rg.GetRandomInt(min_years, max_years),
        rg.GetRandomInt(min_birth,max_birth),
        rg.GetRandomName() }
    );
  }

  std::cout << "\n\n";

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

  // TIME BOTH ALGOS
}
