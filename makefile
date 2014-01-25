#Compiler is cc
CC=cc

#Files to compiled. 
#Just use all c and header files in 'src' directory for now.
FILES=src/*.c src/*.h

#Output directory
#Use '.' to output to current directory
OUTDIR=bin

#Name of the output
OUTNAME=chemtool

#Compiler flags
CFLAGS=-o $(OUTDIR)/$(OUTNAME) -Wall

#Normal build
all:
	$(CC) $(FILES) $(CFLAGS)

#Debug build - use '$ make dbg'
dbg:
	$(CC) $(FILES) $(CFLAGS) -g
