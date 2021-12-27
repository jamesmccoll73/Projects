using namespace std;
#include <string>
#include <iostream>

using namespace std;

void helper(string in, string val);

int main(int arc,char* argv[]){
    string toPermute;
    toPermute = argv[1];
    helper(toPermute, "");
}

void helper(string in, string val)
{
    //if the in string size is one, it adds it on to the end of the value and returns the value
    if(in.size() <= 1){
        val = val + in;
        cout << val << endl;
        return;
    }
    //cycles through current in string and goes through below process for each letter
    for(unsigned int i = 0; i < in.size(); i++){ 
        string temp = "";
        //Includes every letter but in[i] in the temp string
        for(unsigned int j = 0; j < in.size(); j++){
            if(j != i){
                temp = temp + in[j];
            }
            
        }
        //sends temp (the remaining letters string) into the recursive function, adds on in[i] to the value string
        helper(temp, val + in[i]);
    }
}