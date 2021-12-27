#include "GoToStatement.h"
#include <iostream>
using namespace std;

GoToStatement::GoToStatement(int value)
	: m_value( value )
{}

GoToStatement::~GoToStatement()
{}


void GoToStatement::execute(ProgramState * state, ostream &outf)
{
	if(m_value >= state -> programSize)
	{
		outf << "Illegal jump instruction" << endl;
		state -> endProgram();
	}
	else{
		state -> programCounter = m_value;
	}
}