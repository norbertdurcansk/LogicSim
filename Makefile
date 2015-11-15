CC = g++ 
CFLAGS  = -std=c++11 -Wall -Wextra -pedantic -O2 


default: logicSim

logicSim:  logicSim.o 
	@$(CC) $(CFLAGS)  logicSim.o  -o logicSim -lsimlib -lm
	@-rm -rf result
	@mkdir result 	

logicSim.o:   logicSim.cpp 
	@$(CC) $(CFLAGS)  -c logicSim.cpp  -lsimlib -lm 

clean:
	@$(RM) logicSim *.o *~
	@-rm -rf result
	@$(RM) examples/*~
run:
	@test -s logicSim || { echo "Execution file does not exist"; exit 1; }
	@-rm -rf result
	@mkdir result
	@chmod 777 logicSim
	@chmod 777 plotgen.sh
	@./plotgen.sh

