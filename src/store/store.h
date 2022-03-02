#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <stack>


class Operation
{
public:
	std::string command;
	std::string key;
	std::string value;
	Operation(): 
		command(""), key(""), value("") {}
	Operation(const std::string& _command, const std::string& _key, const std::string& _value): 
		command(_command), key(_key), value(_value) {}
	Operation(const Operation& other):
		command(other.command), key(other.key), value(other.value) {}
	Operation& operator=(const Operation& other) {command = other.command; key = other.key; value = other.value;}
};

class Store
{
private:
	std::unordered_map<std::string, std::string> map;
	std::unordered_map<std::string, int> mapOccurrencies;
	std::stack<std::vector<Operation>> stack;
	int countTransactions;

public:
	Store(): countTransactions(0) {};
	void Launch();
	bool ExecuteOperation(const std::string& input, std::string& output);
private:
	void ExecuteCommand(std::string& output, const Operation& op, const bool saveForRollback = true);
	bool ParseInput(const std::string& input, Operation& op);
	void ExecuteRollback();
};
