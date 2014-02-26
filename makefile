#Compiler is cc
CC:=cc

#Python "compiler"
PYC:=python ~/PyInstaller-2.1/pyinstaller.py

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

#Compiler flags
CFLAGS:=-Wall

#If no target is specified report an error
all:
	$(error No target selected)

#Remove all compiled files from OUTDIR
clean:
	rm -rf $(filter-out $(OUTDIR)/elemdb.csv, $(wildcard $(OUTDIR)/*))

#Normal commandline build
cli:
	$(CC) $(FILES) $(SRCDIR)/main.c $(CFLAGS) -o $(OUTDIR)/chemtool

#Commandline debug build - use '$ make dbg'
dbg:
	$(CC) $(FILES) $(SRCDIR)/main.c $(CFLAGS) -g -o $(OUTNAME)/chemtool

