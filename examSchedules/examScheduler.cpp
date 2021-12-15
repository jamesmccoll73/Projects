#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdio.h>     
#include <stdlib.h>     
#include <time.h> 
#include <thread>        
#include <chrono> 
#include <string>
#include <map>
#include <vector>
#include "avlbst.h"
#include <iomanip>

using namespace std;

bool search(int student, vector< vector<int> > fullClasses, int studentNum, 
                AVLTree<int, int> &cal, vector< vector<int> > booked, int classNum);
void printSolution(AVLTree<int, int> &cal, int timeSlots);

int main(int arc,char* argv[]){
    string file = argv[1];

    ifstream infile(file.c_str());

    int examNum;
    int studentNum;
    int timeslotNum;
    infile >> examNum;
    infile >> studentNum;
    infile >> timeslotNum;

    vector< vector<int> > fullClasses;

    //gets vector of vectors that hold each students classes
    for(int i = 0; i < studentNum; i++){
        string studentName;
        infile >> studentName;
        string classSchedule;
        getline(infile, classSchedule);
        vector<int> classes;
        string result = "";
        bool reachedClass = false;
        for(long unsigned int i = 0; i <= classSchedule.length(); i++){
            if((i == classSchedule.length() && result != "") || (classSchedule[i] == ' ' && reachedClass)){
                int num = stoi(result);
                classes.push_back(num);
                result = "";
                reachedClass = false;
            }
            else if(classSchedule[i] != ' '){
                result += classSchedule[i];
                reachedClass = true;
            }
        }
        fullClasses.push_back(classes);
    }

    AVLTree<int, int> cal;
    int classNum = 0;
    vector< vector<int> > booked;
    for(int i = 0; i < studentNum; i++){
        vector<int> row;
        for(int j = 0; j < timeslotNum; j++){
            row.push_back(0); //0 = open, 1 = closed
        }
        booked.push_back(row);
    }

    if(!search(0, fullClasses, studentNum, cal, booked, classNum)){
        cout << "No Valid Exam Schedule" << endl;
    }
}



bool search(int student, vector< vector<int> > fullClasses, int studentNum, 
                AVLTree<int, int> &cal, vector< vector<int> > booked, int classNum){
    if(student == studentNum){
        printSolution(cal, booked[0].size());
        return true;
    }
    else{   
        if(cal.find(fullClasses[student][classNum]) != cal.end()){//has been inserted
            int timeSlot = cal.find(fullClasses[student][classNum]) -> second;
            if(booked[student][timeSlot] == 0){
                booked[student][timeSlot]++;
                if(classNum >= (int)fullClasses[student].size() - 1){
                    if(search(student+1, fullClasses, studentNum, cal, booked, 0)){
                        return true;
                    }
                }
                else{
                    if(search(student, fullClasses, studentNum, cal, booked, classNum+1)){
                        return true;
                    }
                }
                booked[student][timeSlot]--;
                return false;
            }
            return false;
            
        }
        else{ //hasn't been inserted
            for(unsigned long int j = 0; j < booked[student].size(); j++){
                if(booked[student][j] == 0){
                    booked[student][j]++;
                    cal.insert(make_pair(fullClasses[student][classNum], j));
                    if(classNum >= (int)fullClasses[student].size() - 1){
                        if(search(student+1, fullClasses, studentNum, cal, booked, 0)){
                            return true;
                        }
                    }
                    else{
                        if(search(student, fullClasses, studentNum, cal, booked, classNum+1)){
                            return true;
                        }
                    }
                    booked[student][j]--;
                    cal.remove(fullClasses[student][classNum]);
                }
            }
            return false;
        }
        // return false;
    }
}


void printSolution(AVLTree<int, int> &cal, int timeSlots){
    vector< vector<int> > classHolder;
    for(int i = 0; i < timeSlots; i++){
        vector<int> slot;
        slot.push_back(0);
        classHolder.push_back(slot);
    }

    AVLTree<int, int>::iterator it;
    for(it = cal.begin(); it != cal.end(); ++it){   
        classHolder[it -> second].push_back((int)it->first);
    }
    
    for(int i = 0; i < timeSlots; i++){
        if(classHolder[i].size() >= 2){
            cout << "Section " << i+1 << ": ";
            for(int j = 1; j < classHolder[i].size()-1; j++){
                cout << classHolder[i][j] << ", ";
            }
            cout << classHolder[i][classHolder[i].size()-1];
        }
        cout << endl;
    }
}


