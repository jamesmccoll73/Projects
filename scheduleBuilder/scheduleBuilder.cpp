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
#include <set>
#include <vector>
#include <iomanip>

using namespace std;


void search(int classNum, vector< vector<string> > fullClasses, map <string, map <string, vector<string> > > paired,
                map<string, string> &currentClasses, vector< vector<int> > &bookedSlots, int totalClasses);
void printSolution(map<string, string> &currentClasses);
bool updateClass(string str, vector< vector<int> > &bookedSlots, string type);
bool checkSolution(map<string,string> &currentClasses, map <string, map <string, vector<string> > > &paired);

int scheduleCounter = 1;

int main(int arc,char* argv[]){
    string file = argv[1];

    ifstream infile(file.c_str());

    int totalClasses;
    infile >> totalClasses;

    vector< vector<string> > fullClasses;

    //gets vector of vectors that hold each class's time sections
    for(int i = 0; i < totalClasses; i++){
        string className;
        infile >> className;
        string classSchedule;
        getline(infile, classSchedule);
        vector<string> classes;
        classes.push_back(className);
        string result = "";
        bool skip = true;
        for(long unsigned int i = 0; i <= classSchedule.length(); i++){
            if((classSchedule[i] == ',') || (i == classSchedule.length() && result != "")){
                classes.push_back(result);
                result = "";
                skip = true;
            }
            else if(skip){
                skip = false;
            }
            else{
                result += classSchedule[i];
            }
        }
        fullClasses.push_back(classes);
    }

    map<string, string> currentClasses;

    map <string, map <string, vector<string> > > paired;
    int totalPairedClasses;
    infile >> totalPairedClasses;
    for(int i = 0; i < totalPairedClasses; i++){
        string pairedLecture;
        infile >> pairedLecture;
        string pairedDiscussion;
        infile >> pairedDiscussion;
        string wholeLine;
        getline(infile, wholeLine);
        string lectureTime;
        string result = "";
        vector <string> discussionTimes;
        discussionTimes.push_back(pairedDiscussion);
        bool firstTime = true;
        bool skip = true;
        for(long unsigned int i = 0; i <= wholeLine.length(); i++){
            if((wholeLine[i] == ',') || (i == wholeLine.length() && result != "")){
                if(firstTime){
                    lectureTime = result;
                    result = "";
                    skip = true;
                    firstTime = false;
                }    
                else{
                    discussionTimes.push_back(result);
                    result = "";
                    skip = true;
                } 
            }
            else if(skip){
                skip = false;
            }
            else{
                result += wholeLine[i];
            }
        }

    
        if(paired.find(pairedLecture) == paired.end()){
            map <string, vector<string> > inner;
            inner.insert(make_pair(lectureTime, discussionTimes));
            paired.insert(make_pair(pairedLecture, inner));
        }
        else{
            paired[pairedLecture].insert(make_pair(lectureTime, discussionTimes));
        }
    }


    vector< vector<int> > bookedSlots;
    for(int i = 0; i < 5; i++){
        vector<int> temp;
        for(int j = 0; j < 28; j++){
            temp.push_back(0);
        }
        bookedSlots.push_back(temp);
    }

    search(0, fullClasses, paired, currentClasses, bookedSlots, totalClasses);

}


void search(int classNum, vector< vector<string> > fullClasses, map <string, map <string, vector<string> > > paired,
                map<string,string> &currentClasses, vector< vector<int> > &bookedSlots, int totalClasses){
    
    if(classNum == totalClasses){
        if(checkSolution(currentClasses, paired)){    
            cout << "Schedule " << scheduleCounter << ":" << endl;
            printSolution(currentClasses);
            cout << endl;
            scheduleCounter++;
        }
    }
    else{   
        for(unsigned long int i = 1; i < fullClasses[classNum].size(); i++){
            if(updateClass(fullClasses[classNum][i], bookedSlots, "add")){
                currentClasses.insert(make_pair(fullClasses[classNum][0], fullClasses[classNum][i]));
                search(classNum+1, fullClasses, paired, currentClasses, bookedSlots, totalClasses);
                updateClass(fullClasses[classNum][i], bookedSlots, "remove");
                currentClasses.erase(fullClasses[classNum][0]);
            }
        }
    }
}

bool updateClass(string str, vector< vector<int> > &bookedSlots, string type){
    map<char, int> dayConversion;
    dayConversion.insert(make_pair('M', 0));
    dayConversion.insert(make_pair('T', 1));
    dayConversion.insert(make_pair('W', 2));
    dayConversion.insert(make_pair('R', 3));
    dayConversion.insert(make_pair('F', 4));

    int i = 0;

    //gets the days the class is taken
    string days = "";
    while(str[i] != ' '){
        days += str[i];
        i++;
    }

    //gets the times of the classes
    i++;
    int twoTimes[2];
    for(int k = 0; k < 2; k++){
        string numStr = "";
        while(str[i] != 'p' && str[i] != 'a'){
            numStr += str[i];
            i++;
        }
        int num = stoi(numStr);
        if(str[i] == 'a' || (str[i-4] == '1' && str[i-3] == '2')){
            twoTimes[k] = (num - 800 +20)/50;
        }
        else{
            twoTimes[k] = (num + 400 +20)/50;
        }
        i += 3;
    }
    
    if(type == "add"){
        //checks if the class fits in the current schedule
        for(int i = 0; i < days.length(); i++){
            for(int j = twoTimes[0]; j <= twoTimes[1]; j++){
                if(bookedSlots[dayConversion[days[i]]][j] != 0){
                    return false;
                }
            }
        }

        //it works, so update the booked timeslots
        for(int i = 0; i < days.length(); i++){
            for(int j = twoTimes[0]; j <= twoTimes[1]; j++){
                bookedSlots[dayConversion[days[i]]][j] = 1;
            }
        }
        return true;
    }
    else{ //type == "remove"
        for(int i = 0; i < days.length(); i++){
            for(int j = twoTimes[0]; j <= twoTimes[1]; j++){
                bookedSlots[dayConversion[days[i]]][j] = 0;
            }
        }
        return true;
    }
}
//MF 230pm-430pm 
//MWF 1230pm-330pm

void printSolution(map<string,string> &currentClasses){
    map<string, string>::iterator it;
    for(it = currentClasses.begin(); it != currentClasses.end(); ++it){   
        cout << it -> first << ": " << it -> second << endl;
    }
}


bool checkSolution(map<string,string> &currentClasses, map <string, map <string, vector<string> > > &paired){
    map<string, string>::iterator it;
    for(it = currentClasses.begin(); it != currentClasses.end(); ++it){   
        if(paired.find(it->first) != paired.end()){
            string discussionTime = currentClasses[paired[it->first][it->second][0]];
            vector<string> options = paired[it->first][it->second];
            bool didntWork = true;
            for(int i = 1; i < options.size(); i++){
                if(discussionTime == options[i]){
                    didntWork = false;
                }
            }
            if(didntWork){
                return false;
            }     
        }
    }
    return true;
}