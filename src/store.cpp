#include "store.h"

#include <iostream>
#include "utility.h"
#include "tests.h"

//SET <key> <value> // store the value for key
//GET <key>         // return the current value for key
//DELETE <key>      // remove the entry for key
//COUNT <value>     // return the number of keys that have the given value
//BEGIN             // start a new transaction
//COMMIT            // complete the current transaction
//ROLLBACK          // revert to state prior to BEGIN call 

void Store::Launch() 
{
	std::cout << "Lauched store!" << std::endl << "Insert commands:" << std::endl;

	while(true)
	{
		std::string input;
		std::string output;
		getline(std::cin, input);

		if (input == "test")
		{
			Test::ExecuteAllTests();
		}
		else
		{
			if (!ExecuteOperation(input, output))
			{
				std::cout << "Invalid command" << std::endl;
			}
			else
			{
				if (output != "") std::cout << output << std::endl;
			}
		}
	}
}

bool Store::ExecuteOperation(std::string& input, std::string& output)
{
	Operation op;
	if (!ParseInput(input, op))
	{
		return false;
	}
	else
	{
		ExecuteCommand(output, op);
	}
	return true;
}

// check if the input is valid, return false if it is not
bool Store::ParseInput(std::string& input, Operation& op)
{
	#ifdef DEBUG
		std::cout << "Received input: " << input << std::endl;
	#endif

	std::vector<std::string> inputSplit = Utility::SplitString(input, " ");
	op.command = "";
	op.key = "";
	op.value = "";
	if (inputSplit.size() < 1 || inputSplit.size() > 3)
	{
		return false;
	}

	op.command = inputSplit[0];
	Utility::StringToUpper(op.command);
		
	if (op.command == "BEGIN" || op.command == "COMMIT" || op.command == "ROLLBACK")
	{
		if (inputSplit.size() != 1)
		{
			return false;
		}
	}
	else if (op.command == "GET" || op.command == "DELETE" || op.command == "COUNT")
	{
		if (inputSplit.size() != 2)
		{
			return false;
		}
		if (op.command == "COUNT")
		{
			op.value = inputSplit[1];
		}
		else
		{
			op.key = inputSplit[1];
		}
	}
	else if (op.command == "SET")
	{
		if (inputSplit.size() != 3)
		{
			return false;
		}
		op.key = inputSplit[1];
		op.value = inputSplit[2];
	}
	else
	{
		return false;
	}

	#ifdef DEBUG
		std::cout << "Command: " << op.command << std::endl;
		if (op.key != "") 
			std::cout << "Key: " << op.key << std::endl;
		if (op.value != "") 
			std::cout << "Value: " << op.value << std::endl;
	#endif

	return true;
}

void Store::ExecuteCommand(std::string& output, const Operation& op, const bool saveForRollback)
{
	// commands that write the map
	if (op.command == "SET")
	{
		if (countTransactions > 0 && saveForRollback)
		{
			Operation opBackup("SET", op.key, map[op.key]);
			stack.top().push_back(opBackup);
		}

		if (map[op.key]!= "") mapOccurrencies[map[op.key]]--;
		mapOccurrencies[op.value]++;

		map[op.key] = op.value;
	}
	else if (op.command == "DELETE")
	{
		if (countTransactions > 0 && saveForRollback)
		{
			Operation opBackup("SET", op.key, map[op.key]);
			stack.top().push_back(opBackup);
		}

		mapOccurrencies[map[op.key]]--;
		
		map.erase (op.key);
	}
	// commands that read the map
	else if (op.command == "GET")
	{
		std::string value = map[op.key];
		output = (value == "") ? "key not set" : value;
	}
	else if (op.command == "COUNT")
	{
		std::string value = std::to_string(mapOccurrencies[op.value]);
		output = value;
	}
	// commands for the transactions
	else if (op.command == "BEGIN")
	{
		countTransactions++;
		std::vector<Operation> vec;
		stack.push(std::move(vec));
	}
	else if (op.command == "COMMIT")
	{
		if (countTransactions > 0)
		{
			countTransactions--;
			stack.pop();
		}
		else
		{
			output = "no transaction";
		}
	}
	else if (op.command == "ROLLBACK")
	{
		if (countTransactions > 0)
		{
			countTransactions--;
			ExecuteRollback();
		}
		else
		{
			output = "no transaction";
		}
	}
}

void Store::ExecuteRollback()
{
	std::string output;
	for (int i = stack.top().size()-1; i >= 0; i--)
	{
		ExecuteCommand(output, stack.top()[i], false);
	}

	stack.pop();
}
