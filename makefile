#Compiler is cc
CC:=cc

#Source file dir
SRCDIR:=src

#Files to compiled. 
#Use all header and c files in src/ dir except main.c and python_wrapper.c.
#These included based on the target
FILES:=$(wildcard $(SRCDIR)/*.c src/*.h) 
FILES:=$(filter-out $(SRCDIR)/main.c $(SRCDIR)/python_wrapper.c, $(FILES))

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
	rm $(OUTDIR)/gui.py
	rm $(OUTNAME)*

#Normal commandline build
cli:
	$(CC) $(FILES) $(SRCDIR)/main.c $(CFLAGS) -o $(OUTNAME)

#Commandline debug build - use '$ make dbg'
dbg:
	$(CC) $(FILES) $(SRCDIR)/main.c $(CFLAGS) -g -o $(OUTNAME)

#Python module build.
pymod:
	$(CC) $(FILES) $(SRCDIR)/python_wrapper.c -shared -I/usr/include/python2.7/ $(CFLAGS) -o $(OUTNAME).so -fPIC 
	cp $(SRCDIR)/gui.py $(OUTDIR)/gui.py
