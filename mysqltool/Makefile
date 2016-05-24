CFLAGS = -Wall -g -std=c++11 
LDFLAGS = -L/usr/lib64/mysql/  -lmysqlclient

OBJS= main.o MysqlTool.o
TAGTET=main
#main:main.o MysqlTool.o
$(TAGTET):$(OBJS)
	g++  $(CFLAGS) $(LDFLAGS) -o $(TAGTET) $(OBJS)

%.o:%.cpp
	g++  $(CFLAGS) $(LDFLAGS) -c $< -o $@
#main.o:main.cpp  
#	g++  $(CFLAGS) $(LDFLAGS) -c main.cpp
#MysqlTool.o:MysqlTool.cpp 
#	g++  $(CFLAGS) $(LDFLAGS) -c MysqlTool.cpp

.PHONY : clean
clean :
	rm *.o
	rm $(TAGTET)
