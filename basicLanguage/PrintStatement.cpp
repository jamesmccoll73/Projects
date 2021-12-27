// PrintStatement.cpp:
#include "PrintStatement.h"
using namespace std;

PrintStatement::PrintStatement(std::string variableName)
	: m_variableName( variableName )
{}

PrintStatement::~PrintStatement()
{}

void PrintStatement::execute(ProgramState * state, std::ostream &outf)
{
	state -> initializeTest(m_variableName);
	
	outf << state -> variables[m_variableName] << endl;
	state -> programCounter = state -> programCounter + 1;
}
