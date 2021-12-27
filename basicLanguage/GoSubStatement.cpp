#include "GoSubStatement.h"
#include <iostream>
using namespace std;

GoSubStatement::GoSubStatement(int value)
	: m_value( value )
{}

GoSubStatement::~GoSubStatement()
{}


void GoSubStatement::execute(ProgramState * state, ostream &outf)
{
	state -> numStack.push(state -> programCounter);
	if(m_value >= state -> programSize)
	{
		cout << "Illegal jump instruction" << endl;
		state -> endProgram();
	}
	else{
		state -> programCounter = m_value;
	}
}