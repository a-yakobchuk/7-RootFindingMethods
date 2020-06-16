CC = gcc
CFLAGS = -O1 -g -Wall -std=c99 -pedantic
SOURCE = rootfinding.c hw7.c eqn2solve.c
OBJ = $(patsubst %.c, %.o, $(SOURCE))
EXE = hw7
VALGRIND = valgrind --tool=memcheck --leak-check=yes --track-origins=yes 
RESULTS = out.txt
MEMTXT = mem.txt
VERB = -verbose

.SILENT:
all: $(EXE)

$(EXE): $(OBJ)
	@echo "Linking program"
	$(CC) $(OBJ) -lm -o $(EXE)

.c.o: 
	@echo "Compiling program $*.c"
	$(CC) $(CFLAGS) $*.c -c

test: $(EXE) 
	@echo "Testing bisection interval [-2.5,2.5]"
	./$(EXE) -bisection -tol 1E-6 -ga -2.5 -gb 2.5 $(VERB) > $(RESULTS) 
	@echo "Testing newton inital guess -1.5"
	./$(EXE) -newton -tol 1E-6 -ga -1.5 $(VERB) >> $(RESULTS) 
	@echo "Testing newton initial guess 1.5"
	./$(EXE) -newton -tol 1E-6 -ga 1.5 $(VERB) >> $(RESULTS) 
	@echo "Testing secant with [-1.5,-1.6]"
	./$(EXE) -secant -tol 1E-6 -ga -1.5 -gb -1.6 $(VERB) >> $(RESULTS) 
	@echo "Testing secant with [1.5,1.6]"
	./$(EXE) -secant -tol 1E-6 -ga 1.5 -gb 1.6 $(VERB) >> $(RESULTS) 
	@echo "check out.txt for results"

opts: $(EXE)	
	@echo "Running bisection tests..."
	./$(EXE) -b -tol 1E-6 -ga -2 -gb 3 -verb > $(RESULTS)
	./$(EXE) -b -t 1E-6 -g -2 -u 3 -v >> $(RESULTS)
	./$(EXE) -b -t 1E-6 -ba -2 -bb 3 -v >> $(RESULTS)
	@echo "Check out.txt for results"
#	cat $(RESULTS)

.PHONY: mem clean test all help
mem: $(EXE)
	@echo "running valgrind on bisection [-2.5,2.5]"
	$(VALGRIND) ./$(EXE) -bisection -tol 1E-6 -ga -2.5 -gb 2.5 -verb > $(MEMTXT) 2>&1
	@echo "running valgrind on secant [-1.5,-1.6]"
	$(VALGRIND) ./$(EXE) -secant -tol 1E-6 -ga -1.5 -gb -1.6 -verb >> $(MEMTXT) 2>&1
	@echo "running valgrind on newton -1.5"
	@echo "valgrind output in mem.txt"
	$(VALGRIND) ./$(EXE) -newton -tol 1E-6 -ga -1.5 -verb >> $(MEMTXT) 2>&1
#	cat $(MEMTXT)

clean: 
	-rm -f $(OBJ) $(EXE) $(RESULTS) $(MEMTXT)

help:
	@echo "make options are: all, clean, mem, test, opts"

