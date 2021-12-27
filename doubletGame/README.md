**Function:** Implements a self-written MinHeap, uses this MinHeap to play Lewis Carl's Doublet game. 

**Lewis Carl's Doublet Game:** The player enters two words on the command line of identical length. The objective is to transform the first word into the second word by forming successive words of the same length, changing on letter at a time AND using the LEAST amount of words. The third command line argument is a list of valid words to use in the transformation.

**Example input:** <br />
./doublet head tail words.txt

**Example output:** <br />
*Outputs the final path taken, the steps of the final path, and the total number of steps it took to find the final path*

Path:
TAIL
TALL
TELL
TEAL
HEAL
Steps for Fastest Path: 5
Total Steps Tried: 5
