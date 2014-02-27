#Compilers
CC:=cc
CXX:=g++

#Source file dir
SRCDIR:=src

#Files to compiled. 
#Use all header and c files in src/ dir except main.c and python_wrapper.c.
#These included based on the target
FILES:=$(wildcard $(SRCDIR)/*.c src/*.h) 
FILES:=$(filter-out $(SRCDIR)/cli_main.c $(SRCDIR)/gui_main.cpp, $(FILES))

#Qt files
QINCPATH:=-I/usr/include/qt4/ -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui

#Qt libraries
QLIBPATH:=-lQtGui -lQtCore

#Output directory
#Use '.' to output to current directory
OUTDIR:=bin

#Compiler flags
CCFLAGS:=-Wall
CXXFLAGS:=-Wall --std=c++11

#If no target is specified report an error
all:
	$(error No target selected)

#Remove all compiled files from OUTDIR
clean:
	rm -rf $(filter-out $(OUTDIR)/elemdb.csv, $(wildcard $(OUTDIR)/*))

#Normal commandline build
cli:
	$(CC) $(FILES) $(SRCDIR)/cli_main.c $(CCFLAGS) -o $(OUTDIR)/chemtool

#Commandline debug build - use '$ make dbg'
dbg:
	$(CC) $(FILES) $(SRCDIR)/cli_main.c $(CCFLAGS) -g -o $(OUTDIR)/chemtool

#Gui build
gui:
	$(CXX) $(FILES)  $(QINCPATH) $(QLIBPATH) $(SRCDIR)/gui_main.cpp $(CXXFLAGS) -o $(OUTDIR)/gchemtool
