#Compiler is cc
CC:=cc

#Source file dir
SRCDIR:=src

#Files to compiled. 
#Use all header and c files in src/ dir except main.c and python_wrapper.c.
#These included based on the target
FILES:=$(wildcard $(SRCDIR)/*.c src/*.h) 
FILES:=$(filter-out $(SRCDIR)/cli_main.c $(SRCDIR)/gui_main.cpp, $(FILES))

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
	$(CC) $(FILES) $(SRCDIR)/cli_main.c $(CFLAGS) -o $(OUTDIR)/chemtool

#Commandline debug build - use '$ make dbg'
dbg:
	$(CC) $(FILES) $(SRCDIR)/cli_main.c $(CFLAGS) -g -o $(OUTDIR)/chemtool

#Gui build
gui:
	g++ $(FILES) -I/usr/share/qt4/include $(SRCDIR)/gui_main.cpp $(CFLAGS) -o $(OUTDIR)/gchemtool
