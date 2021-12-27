**Function:** Implements an interpreter for a limited version of the programming language BASIC. Uses inheritence and polymorphism to implement each type of BASIC statement so it can perform its specific function

**Example Walkthrough:** <br />
LET ABE 42 //Sets variable Abe = 42
LET BETSY 100
LET CADE 22
LET DAVE 30
IF ABE > 50 THEN 13 //If Abe > 50, then go to line 13
ADD ABE BETSY //Add Betsy to Abe
SUB BETSY CADE //Subtract Cade from Betsy
MULT CADE DAVE //Multiply Cade by Dave
DIV DAVE ABE //Divide Dave by Abe
GOSUB 16 //Go to function line to 16
PRINT ABE //Print Abe
GOTO 20 //Go to line 20
LET ABRA 9001
LET CADABRA 3720
RETURN //Return to line after GOSUB
PRINTALL //Print all variables
END //End of the code
.