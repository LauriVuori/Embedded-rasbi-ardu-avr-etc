#Here we specify compiler
CC = gcc
#Here we define include dir
INCLUDE = ./include
SRC=./src/
#This is for debugging purposes
#CFLAGS = -g -c -Wall -I$(INCLUDE)
#This is for release purposes
#CFLAGS = -O -c -Wall -I$(INCLUDE)

#Here we define compilation flags. 
#-c is to create the .o file(s)
#-I is to include the header directory 
CFLAGS = -c -I$(INCLUDE) -lpthread



#We could have also mentioned the list of source files 
#SOURCES =  profession.cpp employee.cpp main.cpp

#$(patsubst pattern,replacement,text)
#Below we assume that the .cpp source files are under $(SRC) directory
OBJECTS := $(patsubst %.c,%.o,$(wildcard $(SRC)*.c))

#Here we rename object files by replacing .cpp by .o of files.
#OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = runserver

#Here we define all rule and its dependencies
all: $(OBJECTS) $(EXECUTABLE)

# The $@ refers to the left side of : 
$(EXECUTABLE) : $(OBJECTS)
		$(CC) $(OBJECTS) -o $@ $(LIBS) -lpthread

#The $< refers to the first item in the dependency list
#The $@ refers the target file, file.o.
#This is a suffix rule telling how to turn .cpp into .o file
.c.o: *.h
	$(CC) $(CFLAGS) $< -o $@

clean :
	-rm -f $(OBJECTS) $(EXECUTABLE)


#Here we define a new rule by combining two predefined rules
full: all clean