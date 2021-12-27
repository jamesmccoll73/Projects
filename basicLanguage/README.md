**Function:** Implements an interpreter for a limited version of the programming language BASIC. Uses inheritence and polymorphism to implement each type of BASIC statement so it can perform its specific function

**Example Walkthrough:** <br />
LET ABE 42 //Sets variable Abe = 42 <br />
LET BETSY 100 <br />
LET CADE 22 <br />
LET DAVE 30 <br />
IF ABE > 50 THEN 13 //If Abe > 50, then go to line 13 <br />
ADD ABE BETSY //Add Betsy to Abe <br />
SUB BETSY CADE //Subtract Cade from Betsy <br />
MULT CADE DAVE //Multiply Cade by Dave <br />
DIV DAVE ABE //Divide Dave by Abe <br />
GOSUB 16 //Go to function line to 16 <br />
PRINT ABE //Print Abe <br />
GOTO 20 //Go to line 20 <br />
LET ABRA 9001 <br />
LET CADABRA 3720 <br />
RETURN //Return to line after GOSUB <br />
PRINTALL //Print all variables <br />
END //End of the code <br />
.
