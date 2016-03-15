CXX=g++
INC=../base ../net
SUBDIR=../base
CFLAGS= -Wall -g --std=c++11

test:main.o ${SUBDIR}/timer.o
	$(CXX) $(CFLAGS) -o $@ $^
%.o: %.cpp
	$(CXX) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	rm -f test
	rm -f main.o ${SUBDIR}/timer.o
