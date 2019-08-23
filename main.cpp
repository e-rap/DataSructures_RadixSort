#include <iostream>
#include "Employee.h"
#include "CountingSort.h"
#include "RadixSort.h"


int GetYearsWithinCompany(const Employee& employee)
{
  return employee.YearsWithinCompany;
}

int GetBirthYear(const Employee& employee)
{
  return employee.BirthYear;
}

//TODO: Finish
//int GetName(const Employee& employee)
//{
//  return NameToInt(employee.Name);
//}

//int NameToInt(const std::string& name)
//{
//
//}

void CountingSort(std::vector<Employee>& employees, int maxYear)
{
  // I don't use maxYear since CountingSort<T> finds max and min value within the container
  CountingSort(employees, GetBirthYear);
}

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
  std::vector<Employee> employees{{1, 1990, std::string{"Ted"}},
                                  {5, 2001, std::string{"Fred"}},
                                  {3, 2010, std::string{"Eric"}}};

  std::cout << "Before Sort\n";
  PrintEmployees(employees);
  CountingSort(employees, 2010);
  std::cout << "After Sort\n";
  PrintEmployees(employees);
}
