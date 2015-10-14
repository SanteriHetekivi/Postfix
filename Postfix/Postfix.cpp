/*
	Santeri Hetekivi (1202466)
	1. harjoitustyö (Postfix-laskin)
	Tietorakenteet ja algoritmit (5G00BD79-3001)
	Tampere University of Applied Sciences (13I224)
	10/2015
*/

#include "Postfix.hpp"



Postfix::Postfix()
{
}


Postfix::~Postfix()
{
}

void Postfix::RUN(bool prompt)
{
	this->prompt = prompt;
	ERROR error = SUCCESS;
	while (error != QUIT)
	{
		error = this->getLine();
		if (error == SUCCESS)
		{
			error = this->CALCULATE();
			if (error == SUCCESS)
			{
				this->PrintResult();
			}
			else this->PrintERROR(error);
		}
		else this->PrintERROR(error);
	}
	
}


ERROR Postfix::getLine()
{	
	std::getline(std::cin, this->line); //Reading line
	return SUCCESS;
}

ERROR Postfix::CALCULATE()
{
	this->NumbersClear();
	ERROR error = SUCCESS;
	std::istringstream iss(this->line); //Setting line to stream
	std::string tmp = "";
	//going trough stream by spaces
	while (iss >> tmp && error == SUCCESS)
	{
		//If string is double
		if (std::atof(tmp.c_str()))
		{
			//Puch it to stack
			this->numbers.push(std::atof(tmp.c_str()));
		}
		else error = this->operate(tmp[0]);
	}

	return error;
}

ERROR Postfix::operate(char tmpOperator)
{
	double tmpResult = 0.00;

	if (tmpOperator == 'q')
	{
		return QUIT;
	}
	else if (tmpOperator == 'x')
	{
		double last = this->numbers.top();
		this->numbers.pop();
		double secondToLast = this->numbers.top();
		this->numbers.pop();
		this->numbers.push(last);
		this->numbers.push(secondToLast);
	}
	else if (tmpOperator == 's')
	{
		while (!this->numbers.empty())
		{
			tmpResult += this->numbers.top();
			this->numbers.pop();
		}
		this->numbers.push(tmpResult);
	}
	else if (tmpOperator == 'a')
	{
		int count = 0;
		while (!this->numbers.empty())
		{
			tmpResult += this->numbers.top();
			this->numbers.pop();
			++count;
		}
		if(count != 0) this->numbers.push(tmpResult / count);
	}
	else
	{
		this->NumbersFlip();
		tmpResult = this->numbers.top();
		if (tmpOperator == 'v')
		{
			if (tmpResult > 1) tmpResult = sqrt(tmpResult);
			else return UNDEFINE;
		}
		else
		{
			while (!this->numbers.empty())
			{
				double number = this->numbers.top();
				switch (tmpOperator)
				{
				case '-':
					tmpResult -= number;
					break;
				case '+':
					tmpResult += number;
					break;
				case '*':
					tmpResult *= number;
					break;
				case '/':
					if (number != 0) tmpResult /= number;
					else return UNDEFINE;
					break;
				case '^':
					tmpResult = pow(tmpResult, number);
					break;
				case '%':
					if (number != 0) tmpResult = fmod(tmpResult, number);
					else return UNDEFINE;
					break;
				default:
					break;
				}
				this->numbers.pop();
			}
		}
		
		this->numbers.push(tmpResult);
	}
	return SUCCESS;
}

void Postfix::PrintResult() const
{
	if(this->prompt)std::cout << "Result:" << this->numbers.top() << std::endl;
	else std::cout << this->numbers.top() << std::endl;
}


void Postfix::NumbersClear()
{
	while (!this->numbers.empty())
	{
		this->numbers.pop();
	}
}
void Postfix::NumbersFlip()
{
	std::stack<double> tmpStack;
	while (!this->numbers.empty())
	{
		tmpStack.push(this->numbers.top());
		this->numbers.pop();
	}
	this->numbers = tmpStack;
}

void Postfix::PrintERROR(ERROR error) const
{
	switch (error)
	{
	case UNDEFINE:
		std::cout << std::endl << "ERROR: Result undefined!" << std::endl;
		break;
	default:
		break;
	}
}