#pragma once

#include <iostream>
#include <string>

#define ASSERT(testName,x) if(!(x)) \
		{ std::cout << "FAILED TEST:" << std::to_string(testName) << std::endl; } \
		else \
		{ std::cout << "PASSED TEST:" << std::to_string(testName) << std::endl; }

namespace Test
{
	void ExecuteAllTests();
	void Test1();
	void Test2();
	void Test3();
	void Test4();
	void Test5();
	void Test6();
}
