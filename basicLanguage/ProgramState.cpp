#include "ProgramState.h"
#include <iostream>
using namespace std;

ProgramState::ProgramState(int value)
	: programSize( value )
{
    programCounter = 1;
}

ProgramState::~ProgramState()
{}

void ProgramState::endProgram()
{
    programCounter = programSize;
}

int ProgramState::secondTermToInt(string str)
{
    int secondTerm;
	if(std::isdigit(str[0]) || std::isdigit(str[1])){
        secondTerm = stoi(str);
    }
    else{
       	secondTerm = variables.find(str) -> second;
    }
    return secondTerm;
}

void ProgramState::insert_or_assign(string str, int num)
{
    map<string, int>::iterator it;
    bool alreadyInside = false;
	for(it = variables.begin(); it != variables.end(); it++){ 
		if(it -> first == str){
            it -> second = num;
            alreadyInside = true;
        }
	}
    if(!alreadyInside)
    {
        variables.insert(pair<string,int>(str, num));
    }
}

void ProgramState::initializeTest(string str)
{
    if(!std::isdigit(str[0]) && !std::isdigit(str[1]))
    {
        map<string, int>::iterator it;
        bool alreadyInside = false;
        for(it = variables.begin(); it != variables.end(); it++){ 
            if(it -> first == str){
                alreadyInside = true;
            }
        }
        if(!alreadyInside)
        {
            variables.insert(pair<string,int>(str, 0));
        }
    }
}