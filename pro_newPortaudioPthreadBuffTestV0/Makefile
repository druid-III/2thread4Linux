################################################################################
################################################################################
##  developed by DRUID's labs.                                                ##
##  druid3@i.ua or druidthree@gmail.com                                       ##
##  http://dsp.la.net.ua                                                      ##
##                                                                            ##
##                 00  000   0  0  0  000   0   000                           ##
##                000  0  0  0  0  0  0  0     00        *******              ##
##               0100  000   0  0  0  0  0       00     * ****  *             ##
##              01100  0  0   000  0  000      000     *  *   *  *            ##
##             011 00                                  *  ****   *            ##
##            011  00     11   1      111               * *   * *             ##
##           00000000    1  1  111   11                  *******              ##
##          00000000011  1111  1  1    11                                     ##
##          11111111111  1  1  111   111                                      ##
##                                                                            ##
################################################################################
################################################################################
# Clean plus automated Makefile 4 C&C++ (prg) 
# distributed under GNU GPL v.3

WHERE_IS_GCC       = /usr/bin/
WHERE_IS_COLOR_GCC = /usr/bin/
# /usr/local/bin/

INCLUDE = -I/opt/local/include/ -I/usr/local/include/
#-I../src/include -I/usr/src/linux/include/

WHOAMI := $(shell whoami)
YORN   := $(shell if [ -d ./libs ] ; then echo yes; else echo no; fi)
COLOR  := $(shell if [ -f /usr/bin/colorgcc ] ; then echo yes; else echo no; fi)
TODOINS = /usr/local/bin

ifneq ($(COLOR), yes)
CC            = $(WHERE_IS_GCC)gcc
CPP           = $(WHERE_IS_GCC)g++
STRIP         = $(WHERE_IS_GCC)strip
else
CC            = $(WHERE_IS_COLOR_GCC)colorgcc
CPP           = $(WHERE_IS_COLOR_GCC)colorgcc
STRIP         = strip
endif

CC_FLAGS      = -O2                                                            \
                -W                                                             \
                -Wall                                                          \
                -Winline                                                       \
                -Wmissing-noreturn                                             \
                -Wmissing-prototypes                                           \
                -Wnested-externs                                               \
                -Wconversion                                                   \
                -Wfloat-equal                                                  \
                -Wshadow                                                       \
                -Wsequence-point                                               \
                -pipe                                                          \
                $(INCLUDE)

LD_FLAGS      = -L./LIB/ -L/opt/local/lib/ $(ALIB) $(DLIB)
DLIB          = -pthread -lportaudio 
ALIB          =


PRG_NAME      = newPortaudioBuffTest

PRJDIRS       = ./OBJ                                                          \
                ./ASM                                                          \
                ./LIB

OBJFILES     := $(patsubst %.c,   ./OBJ/%.o,       $(wildcard *.c))
OBJFILES     += $(patsubst %.cpp, ./OBJ/%.o,       $(wildcard *.cpp))
OBJFILES     += $(patsubst %.s,   ./OBJ/%.o,       $(wildcard *.s))

C2ASM        := $(patsubst %.c,   ./ASM/%.S,       $(wildcard *.c))
CPP2ASM      := $(patsubst %.cpp, ./ASM/%.S,       $(wildcard *.cpp))

#  include <bla-bla-bla> error and stop if *.mk not available
# -include <bla-bla-bla> work if *.mk not available
-include ./options/options.mk

all: prj_dirs make_lib myprog show_src run_script

#PRG----------------------------------------------------------------------------
myprog: $(OBJFILES) 
	$(CC) -o $(PRG_NAME) $(OBJFILES) $(LD_FLAGS)

./OBJ/%.o: %.c
	$(CC) $(CC_FLAGS) -c -o $@ $<
./OBJ/%.o: %.cpp
	$(CPP) $(CC_FLAGS) -c -o $@ $<
./OBJ/%.o: %.s  
	$(CC) -o $@ -c $<
	
#-------------------------------------------------------------------------------

run: all
	./run

src2asm: c2asm cpp2asm

c2asm: $(C2ASM)

