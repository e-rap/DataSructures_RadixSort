#pragma once

#include <string>

/******************************************************************************
 * @class Employee
 * @brief Employee object struct
 *****************************************************************************/
struct Employee
{
  int YearsWithinCompany; ///< number of years the employee has worked
  int BirthYear;          ///< birth year of the employee
  std::string Name;        ///< name of the employee
};