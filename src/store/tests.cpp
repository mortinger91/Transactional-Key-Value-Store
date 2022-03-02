#include "tests.h"

#include <stack>
#include <vector>

#include "store.h"

namespace Test
{
	void ExecuteAllTests()
	{
		Test1();
		Test2();
		Test3();
		Test4();
		Test5();
		Test6();
	}

	void Test1()
	{
		Store store;
		std::string output;
		ASSERT(1, store.ExecuteOperation(std::string("SET foo 123"), output));
		ASSERT(1, store.ExecuteOperation(std::string("GET foo"), output));
		ASSERT(1, output == "123")
	}

	void Test2()
	{
		Store store;
		std::string output;
		ASSERT(2, store.ExecuteOperation(std::string("DELETE foo"), output));
		ASSERT(2, store.ExecuteOperation(std::string("GET foo"), output));
		ASSERT(2, output == "key not set")
	}

	void Test3()
	{
		Store store;
		std::string output;
		ASSERT(3, store.ExecuteOperation(std::string("SET foo 123"), output));
		ASSERT(3, store.ExecuteOperation(std::string("SET bar 456"), output));
		ASSERT(3, store.ExecuteOperation(std::string("SET baz 123"), output));
		ASSERT(3, store.ExecuteOperation(std::string("COUNT 123"), output));
		ASSERT(3, output == "2")
		ASSERT(3, store.ExecuteOperation(std::string("COUNT 456"), output));
		ASSERT(3, output == "1")
	}

	void Test4()
	{
		Store store;
		std::string output;
		ASSERT(4, store.ExecuteOperation(std::string("BEGIN"), output));
		ASSERT(4, store.ExecuteOperation(std::string("SET foo 456"), output));
		ASSERT(4, store.ExecuteOperation(std::string("COMMIT"), output));
		ASSERT(4, store.ExecuteOperation(std::string("ROLLBACK"), output));
		ASSERT(4, output == "no transaction")
		ASSERT(4, store.ExecuteOperation(std::string("GET foo"), output));
		ASSERT(4, output == "456")
	}

	void Test5()
	{
		Store store;
		std::string output;
		ASSERT(5, store.ExecuteOperation(std::string("SET foo 123"), output));
		ASSERT(5, store.ExecuteOperation(std::string("SET bar abc"), output));
		ASSERT(5, store.ExecuteOperation(std::string("BEGIN"), output));
		ASSERT(5, store.ExecuteOperation(std::string("SET foo 456"), output));
		ASSERT(5, store.ExecuteOperation(std::string("GET foo"), output));
		ASSERT(5, output == "456")
		ASSERT(5, store.ExecuteOperation(std::string("SET bar def"), output));
		ASSERT(5, store.ExecuteOperation(std::string("GET bar"), output));
		ASSERT(5, output == "def")
		ASSERT(5, store.ExecuteOperation(std::string("ROLLBACK"), output));
		ASSERT(5, store.ExecuteOperation(std::string("GET foo"), output));
		ASSERT(5, output == "123")
		ASSERT(5, store.ExecuteOperation(std::string("GET bar"), output));
		ASSERT(5, output == "abc")
		ASSERT(5, store.ExecuteOperation(std::string("COMMIT"), output));
		ASSERT(5, output == "no transaction")
	}

	void Test6()
	{
		Store store;
		std::string output;
		ASSERT(6, store.ExecuteOperation(std::string("SET foo 123"), output));
		ASSERT(6, store.ExecuteOperation(std::string("BEGIN"), output));
		ASSERT(6, store.ExecuteOperation(std::string("SET foo 456"), output));
		ASSERT(6, store.ExecuteOperation(std::string("BEGIN"), output));
		ASSERT(6, store.ExecuteOperation(std::string("SET foo 789"), output));
		ASSERT(6, store.ExecuteOperation(std::string("GET foo"), output));
		ASSERT(6, output == "789")
		ASSERT(6, store.ExecuteOperation(std::string("ROLLBACK"), output));
		ASSERT(6, store.ExecuteOperation(std::string("GET foo"), output));
		ASSERT(6, output == "456")
		ASSERT(6, store.ExecuteOperation(std::string("ROLLBACK"), output));
		ASSERT(6, store.ExecuteOperation(std::string("GET foo"), output));
		ASSERT(6, output == "123")
	}
}
