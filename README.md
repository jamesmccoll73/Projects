## bst.h, avlbst.h, print_bst.h:
Wrote and implemented own version of Binary Search Trees and AVL trees, used these self-implemented trees to keep track of classes in examScheduler (explained below)


## examScheduler.cpp:

**Function:** Takes the schedules of multiple different students and yields an exam schedule where no student will have two exams at the same time

**Explaination:** The input file (whose name is passed in at the command line) will have three parameters: how many classes there are, how many students there are, and how many timeslots are available for exams. Each successive line will have the name of a student followed by the class numbers that the student is in. The best possible exam schedule is then output in the terminal, with "No Valid Exam Schedule" being outputted if there is no possible way to avoid conflicts with the alloted amount of timeslots.

**Example input:** <br />
10 7 6                       (10 classes, 7 students, 6 exam timeslots) <br />
aaron 104 170 101 350      //student and their class numbers  <br />
david 104 170 350 270 <br />
sarah 101 310 104 <br />
brook 270 350 242 360 <br />
james 101 350 270 310 <br />
mason 360 481 101 340 <br />
ethan 340 350 360 310 <br />

**Example output:** <br />
Section 1: 104, 242, 481 <br />
Section 2: 170, 310 <br />
Section 3: 101 <br />
Section 4: 350 <br />
Section 5: 270, 340 <br />
Section 6: 360 <br />
