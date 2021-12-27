#include <vector>
#include <map>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <time.h> 
#include <thread>        
#include <chrono> 



template <class T>
    class Hashtable{
        public:
            Hashtable(bool deb, unsigned int size = 11);
            ~Hashtable();
            int add(std::string k, const T& val);
            const T& lookup(std::string k);
            void reportAll(std::ostream &) const;

        private:
            void resize();
            int getSize(int num); //gets the next prime number for tableSize
            int hash(std::string k) const;
            int tableSize; //current size of the table
            int currSize; //current number of elements
            bool debug;
            int r1, r2, r3, r4, r5;
            struct Item{
                Item(std::string str, const T&);
                T val;
                std::string str;
            };
            Item **table;
            T garbage;
    };

template <class T>
Hashtable<T>::Item::Item(std::string s, const T& v){
    str = s;
    val = v;
}


template <class T>
Hashtable<T>::Hashtable(bool deb, unsigned int size){
    srand (time(NULL));

    debug = deb;
    tableSize = size;
    currSize = 0;
    table = new Item*[tableSize];

    for(int i = 0; i < tableSize; i++){
        table[i] = nullptr;
    }

    if(!debug){
        r1 = rand() % tableSize;
        r2 = rand() % tableSize;
        r3 = rand() % tableSize;
        r4 = rand() % tableSize;
        r5 = rand() % tableSize;
    }
    else{
        r1 = 983132572;
        r2 = 1468777056;
        r3 = 552714139;
        r4 = 984953261;
        r5 = 261934300;
    }

}

template <class T>
Hashtable<T>::~Hashtable(){
    for(int i = 0; i < tableSize; i++){
        if(table[i] != nullptr){
            delete table[i];
        }
    }
    delete table;
}


template <class T>
int Hashtable<T>::add(std::string k, const T& val){
    if((double)(currSize+1)/tableSize >= 0.5){ //load factor >= 0.5 if item is inserted
        resize();
    }
    
    int hashIndex = hash(k);
    if(table[hashIndex] == nullptr){ //open spot for item
        Item* temp = new Item(k, val);
        table[hashIndex] = temp;
        currSize ++;
        return 0;
    }
    else if(lookup(k) == val){ //item is in the table already
        return -1;
    }
    else{ //item to be inserted needs to probe to find spot
        long long currIndex = hashIndex;
        long long counter = 0;
        long long pow = 1;
        time_t futur = time(NULL) + 10;
        while(table[currIndex] != nullptr){
            currIndex = (hashIndex + pow*pow) % tableSize;
            counter++;
            pow++;
            if(time(NULL) > futur) { //if it probes for 10 seconds without finding a spot (can't find a spot)
                std::cout << "INFINITE LOOP" << std::endl;
                std::cout << "Number of probes before timeout: " << counter << std::endl;
                break;
            }
        }
        Item* temp = new Item(k, val); //finds spot, insert item
        table[currIndex] = temp;
        currSize ++;
        return counter;
    }
    currSize ++;
}


template <class T>
const T& Hashtable<T>::lookup(std::string k){
    int hashIndex = hash(k);
    int currIndex = hashIndex;
    int pow = 1;
    while(table[currIndex] != nullptr){ //quadratic probes until finds open spot or finds item
        if(table[currIndex] -> str == k){
            return table[currIndex] -> val;
        }
        currIndex = (hashIndex + pow*pow) % tableSize;
        pow++;
    }
    return garbage;
}


template <class T>
void Hashtable<T>::reportAll(std::ostream &) const{
    for(int i = 0; i < tableSize; i++){
        if(table[i] != nullptr){
            std::cout << table[i] -> str << " " << table[i] -> val << std::endl;
        }
    }
}

template <class T>
void Hashtable<T>::resize(){
    srand (time(NULL));

    int oldTableSize = tableSize;
    tableSize = getSize(tableSize + 5);

    if(!debug){
        r1 = rand() % tableSize;
        r2 = rand() % tableSize;
        r3 = rand() % tableSize;
        r4 = rand() % tableSize;
        r5 = rand() % tableSize;
    }

    Item** oldTable = table;
    table = new Item*[tableSize];
    for(int i = 0; i < tableSize; i++){
        table[i] = nullptr;
    }
    
    for(int i = 0; i < oldTableSize; i++){ //rehashes items from old table into new table with new tableSize
        if(oldTable[i] != nullptr){
            int newHash = hash(oldTable[i] -> str);
            table[newHash] = new Item(oldTable[i] -> str, oldTable[i] -> val);
        }
    }
    
    for(int i = 0; i < oldTableSize; i++)
    {
        delete oldTable[i];
    }
    delete oldTable;

}

template <class T>
int Hashtable<T>::hash(std::string k) const{
    long long holder[5];
    int lastIndex = k.length()%6;
    int currIndex = 4;
    long long result = 0;
    int power = 0;
    for(int i = k.length()-1; i >= lastIndex; i--){
        int letterNum = int(k[i]) - 96;
        result += letterNum * std::pow(27, power);
        if(power == 5){
            holder[currIndex] = result;
            result = 0;
            power = 0;
            currIndex--;
        }
        else{
            power++;
        }
    }
    result = 0;
    power = 0;
    for(int i = lastIndex-1; i >= 0; i--){
        int letterNum = int(k[i]) - 96;
        result += letterNum * pow(27, power);
        if(i == 0){
            holder[currIndex] = result;
            currIndex--;
        }
        power++;
    }
    for(int i = currIndex; i >=0; i--){
        holder[i] = 0;
    }

    long long solution = (r1*holder[0] + r2*holder[1] + r3*holder[2] + 
                            r4*holder[3] + r5*holder[4]) % tableSize;

    return (int)solution;
}

template <class T>
int Hashtable<T>::getSize(int num){
    
    if(num <= 11){
        return 11;
    }
    else if(num <= 23){
        return 23;
    }
    else if(num <= 47){
        return 47;
    }
    else if(num <= 97){
        return 97;
    }
    else if(num <= 197){
        return 197;
    }
    else if(num <= 397){
        return 397;
    }
    else if(num <= 797){
        return 797;
    }
    else if(num <= 1597){
        return 1597;
    }
    else if(num <= 3203){
        return 3203;
    }
    else if(num <= 6421){
        return 6421;
    }
    else if(num <= 12853){
        return 12853;
    }
    else if(num <= 25717){
        return 25717;
    }
    else if(num <= 51437){
        return 51437;
    }
    else if(num <= 102877){
        return 102877;
    }
    else if(num <= 205759){
        return 205759;
    }
    else if(num <= 411527){
        return 411527;
    }
    else{ 
        return 823117;
    }
}