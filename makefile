#Compiler is cc
CC:=cc

#Files to compiled. 
#Use all header and c files in src/ dir except main.c and python_wrapper.c.
#These included based on the target
FILES:=$(wildcard src/*.c src/*.h) 
FILES:=$(filter-out src/main.c src/python_wrapper.c, $(FILES))

#Output directory
#Use '.' to output to current directory
OUTDIR:=bin

#Name of the output
OUTNAME:=$(OUTDIR)/chemtool

#Compiler flags
CFLAGS:=-Wall

#If no target is specified report an error
all:
	$(error No target selected)

#Remove all compiled files from OUTDIR
clean:
	rm $(OUTNAME)*

#Normal commandline build
cli:
	$(CC) $(FILES) src/main.c $(CFLAGS) -o $(OUTNAME)

#Commandline debug build - use '$ make dbg'
dbg:
	$(CC) $(FILES) src/main.c $(CFLAGS) -g -o $(OUTNAME)

#Python module build.
pymod:
	$(CC) $(FILES) src/python_wrapper.c -shared -I/usr/include/python2.7/ $(CFLAGS) -o $(OUTNAME).so
