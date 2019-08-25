#include <iostream>
#include "Employee.h"
#include "CountingSort.h"
#include "RadixSort.h"
#include "RandomGenerators.h"


// Return YearsWithinCompany for an employee object
int GetYearsWithinCompany(const Employee& employee)
{
  return employee.YearsWithinCompany;
}

// Returns BirthYear for an employee object
int GetBirthYear(const Employee& employee)
{
  return employee.BirthYear;
}

// Counting Sort function specified in the assignment
// Calls overloaded counting sort template functiion and sorts by Birth Year
// Time complexity is O(n + k) where n is the number of employees 
// and k is (max birth year - min birth year + 1)
void CountingSort(std::vector<Employee>& employees, int maxYear)
{
  // I don't use maxYear since CountingSort<T> finds max and min value within the container
  CountingSort(employees, GetYearsWithinCompany);
}

//void CountingSort(std::vector<Employee>& employees, int maxBirthYear)
//{
//  CountingSort(employees, GetYearsWithinCompany);
//}

void PrintEmployees(std::vector<Employee>& employees)
{
  for (auto& employee : employees)
  {
    std::cout << "Birth Year: " << employee.BirthYear << ", ";
    std::cout << "Years Within Company: " << employee.YearsWithinCompany << ", ";
    std::cout << "Name: " << employee.Name << " \n";
  }
}

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

  std::cout << "Before Sort by Years within company \n";
  PrintEmployees(employees);
  CountingSort(employees, GetYearsWithinCompany);
  std::cout << "\n";
  std::cout << "After Sort by Years within company\n";
  PrintEmployees(employees);

  CountingSort(employees, GetBirthYear);
  std::cout << "\n";
  std::cout << "After Sort by Years within company\n";
  PrintEmployees(employees);

  // TIME BOTH ALGOS
}
