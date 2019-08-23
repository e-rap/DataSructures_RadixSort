#include "CountingSort.h"
#include <tuple>


int GetYearsWithinCompany(const Employee& employee)
{
  return employee.YearsWithinCompany;
}

void CountingSort(std::vector<Employee>& employees, int maxYear)
{
  // I don't use maxYear since CountingSort<T> finds max and min value within the container
  CountingSort(employees, GetYearsWithinCompany);
}