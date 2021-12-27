## birthdayProblem:

**Function:** Implements a self-written hashtable and uses it to test the birthday paradox: it only takes an average of 23 people until you have a greater than 50% chance to pick two people with the same birthday. 

**Explanation:** Birthday.cpp declares a hashtable of size 365, representing the 365 possible birthdays. It then runs 1000 trials where it adds items to the hashtable until there is a collision, representing how many people need to be added until two people have the same birthday. It then finds the percentage of times the total runs taken before a collision is under 24, testing the hypothesis that it only takes an average of 23 people until you have a greater than 50% chance to pick two people with the same birthday. 

