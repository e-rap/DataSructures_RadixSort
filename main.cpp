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

/**
 * creates a compare function for employee objects based on
 * the output of the value function
 *
 * @param value_func[in] function to return value to compare by
 * @returns compare function of type CompareFunc
 */
template<typename ValueFunc>
CompareFunc EmployeeComparator(ValueFunc value_func)
{
  auto compare_func{ [](const Employee& a, const Employee& b)
  {
    return GetBirthYear(a) < GetBirthYear(b);
  } };
  return compare_func;
}

/** Main Test Function */
int main()
{

  /* Constants */
  const int num_employees{ 20 };
  const int min_years{ 0 };
  const int max_years{ 10 };
  const int min_birth{ 1980 };
  const int max_birth{ 1990 };


  RandomGenerator rg{};

  /*******************************************
   *              Counting Sort              *
   *******************************************/

   // generate random vector of employees
  EmployeeContainer employees{};
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

  // Answers for questions about counting sort
  std::cout << "\n";
  std::cout << "Which sorting algorithm is more efficient in this case?\n\n";
  std::cout << "std::sort is more efficent, counting sort is not because of the range of birth year values (0 to 1990).\n";
  std::cout << "However, my implementation of counting sort utilizes only the range between max and min birth years for\n";
  std::cout << "all employees. therefore with a max year of 1990 and min year of 1980 only 10 values are mapped instead\n";
  std::cout << "of 1991 values\n";
  std::cout << "\n";

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

  // Answers for questions about radix sort
  std::cout << "\n";
  std::cout << "Which sorting algorithm is more efficient in this case?\n\n";
  std::cout << "std::sort is more efficent, my implmentation of radix sort is not as fast.\n";
  std::cout << "if you compare radix sort vs counting sort, radix sort is still techincally slower because the overhead\n";
  std::cout << "of sortingeach digit within the birth year. Since my counting sort maps 1980 to 1990 with 10 values, it is faster\n";
  std::cout << "differnce in speed should be:\n";
  std::cout << "CountingSort = O(n + m) where m is the number of mapped values and n is the number of employees.\n";
  std::cout << "RadixSort = O(d * (n + m)) where m is the number of mapped values, n is the number of employees\n";
  std::cout << "and d is the number of digits within the value sorted\n";
  std::cout << "therefore, CountingSort = O(200,011) | RadixSort = O(4*(200,009) = O(800,036)\n";
  std::cout << "Counting Sort is faster in my case";
  std::cout << "However, my implementation of counting sort utilizes only the range between max and min birth years for\n";
  std::cout << "all employees. therefore with a max year of 1990 and min year of 1980 only 10 values are mapped instead\n";
  std::cout << "of 1991 values\n";
  std::cout << "\n";

}
