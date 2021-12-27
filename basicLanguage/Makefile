all: interpreter

interpreter: interpreter.cpp EndStatement.o GoSubStatement.o GoToStatement.o IfStatement.o LetStatement.o MathStatement.o PrintStatement.o PrintAllStatement.o ProgramState.o ReturnStatement.o Statement.o
	g++ -g -Wall interpreter.cpp EndStatement.o GoSubStatement.o GoToStatement.o IfStatement.o LetStatement.o MathStatement.o PrintStatement.o PrintAllStatement.o ProgramState.o ReturnStatement.o Statement.o -o interpreter

EndStatement.o: EndStatement.h EndStatement.cpp Statement.h
	g++ -g -Wall -c EndStatement.cpp -o EndStatement.o

GoSubStatement.o: GoSubStatement.h GoSubStatement.cpp Statement.h
	g++ -g -Wall -c GoSubStatement.cpp -o GoSubStatement.o

GoToStatement.o: GoToStatement.h GoToStatement.cpp Statement.h
	g++ -g -Wall -c GoToStatement.cpp -o GoToStatement.o

IfStatement.o: IfStatement.h IfStatement.cpp Statement.h
	g++ -g -Wall -c IfStatement.cpp -o IfStatement.o

LetStatement.o: LetStatement.h LetStatement.cpp Statement.h
	g++ -g -Wall -c LetStatement.cpp -o LetStatement.o

MathStatement.o: MathStatement.h MathStatement.cpp Statement.h
	g++ -g -Wall -c MathStatement.cpp -o MathStatement.o

PrintStatement.o: PrintStatement.h PrintStatement.cpp Statement.h
	g++ -g -Wall -c PrintStatement.cpp -o PrintStatement.o

PrintAllStatement.o: PrintAllStatement.h PrintAllStatement.cpp Statement.h
	g++ -g -Wall -c PrintAllStatement.cpp -o PrintAllStatement.o

ProgramState.o: ProgramState.h ProgramState.cpp
	g++ -g -Wall -c ProgramState.cpp -o ProgramState.o

ReturnStatement.o: ReturnStatement.h ReturnStatement.cpp Statement.h
	g++ -g -Wall -c ReturnStatement.cpp -o ReturnStatement.o

Statement.o: Statement.h Statement.cpp
	g++ -g -Wall -c Statement.cpp -o Statement.o

.PHONY: clean
clean:
	rm -rf *.o