./ASM/%.S: %.c
	$(CC) -o $@ -S -fverbose-asm $<
	
cpp2asm: $(CPP2ASM)

./ASM/%.S: %.cpp
	$(CPP) -o $@ -S -fverbose-asm $<


prj_dirs:
	@$(foreach DIR, $(PRJDIRS),                                                    \
	if ! test -d $(DIR);                                                           \
		then                                                                   \
			mkdir $(DIR);                                                  \
			chmod 775 $(DIR);                                              \
		else                                                                   \
			echo ' $(DIR) directory already is available ';                \
	fi;                                                                            \
	)

run_script:
	@if ! test -f ./run;                                                           \
	then                                                                           \
		touch ./run;                                                           \
		chmod 775 ./run;                                                       \
		echo '#!/bin/bash'                                   >> ./run;         \
		echo 'echo "starting ..."'                           >> ./run;         \
		echo 'export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./LIB' >> ./run;         \
		echo 'exec ./$(PRG_NAME) $$@'                        >> ./run;         \
	else                                                                           \
		echo ' run-file exists ';                                              \
	fi

#-------------------------------------------------------------------------------
# * !!! <attention> !!!
# <ALL the source code from this directory join to the project.>
# * !!! <attention> !!!
show_src:
	@echo "-------------------------------------------------------------------------------"
	@echo "src in project:"
	@echo
	@for i in `ls *.[c,h,s] *.[c,h]?*`;                                                     \
		do                                                                              \
			echo $${i};                                                             \
		done
	@echo "-------------------------------------------------------------------------------"
#-------------------------------------------------------------------------------
count:
	@wc -l *.[c,h,s] *.[c,h]?*

archive_tar: clean
	@tar -cvf  ../$(PRG_NAME)__`date +%y.%m.%d`.tgz     ./ --recursion -P

archive_targz: clean
	@tar -zcvf ../$(PRG_NAME)__`date +%y.%m.%d`.tar.gz  ./ --recursion -P
	
archive_tarbz2: clean
	@tar -jcvf ../$(PRG_NAME)__`date +%y.%m.%d`.tar.bz2 ./ --recursion -P

archive_zip: clean
	@zip -r    ../$(PRG_NAME)__`date +%y.%m.%d`.zip     ./ 

clean:
	@rm -f $(PRG_NAME) run
	@$(foreach DIR, ./ $(PRJDIRS), rm -f                                       \
	                                     $(DIR)/*.o                            \
	                                     $(DIR)/*.d                            \
	                                     $(DIR)/*.map                          \
	                                     $(DIR)/*.hex                          \
	                                     $(DIR)/*.listing                      \
	                                     $(DIR)/*.bak                          \
	                                     $(DIR)/*.out                          \
	                                     $(DIR)/*.swp                          \
	                                     $(DIR)/*~                             \
	                                     $(DIR)/core                           \
	                                     $(DIR)/*.tu                           \
	  )

striping:
	@$(STRIP) ./$(PRG_NAME)

doc++:
	@doc++ --all --html --tables-border --private --dir ./DOC *.[c,h,s] *.[c,h]?*
	
gnu_style:
	@astyle --style=gnu `ls *.[c,h]?*`
	@rm -f *.orig


install:
ifeq ($(WHOAMI), root)
	cp -if ./$(PRG_NAME) $(TODOINS)
else
	@echo Sorry, you do not have root right
endif

uninstall:
ifeq ($(WHOAMI), root)
	rm -f  $(TODOINS)/$(PRG_NAME)
else
	@echo Sorry, you do not have root right
endif

make_lib:
ifeq ($(YORN), yes)
	$(MAKE) -C ./LIB/
endif
	
.PHONY: all
.PHONY: make_lib
.PHONY: myprog
.PHONY: run
.PHONY: src2asm
.PHONY: prj_dirs
.PHONY: run_script
.PHONY: show_src
.PHONY: count
.PHONY: archive_tar
.PHONY: archive_targz
.PHONY: archive_tarbz2
.PHONY: archive_zip
.PHONY: clean
.PHONY: striping
.PHONY: doc++
.PHONY: install
.PHONY: uninstall

