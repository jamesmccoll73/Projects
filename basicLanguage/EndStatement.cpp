#include "EndStatement.h"
using namespace std;

EndStatement::EndStatement()
{}

EndStatement::~EndStatement()
{}


void EndStatement::execute(ProgramState * state, std::ostream &outf)
{
	state -> endProgram();
}
