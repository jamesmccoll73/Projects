#include <vector>
#include <map>
#include <exception>
#include <stdexcept>
#include <iostream>

template <class T>
  class MinHeap {
     public:
        MinHeap (int d);
         /* Constructor that builds a d-ary Min Heap
          This should work for any d >= 2,
          but doesn't have to do anything for smaller d.*/

        ~MinHeap ();

        void add (T item, int priority);
         /* adds the item to the heap, with the given priority. */

        const T & peek () const;
         /* returns the element with smallest priority.  
			Break ties however you wish.  
			Throws an exception if the heap is empty. */

        void remove ();
         /* removes the element with smallest priority.
			Break ties however you wish.
            Throws an exception if the heap is empty. */

        bool isEmpty ();
         /* returns true iff there are no elements on the heap. */

        void update(T item, int priority);
        int getPriority(T item);
        void swap(int first, int second);
        int locateItem(T item);
        void printHeap();
        int size;

   private:
      // whatever you need to naturally store things.
      // You may also add helper functions here.
        std::vector<std::pair<T,int> > heap; //stores item type with its priority
        int n;
        void bubbleUp(int pos);
        void trickleDown(int pos);
        void breakTie(T, T);
  };

template <class T>
MinHeap<T>::MinHeap (int d){
    n = d;
    size = 0;
}

template <class T>
MinHeap<T>::~MinHeap (){}

template <class T>
void MinHeap<T>::add (T item, int priority){
    heap.push_back(std::make_pair(item, priority));
    bubbleUp(size);
    size++;
}
         
template <class T>
const T & MinHeap<T>::peek () const{
    if(size <= 0){
        throw std::logic_error("Heap is empty!");
    }
    
    return heap.front().first;
}
         
template <class T>
void MinHeap<T>::remove (){
    if(size <= 0){
        throw std::logic_error("Heap is empty!");
    }
    else if(size == 1){
        heap.clear();
        size--;
    }
    else{
        swap(0, size-1);
        size--;
        heap.pop_back();
        trickleDown(0);  
    }   
} 

template <class T>
bool MinHeap<T>::isEmpty (){
    return size == 0;
}

template <class T>
void MinHeap<T>::update(T item, int priority){
    
    int itemLocation = locateItem(item);
    int pastPriority = heap[itemLocation].second;
    heap[itemLocation].second = priority;

    if(pastPriority <= priority){
        bubbleUp(itemLocation);
    }
    else{
        trickleDown(itemLocation);
    }
}

template <class T>
void MinHeap<T>::bubbleUp(int pos){
    if(pos > 0 && heap[pos].second < heap[(pos-1)/n].second){
        swap(pos, (pos-1)/n);
        bubbleUp((pos-1)/n);
    }
    if(pos > 0 && heap[pos].second == heap[(pos-1)/n].second){
        breakTie(heap[(pos-1)/n].first, heap[pos].first);
    }
}
        
template <class T>
void MinHeap<T>::trickleDown(int pos){
    int child = n*pos+1;
    if(child < size){
        int minVal = heap[child].second;
        int minIndex = 0;
        int i;
        for(i = 1; i < n; i++){
            if(child + i < size && heap[child + i].second < minVal)
            {
                minVal = heap[child + i].second;
                minIndex = i;
            }
        }
        child += minIndex;

        if(heap[child].second < heap[pos].second){
            swap(child, pos);
            trickleDown(child);
        }
        if(heap[child].second == heap[pos].second){
            breakTie(heap[pos].first, heap[child].first);
        }
    }
}

template <class T>
void MinHeap<T>::swap(int first, int second){
    std::pair<T, int> item = heap[first];
    heap[first] = heap[second];
    heap[second] = item;
}

template <class T>
int MinHeap<T>::getPriority(T item){
    return heap[locateItem(item)].second;
}

//If two strings have the same priority, it compares the strings and puts the 
//smaller lexicographic string first
template <class T>
void MinHeap<T>::breakTie(T top, T bottom){
    if(bottom < top){
        swap(locateItem(top), locateItem(bottom));
    }
}

template <class T>
int MinHeap<T>::locateItem(T item){
    for(int i = 0; i <= size; i++){
        if(heap[i].first == item){
            return i;
        }
    }
    return -1;
}



  