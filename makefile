# general dirs
SRC_DIR:=src
OUT_DIR:=bin
OBJ_DIR:=$(OUT_DIR)/obj

# base files and dirs
BASE_DIR:=$(SRC_DIR)/base
BASE_SRC:=$(wildcard $(BASE_DIR)/*.c)
BASE_OBJ:=$(addprefix $(OBJ_DIR)/, $(notdir $(BASE_SRC:.c=.o)))

#commandline version files and dirs
CLI_DIR:=$(SRC_DIR)/cli
CLI_SRC:=$(wildcard $(CLI_DIR)/*.c)
CLI_OBJ:=$(addprefix $(OBJ_DIR)/, $(notdir $(CLI_SRC:.c=.o)))

#gui version files and dirs
GUI_DIR:=$(SRC_DIR)/gui
GUI_HDR:=$(wildcard $(GUI_DIR)/*.h)
GUI_MOC:=$(addprefix $(GUI_DIR)/moc_, $(notdir $(GUI_HDR:.h=.cpp)))
GUI_SRC:=$(filter-out $(GUI_MOC), $(wildcard $(GUI_DIR)/*.cpp)) $(GUI_MOC)
GUI_OBJ:=$(addprefix $(OBJ_DIR)/, $(notdir $(GUI_SRC:.cpp=.o)))

# C compiler
CC:=gcc
CC_FLAGS:= -Wall -c -I $(BASE_DIR)
LC_FLAGS:= -Wall -I $(BASE_DIR)

# Qt specifics
Q_INC:=-I/usr/include/qt4/ -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui
Q_LIB:=-lQtGui -lQtCore
QMOC:=/usr/bin/moc-qt4

# C++ compiler
CXX:=g++
CXX_FLAGS:=-Wall -c -std=c++11 $(Q_INC) $(Q_LIB) -I $(BASE_DIR)
LXX_FLAGS:=-Wall -std=c++11 $(Q_INC) $(Q_LIB) -I $(BASE_DIR)

# default
all: chemtool

# make the commandline version
chemtool: base $(CLI_OBJ)
	$(CC) $(LC_FLAGS) -o $(OUT_DIR)/$@ $(BASE_OBJ) $(CLI_OBJ)

$(OBJ_DIR)/%.o: $(CLI_DIR)/%.c
	$(CC) $(CC_FLAGS) -o $@ $<

# make the gui version
gchemtool: base qmoc $(GUI_OBJ)
	$(CXX) $(LXX_FLAGS) -o $(OUT_DIR)/$@ $(BASE_OBJ) $(GUI_OBJ)

$(OBJ_DIR)/%.o: $(GUI_DIR)/%.cpp
	$(CXX) $(CXX_FLAGS) -o $@ $<

# make the base object files
base: $(BASE_OBJ)

$(OBJ_DIR)/%.o: $(BASE_DIR)/%.c
	$(CC) $(CC_FLAGS) -o $@ $<

# run qt-moc
qmoc: $(GUI_MOC)

$(GUI_DIR)/moc_%.cpp: $(GUI_DIR)/%.h
	$(QMOC) $< -o $@

# remove all files genereated by the compiler
clean: objclean mocclean gchclean
	rm -rf $(filter-out $(OUT_DIR)/elemdb.csv $(OBJ_DIR), \
		$(wildcard $(OUT_DIR)/*))

# remove all object files
objclean:
	rm -rf $(wildcard $(OBJ_DIR)/*)

# remove all files made by qt-moc
mocclean:
	rm -f $(wildcard $(GUI_DIR)/moc_*.cpp)

# remove all .gch files
gchclean:
	rm -f $(wildcard $(BASE_DIR)/*.gch)