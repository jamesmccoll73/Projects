#include "ReturnStatement.h"
using namespace std;

ReturnStatement::ReturnStatement()
{}

ReturnStatement::~ReturnStatement()
{}

void ReturnStatement::execute(ProgramState * state, ostream &outf)
{
    if(state -> numStack.empty()){
        state -> endProgram();
    }
    else{
        int val = state -> numStack.top();
        state -> numStack.pop();
        state -> programCounter = val + 1;
    }
    
}