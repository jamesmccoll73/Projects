## classFinder.cpp:

**Function:** Takes all possible timeslots of the classes the user wants to take and outputs all possible schedule combinations, ensuring that 1) there are no conflicts between classes and 2) Any lectures that are paired to specific discussions are still paired

**Explaination:** The input file (whose name is passed in at the command line) will have three parameters: how many classes there are, how many students there are, and how many timeslots are available for exams. Each successive line will have the name of a student followed by the class numbers that the student is in. The best possible exam schedule is then output in the terminal, with "No Valid Exam Schedule" being outputted if there is no possible way to avoid conflicts with the alloted amount of timeslots.

**Example input:** <br />
6   //total number of classes<br />
BAEP460 M 600pm-750pm   //Class name and the all times it's offered (Monday from 6:00pm-7:50pm) <br />
CSCI201 TR 330pm-450pm, MW 1200pm-150pm <br />
CSCI201LAB W 1200pm-150pm, M 1000am-1150am, W 1000am-1150am, M 1200pm-150pm, R 1000am-1150am <br />
CSCI270 MW 1230pm-150pm, MW 330pm-450pm <br />
CALC3 MWF 1100am-1150am, MWF 1000am-1050am <br />
CALC3DISC TR 1200pm-1250pm, TR 100pm-150pm <br />

2   //total number of classes that have specific labs/discussions that pair with them <br />
CSCI201 CSCI201LAB TR 330pm-450pm, W 1200pm-150pm, M 1000am-1150am //Lecture name, Discussion/Lab that it's paired to, time of the lecutre, times of the possible paired discussion/labs <br />
CSCI201 CSCI201LAB MW 1200pm-150pm, W 1000am-1150am, M 1200pm-150pm, R 1000am-1150am <br />

**Example output:** <br />
Schedule 1: <br />
BAEP460: M 600pm-750pm <br />
CALC3: MWF 1100am-1150am <br />
CALC3DISC: TR 1200pm-1250pm <br />
CSCI201: TR 330pm-450pm <br />
CSCI201LAB: W 1200pm-150pm <br />
CSCI270: MW 330pm-450pm <br />
<br />
Schedule 2: <br />
BAEP460: M 600pm-750pm <br />
CALC3: MWF 1100am-1150am <br />
CALC3DISC: TR 100pm-150pm <br />
CSCI201: TR 330pm-450pm <br />
CSCI201LAB: W 1200pm-150pm <br />
CSCI270: MW 330pm-450pm <br />

Schedule 3: <br />
BAEP460: M 600pm-750pm <br />
CALC3: MWF 1000am-1050am <br />
CALC3DISC: TR 1200pm-1250pm <br />
CSCI201: TR 330pm-450pm <br />
CSCI201LAB: W 1200pm-150pm <br />
CSCI270: MW 330pm-450pm <br />
<br />
Schedule 4: <br />
BAEP460: M 600pm-750pm <br />
CALC3: MWF 1000am-1050am <br />
CALC3DISC: TR 100pm-150pm <br />
CSCI201: TR 330pm-450pm <br />
CSCI201LAB: W 1200pm-150pm <br />
CSCI270: MW 330pm-450pm <br />
<br />
Schedule 5: <br />
BAEP460: M 600pm-750pm <br />
CALC3: MWF 1100am-1150am <br />
CALC3DISC: TR 1200pm-1250pm <br />
CSCI201: MW 1200pm-150pm <br />
CSCI201LAB: R 1000am-1150am <br />
CSCI270: MW 330pm-450pm <br />
<br />
Schedule 6: <br />
BAEP460: M 600pm-750pm <br />
CALC3: MWF 1100am-1150am <br />
CALC3DISC: TR 100pm-150pm <br />
CSCI201: MW 1200pm-150pm <br />
CSCI201LAB: R 1000am-1150am <br />
CSCI270: MW 330pm-450pm <br />
<br />
Schedule 7: <br />
BAEP460: M 600pm-750pm <br />
CALC3: MWF 1000am-1050am <br />
CALC3DISC: TR 1200pm-1250pm <br />
CSCI201: MW 1200pm-150pm <br />
CSCI201LAB: R 1000am-1150am <br />
CSCI270: MW 330pm-450pm <br />
<br />
Schedule 8: <br />
BAEP460: M 600pm-750pm <br />
CALC3: MWF 1000am-1050am <br />
CALC3DISC: TR 100pm-150pm <br />
CSCI201: MW 1200pm-150pm <br />
CSCI201LAB: R 1000am-1150am <br />
CSCI270: MW 330pm-450pm <br />