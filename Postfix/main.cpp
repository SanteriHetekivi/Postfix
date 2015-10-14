/*
	Santeri Hetekivi (1202466)
	1. harjoitustyö (Postfix-laskin)
	Tietorakenteet ja algoritmit (5G00BD79-3001)
	Tampere University of Applied Sciences (13I224)
	10/2015
*/
#include "Postfix.hpp"

int main(int argc, char *argv[])
{
	bool prompt = (argc > 1 && argv[1] == "-p");
	Postfix* cal = new Postfix();
	cal->RUN(prompt);
	return 1;
}
