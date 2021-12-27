//QUESTIONS: 
//How do I check whether the math operations second val is a varaible name or int?
//PRINTALL() vs PRINT(var), how to manage that difference in parameters

// Interpreter.cpp
#include "Statement.h"
#include "LetStatement.h"
#include "GoToStatement.h"
#include "GoSubStatement.h"
#include "MathStatement.h"
#include "PrintStatement.h"
#include "PrintAllStatement.h"
#include "EndStatement.h"
#include "IfStatement.h"
#include "ReturnStatement.h"
#include <vector>
#include <string>
#include <sstream> 
#include <fstream>
#include <cstdlib>


using namespace std;

// parseProgram() takes a filename as a parameter, opens and reads the
// contents of the file, and returns an vector of pointers to Statement.
void parseProgram(istream& inf, vector<Statement *> & program);

// parseLine() takes a line from the input file and returns a Statement
// pointer of the appropriate type.  This will be a handy method to call
// within your parseProgram() method.
Statement * parseLine(string line);

// interpretProgram() reads a program from the given input stream
// and interprets it, writing any output to the given output stream.
// Note:  you are required to implement this function!
void interpretProgram(istream& inf, ostream& outf);


int main()
{
        cout << "Enter BASIC program file name: ";
        string filename;
        getline(cin, filename);
        ifstream infile(filename.c_str());
        if (!infile)
        {
                cout << "Cannot open " << filename << "!" << endl;
                return 1;
        }
        interpretProgram(infile, cout);
}



void parseProgram(istream &inf, vector<Statement *> & program)
{
	program.push_back(NULL);
	
	string line;
	while( ! inf.eof() )
	{
		getline(inf, line);
		program.push_back( parseLine( line ) );
	}
}


Statement * parseLine(string line)
{
	Statement * statement;	
	stringstream ss;
	int lineNumber;
	string type;
	string var;
	string var2;
	int val;
	string op;
	string thenVariable;
	

	ss << line;
	ss >> lineNumber;
	ss >> type;
	
	if ( type == "LET" )
	{
		ss >> var;
		ss >> val;
		statement = new LetStatement(var, val);
	}
	if ( type == "ADD" || type == "SUB" || type == "MULT" || type == "DIV")
	{
		ss >> var;
		ss >> var2;
		statement = new MathStatement(type, var, var2);
	}
	if ( type == "GOTO")
	{
		ss >> val;
		statement = new GoToStatement(val);
	}
	if ( type == "GOSUB")
	{
		ss >> val;
		statement = new GoSubStatement(val);
	}
	if ( type == "RETURN")
	{
		statement = new ReturnStatement();
	}
	if ( type == "PRINT")
	{
		ss >> var;
		statement = new PrintStatement(var);
	}
	if ( type == "PRINTALL")
	{
		statement = new PrintAllStatement();
	}
	if( type == "END" || type == ".")
	{
		statement = new EndStatement();
	}
	if( type == "IF")
	{
		ss >> var;
		ss >> op;
		ss >> var2;
		ss >> thenVariable;
		ss >> val;
		
		statement = new IfStatement(var, op, var2, val);
	}


		
	return statement;
}


void interpretProgram(istream& inf, ostream& outf)
{
	vector<Statement *> program;
	parseProgram( inf, program );
	ProgramState * tracker = new ProgramState(program.size());
	while((tracker -> programCounter) < (int)program.size())
	{
		program[tracker -> programCounter] -> execute(tracker, outf);
	}
	for(int i = 0; i < (int)program.size(); i++)
	{
		delete program[i];
	}
	delete tracker;
}
