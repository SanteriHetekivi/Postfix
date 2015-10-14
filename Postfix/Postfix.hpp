/*	
	Santeri Hetekivi (1202466)
	1. harjoitustyö (Postfix-laskin)
	Tietorakenteet ja algoritmit (5G00BD79-3001)
	Tampere University of Applied Sciences (13I224)
	10/2015
*/
#ifndef POSTFIX_HPP
#define POSTFIX_HPP

#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <cmath>


struct Calculation
{
	std::queue<double> numbers;
	std::queue<char> actions;
};

enum ERROR
{
	SUCCESS,
	QUIT,
	UNDEFINE,
};

class Postfix
{
public:
	void RUN(bool prompt = false);
	Postfix();
	virtual ~Postfix();
private:
	ERROR getLine();
	ERROR CALCULATE();
	ERROR operate(char);
	void PrintResult() const;
	void NumbersFlip();
	void NumbersClear();
	void PrintERROR(ERROR) const;
	std::stack<double> numbers;
	std::string line;
	bool prompt = false;
};
#endif
