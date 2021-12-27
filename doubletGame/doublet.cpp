#include "MinHeap.h"
#include <iostream>
#include <sstream> 
#include <fstream>
#include <queue>
#include <set>
#include <algorithm> 
#include <string>  

using namespace std;

pair<int,int> ASearch(string head, string tail, set<string> words, map<string, int> heuristic, 
                                map<string,int> distance, set<string> visited);
void findNodes(string str, MinHeap<string> heap, set<string> words, int dist, string tail, 
                    map<string,int> heuristic, map<string,int> distance, set<string> visited);
int setHeuristic(string temp, string tail);



int main(int arc,char* argv[]){
    
    string head;
    string tail;
    string file;
    int n;

    head = argv[1];
    tail = argv[2];
    file = argv[3];

    ifstream infile(file.c_str());
    if (!infile)
    {
        cout << "Cannot open " << file << "!" << endl;
        return 1;
    }
    infile >> n;
    
    set<string> words; //set that holds all the words in a file
    map<string, int> heuristic; //map that, given a string, returns that string's heuristic
    map<string, int> distance; //map that, given a string, returns that string's distance from the starting point
    set<string> visited; //set that holds the strings that have been visited
    for(int i = 0; i < n; i ++){
        string input;
        infile >> input;
        for(long unsigned int i = 0; i < input.length(); i++){
            input[i] = toupper(input[i]);
        }
        words.insert(input);
    }
    for(long unsigned int i = 0; i < head.length(); i++){
        head[i] = toupper(head[i]);
        tail[i] = toupper(tail[i]);
    }

    cout << "Path:" << endl;
    //A* Search Algorithm
    pair<int,int> vals = ASearch(head, tail, words, heuristic, distance, visited);
    
    if(vals.first == -1){
        cout << "No transformation" << endl;
    }
    else{
        cout << "Steps for Fastest Path: " << vals.first << endl;
    }
    cout << "Total Steps Tried: " << vals.second << endl;
    return 0;
}

pair<int,int> ASearch(string head, string tail, set<string> words, map<string, int> heuristic, 
                                map<string,int> distance, set<string> visited){
    
    MinHeap<string> heap(2);
    map<string,string> predecessor;
    predecessor[head] = "garbagevalue";
    int expansions = 0;
    int headHeuristic = setHeuristic(head, tail);
    heap.add(head, (headHeuristic)*(head.length()+1) + headHeuristic);
    distance[head] = 0;
    heuristic[head] =  headHeuristic;
    visited.insert(head);

    while(!heap.isEmpty() && heuristic[heap.peek()] != 0){
        
        string str = heap.peek();
        heap.remove();
        
        string original = str;
        int dist = distance[original];
        
        //checks all outgoing nodes from string being inspected
        for(unsigned long int i = 0; i < str.length(); i++){
            char letter = str[i];
            char temp = 'A';
            while(temp != '['){
                str[i] = temp;
                if(words.find(str) != words.end() && str != original){  //if word is in the set
                    int h = setHeuristic(str, tail);
                    if(visited.find(str) == visited.end()){   //if word hasn't been discovered yet
                        heuristic[str] = h;
                        distance[str] = dist + 1;
                        visited.insert(str);
                        predecessor[str] = original;
                        heap.add(str, (dist+1 + h)*(str.length()+1) + h);
                    }
                    else{
                        if(distance[str] > dist+1){ //checks if the string's past distance is greater than the new distance that was just found
                            distance[str] = dist + 1;
                            predecessor[str] = original;
                            heap.update(str, (dist+1 + h)*(str.length()+1) + h);
                        }
                    }
                }
                temp++;
            }
            str[i] = letter;
        }
        expansions++;
    }

    string temp = heap.peek();
    while(predecessor[temp] != "garbagevalue"){
        cout << temp << endl;
        temp = predecessor[temp];
    }
    
    //checks if successful path was not found
    if(heap.isEmpty()){
        pair<int,int> failed;
        failed.first = -1;
        failed.second = expansions;
        return failed;
    }
    pair<int,int> success;
    success.first = distance[heap.peek()]; 
    success.second = expansions;
    return success;

}

//calculates heuristic
int setHeuristic(string temp, string tail){
    int counter = 0;
    for(unsigned long int i = 0; i < temp.length(); i++){
        if(temp[i] != tail[i]){
            counter++;
        }
    }
    return counter;
}
