// PrintStatement.cpp:
#include "PrintAllStatement.h"
using namespace std;

PrintAllStatement::PrintAllStatement()
{}

PrintAllStatement::~PrintAllStatement()
{}

void PrintAllStatement::execute(ProgramState * state, std::ostream &outf)
{
	map<string, int>::iterator it;
	for(it = state -> variables.begin(); it != state -> variables.end(); it++){ 
		outf << it -> first << " " << it -> second << endl;
	}
	state -> programCounter = state -> programCounter + 1;
}
