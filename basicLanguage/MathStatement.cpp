#include "MathStatement.h"
#include <iostream>
#include <string>
using namespace std;

MathStatement::MathStatement(std::string type, std::string variableName, std::string value)
	:mathType( type ), m_variableName( variableName ), m_secondValue( value )
{}

MathStatement::~MathStatement()
{}

// The LetStatement version of execute() should make two changes to the
// state of the program:
//
//    * set the value of the appropriate variable
//    * increment the program counter
void MathStatement::execute(ProgramState * state, ostream &outf)
{
	state -> initializeTest(m_variableName);
    state -> initializeTest(m_secondValue);

    int firstTerm = state -> variables.find(m_variableName) -> second;
    int secondTerm = state -> secondTermToInt(m_secondValue);
    
    if(mathType == "ADD"){
        state -> insert_or_assign(m_variableName, firstTerm + secondTerm);
    }
    if(mathType == "SUB"){
        state -> insert_or_assign(m_variableName, firstTerm - secondTerm);
    }
    if(mathType == "MULT"){
        state -> insert_or_assign(m_variableName, firstTerm * secondTerm);
    }
    if(mathType == "DIV"){
        if(secondTerm == 0)
        {
            cout << "Divide by zero exception" << endl;
            state -> endProgram();
            return; //WANT TO END PROGRAM HERE! BREAK?
        }
        state -> insert_or_assign(m_variableName, firstTerm / secondTerm);
    }
    
    state -> programCounter = state -> programCounter + 1;
	//Increments program counter
}