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

#Python module build.
pymod:
	$(CC) $(FILES) $(SRCDIR)/python_wrapper.c -shared -I/usr/include/python2.7/ $(CFLAGS) -o $(OUTDIR)/chemtool.so -fPIC 
	cp $(SRCDIR)/gui.py $(OUTDIR)/gui.py

#Executable for the gui
pyexe: pymod
	$(PYC) bin/gui.py --windowed --name=gchemtool --distpath=bin/ --specpath=bin/tmp/ --workpath=bin/tmp/ --hidden-import=elemdb.csv --ascii
	cp bin/elemdb.csv bin/gchemtool/
	rm -r bin/tmp/
	rm bin/gui.py
	rm -f bin/chemtool.so
