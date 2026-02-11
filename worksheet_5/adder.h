/**
*@file adder.h
*@brief Header file for maths libary addition function.
*/

#ifndef MATHSLIB_ADDER_H
#define MATHSLIB_ADDER_H

#if defined(_WIN32)
  #if defined(maths_STATIC)
    #define MATHSLIB_API
  #else
    #if defined(maths_EXPORTS)
      #define MATHSLIB_API __declspec(dllexport)
    #else
      #define MATHSLIB_API __declspec(dllimport)
    #endif
  #endif
#else
  #define MATHSLIB_API
#endif

/**
*@brief Adds two integers
*@param a First integer
*@param b Second integer
*@return sum of a and b
*/

MATHSLIB_API int add(int a, int b);

#endif
