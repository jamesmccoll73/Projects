#include "IfStatement.h"
#include <iostream>
using namespace std;

IfStatement::IfStatement(std::string var1, std::string op, std::string var2, int val)
	: m_var1( var1 ), m_op( op ), m_var2( var2), m_val( val )
{}

IfStatement::~IfStatement()
{}

void IfStatement::execute(ProgramState * state, ostream &outf)
{
	state -> initializeTest(m_var1);
    state -> initializeTest(m_var2);
    
    bool send = false;
    int firstTerm = state -> variables.find(m_var1) -> second;
    int secondTerm = state -> secondTermToInt(m_var2);

    if(m_op == "<>"){
        if(firstTerm != secondTerm){ send = true; }
    }
    if(m_op == "="){
        if(firstTerm == secondTerm){ send = true; }
    }
    if(m_op == "<"){
        if(firstTerm < secondTerm){ send = true; }
    }
    if(m_op == ">"){
        if(firstTerm > secondTerm){ send = true; }
    }
    if(m_op == ">="){
        if(firstTerm >= secondTerm){ send = true; }
    }
    if(m_op == "<="){
        if(firstTerm <= secondTerm){ send = true; }
    }
    
    if(m_val >= state -> programSize)
	{
		outf << "Illegal jump instruction" << endl;
		state -> endProgram();
	}
	else{
        if(send){
            state -> programCounter = m_val;
        }
        else{
            state -> programCounter = state -> programCounter + 1;
        }
    }
}