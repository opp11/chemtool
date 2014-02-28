#Compilers
CC:=cc
CXX:=g++

#Source file dir
SRCDIR:=src

#Files to compiled.
GUIFILES:=$(SRCDIR)/gui_main.cpp $(SRCDIR)/gui_main.h $(SRCDIR)/moc_gui_main.cpp
CLIFILES:=$(SRCDIR)/cli_main.c
FILES:=$(wildcard $(SRCDIR)/*.c src/*.h) 
FILES:=$(filter-out $(GUIFILES) $(CLIFILES), $(FILES))

#Qt variables
QINCPATH:=-I/usr/include/qt4/ -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui
QLIBPATH:=-lQtGui -lQtCore
QMOC:=/usr/bin/moc-qt4

#Output directory
#Use '.' to output to current directory
OUTDIR:=bin

#Compiler flags
CCFLAGS:=-Wall -fPIC
CXXFLAGS:=-Wall --std=c++11

#If no target is specified report an error
all:
	$(error No target selected)

#Remove all compiled files from OUTDIR
clean:
	rm -rf $(filter-out $(OUTDIR)/elemdb.csv, $(wildcard $(OUTDIR)/*))

#Normal commandline build
cli:
	$(CC) $(FILES) $(CLIFILES) $(CCFLAGS) -o $(OUTDIR)/chemtool

#Commandline debug build - use '$ make dbg'
cli_dbg:
	$(CC) $(FILES) $(CLIFILES) $(SRCDIR)/cli_main.c $(CCFLAGS) -g -o $(OUTDIR)/chemtool

#Gui build
gui: qt_moc
	$(CXX) $(FILES) $(GUIFILES) $(QINCPATH) $(QLIBPATH) $(CXXFLAGS) -o $(OUTDIR)/gchemtool
	rm -f $(SRCDIR)/moc_gui_main.cpp
qt_moc:
	$(QMOC) $(SRCDIR)/gui_main.h $(QINCPATH) -o $(SRCDIR)/moc_gui_main.cpp
