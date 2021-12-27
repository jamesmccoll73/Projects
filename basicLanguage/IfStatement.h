#ifndef IF_STATEMENT_INCLUDED
#define IF_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"

class IfStatement: public Statement
{
private:
	std::string m_var1;
    std::string m_op;
    std::string m_var2;
    int m_val;

public:
	IfStatement(std::string var1, std::string op, std::string var2, int val);
    ~IfStatement();

	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif