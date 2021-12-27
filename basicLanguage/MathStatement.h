#ifndef MATH_STATEMENT_INCLUDED //CHANGE, FIGURE OUT WHAT TO CHANGE TO
#define MATH_STATEMENT_INCLUDED //CHANGE, FIGURE OUT WHAT TO CHANGE TO

#include "Statement.h"
#include "ProgramState.h"

class MathStatement: public Statement
{
private:
	std::string m_variableName;
	std::string m_secondValue;
    std::string mathType;


public:
	MathStatement(std::string type, std::string variableName, std::string value);
	~MathStatement();
	
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif