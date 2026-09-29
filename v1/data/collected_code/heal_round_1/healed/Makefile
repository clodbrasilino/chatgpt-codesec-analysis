CC:= gcc-13
# Sources are all .c files in this dir
SRCS := $(wildcard *.c)
# Object files are everything in $SRCS, with the .c replaced by a .o
OBJS := $(patsubst %.c, %.o, $(SRCS))
 
# Default target makes the executable, so you just type 'make' at the command line
default : $(OBJS)
 
# Make every .o file require it's corresponding .c file
# Use the requisite ($<) as input (the .c file)
# Use the target name ($@) as the output file name (the .o file)
%.o : %.c
	-$(CC) $< -o $@