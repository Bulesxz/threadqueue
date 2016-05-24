#DEBUGFALG=DEBUG
DEBUGFALG=RELEASE
CXXFLAGS = -Wall -g -std=c++11 -D$(DEBUGFALG)
LDFLAGS = -L/usr/lib64/mysql/  -lmysqlclient
BASEDIR= ../base
THREADDIR=../thread
INCPATH = -I $(BASEDIR) -I$(THREADDIR)
TAGTET=main

SRCS:=$(wildcard *.cpp) $(wildcard $(BASEDIR)/*.cpp) $(wildcard $(THREADDIR)/*.cpp)
OBJS := $(patsubst %.cpp,%.o ,$(SRCS))

#
#none:
#	@echo "objs : " $(OBJS) "src: " $(SRCS)

$(TAGTET):$(OBJS)
	g++  $(CXXFLAGS) $(LDFLAGS) -o $(TAGTET) $(OBJS)

%.o:%.cpp
	g++  $(CXXFLAGS) $(LDFLAGS) $(INCPATH) -c $< -o $@

.PHONY : clean
clean :
	rm  -rf $(OBJS)
	rm $(TAGTET)
