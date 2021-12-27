#include <iostream>
#include <sstream> 
#include <fstream>
#include <stdio.h> 
#include <math.h>
#include <cmath>
#include <string>  
#include <bitset>
#include <vector>

using namespace std;

long decryptionKey(long p, long q);
void encrypt(string filename, long n, string message);
void decrypt(string input, string output, long d, long n);
long modularExponentiation(long M, vector<int> bitE, long n);
vector<int> toBinaryArray(long e);
long gcd(long p, long q);
pair<long,long> extendedEuclideanAlg(long L, long e);
string translation(string str, long x);


int main(int arc,char* argv[]){
    string pString;
    string qString;
    long p;
    long q;
    pString = argv[1];
    qString = argv[2];
    p = stol(pString);
    q = stol(qString);

    bool terminate = false;
   
    long d = decryptionKey(p, q);

    //if L is too small or p or q isn't prime
    if(d == -1){
        terminate = true;
    }

    while(!terminate){
        cout << "Please enter a command: ";
        string command;
        string input;
        string output;
        string filename;
        long n;
        string message;


        cin >> command;

        if(command == "EXIT"){
            terminate = true;
        }
        else if(command == "DECRYPT"){
            cin >> input;
            cin >> output;
            long n = p*q;
            decrypt(input, output, d, n);
        }
        else if(command == "ENCRYPT"){
            cin >> filename;
            cin >> n;
            getline(cin, message);
            if(n < 27){
                cout << "n value two small, please try again" << endl;
            }
            else{
                encrypt(filename, n, message);
            }
        }
        else{
            cout << "Invalid Command, please try again" << endl;
        }
    }
    return 0;
}

void encrypt(string filename, long n, string message){
    string newMessage;
    long e = 65537;
    long x = 1 + (log(n/27) / log(100));
    string segment = "";

    ofstream newFile;
    newFile.open(filename);

    for(long unsigned int i = 1; i < message.length(); i++)
    {
        string ascii;
        char letter = message[i];
        if(letter == ' '){
            ascii = "00";
        }
        else if(int(letter) - 96 < 10){
            ascii = "0" + to_string(int(letter) - 96);
        }
        else{
            ascii = to_string(int(letter) - 96);
        }
        segment += ascii;
        
        if((i % x == 0) || i == message.length() - 1){
            while(segment.length() < x*2){
                segment += "0";
            }
            long M = stol(segment);
            vector<int> bitE = toBinaryArray(e);
            long C = modularExponentiation(M, bitE, n);
            newFile << C << " ";
            
            segment = "";
        }

    }
}

void decrypt(string input, string output, long d, long n){
    ofstream outputFile;
    outputFile.open(output);

    long x = 1 + (log(n/27) / log(100));

    ifstream infile(input.c_str());
    long num;
    while(infile >> num){
        vector<int> bitD = toBinaryArray(d);
        long M = modularExponentiation(num, bitD, n);
        string str = to_string(M);
        string letters = translation(str, x);
        outputFile << letters;
    }
}

long decryptionKey(long p, long q){
    long L = ((p-1)*(q-1)) / gcd(p-1, q-1);
    if(L <= 65537){
        cout << "L is too small, please try again" << endl;;
        return -1;
    }
    pair<long,long> pairD = extendedEuclideanAlg(L, 65537);
    if(pairD.first != 1){
        cout << "Your P and Q are not primes, please try again" << endl;
        return -1;
    }
    while(pairD.second <= 0){
        pairD.second += (p-1)*(q-1);
    }
    return pairD.second;

}

long modularExponentiation(long M, vector<int> bitE, long n){
    long x = 1;
    long power = M % n;
    for(long unsigned int i = 0; i < bitE.size(); i++){
        if(bitE[i] == 1){
            x = (x * power) % n;
        }
        power = (power * power) % n;
    }
    return x;
}

vector<int> toBinaryArray(long e){
    vector<int> temp;
    for(int i = 0; e > 0; i++){
        temp.push_back(e%2);
        e = e/2;
    }
    
    return temp;
}

long gcd(long a, long b){
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

pair<long, long> extendedEuclideanAlg(long L, long e){
    long t = 1, old_t = 0, r = e, old_r = L;
    long quotient, temp;
    while(r != 0){
        quotient = old_r/r;
        temp = r;
        r = old_r - (quotient * r);
        old_r = temp;
        temp = t;
        t = old_t - (quotient*t);
        old_t = temp;
    }

    return make_pair(old_r, old_t);
}

string translation(string str, long x){
    string result;
    //filling in the missing spaces
    for(int i = 0; i < ((x*2)-str.length())/2; i++){
        result += ' ';
    }
    //adding missing zero for letters a-i
    if(str.length() % 2 == 1){
        str = "0" + str;
    }
    for(long unsigned int i = 0; i < str.length()-1; i += 2){
        string num = "";
        num += str[i];
        num += str[i+1];
        int ascii = stoi(num) + 96;
        char letter = (char)ascii;
        //ascii value for 0+96 --> space
        if(letter == '`'){
            letter = ' ';
        }
        result += letter;
    }
    return result;
}