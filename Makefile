CC= g++	
CFLAGS= -Wall -pedantic 

SRC= ./src/main.cpp \

OBJ= $(SRC:.cpp=.o)
	EXE= aarecovery

$(EXE): $(OBJ)
	$(CC) -o $@ $^

%.o : %.cpp
	$(CC) $(CFLAGS) -o $@ -c $< 

debug :
	gdb ./$(EXE)

tar :
	make clean
	#tar -vcf $(EXE).gz mtx src report/report.pdf makefile

clean :
	rm -vf $(EXE) ./src/*.o *.gz
