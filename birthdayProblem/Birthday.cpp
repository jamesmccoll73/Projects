#include "hashtable.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdio.h>     
#include <stdlib.h>     
#include <time.h> 
#include <thread>        
#include <chrono> 

using namespace std;


string generateRandomWord();
int birthdayProblem();

int main(){
    srand (time(NULL));
    double twentyThreeAndUnder = 0;
    double twentyFourAndOver = 0;
    int testRuns = 1000;
    for(int i = 0; i < testRuns; i++){
        int wordCount = birthdayProblem();
        cout << wordCount << endl; //outputs the number of calls it took on that run
        if(wordCount <= 23){
            twentyThreeAndUnder++;
        }
        else{
            twentyFourAndOver++;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    cout << "Number of times 23 and under: " << twentyThreeAndUnder << endl;
    cout << "Number of times 24 and over: " << twentyFourAndOver << endl;
    cout << "Ratio of times 23 and under: " << (twentyThreeAndUnder/testRuns) * 100 << "%" << endl;
}


int birthdayProblem(){
    Hashtable<int> Birthday(false,365);
    int wordCounter = 0;
    bool done = false;
    int i = 0;
    while(!done){
        string str = generateRandomWord();
        int num = Birthday.add(str, i);
        if(num > 0){ //add until it needs to probe to place the item in the hashtable (collision)
            done = true;
        } 
        wordCounter++;
        i++;
    }
    return wordCounter;       
}
    

string generateRandomWord(){
    // int wordSize = (rand() % 28) + 1;
    int wordSize = 28;
    string result = "";

    for(int i = 0; i < wordSize; i++){
        char randLetter = (char)((rand() % 26) + 97);
        result += randLetter; 
    }
    return result; 
}