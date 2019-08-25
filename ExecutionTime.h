#pragma once

#include <chrono>


/******************************************************************************
 * calculates the execution time of a function func
 *
 * @param func[in] function under examination
 * @returns execution time in microseconds
 *****************************************************************************/
template<typename Func, typename... Args>
unsigned long long ProfileFunction(Func& func, Args& ... args)
{
  using namespace std::chrono;
  auto t0{ high_resolution_clock::now() };
  func(args...);
  auto t1{ high_resolution_clock::now() };
  return static_cast<unsigned long long>(duration_cast<microseconds>(t1 - t0).count());
}