CC = g++ 
CFLAGS  = -std=c++11 -Wall -Wextra -pedantic -O2 

default: logicSim

logicSim:  logicSim.o 
	$(CC) $(CFLAGS)  logicSim.o  -o logicSim -lsimlib -lm 

logicSim.o:   logicSim.cpp 
	$(CC) $(CFLAGS)  -c logicSim.cpp  -lsimlib -lm 

clean:
	$(RM) logicSim *.o *~

