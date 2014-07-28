# Graham Greving
# ggreving@ucsc.edu
# asg4: Makefile

MKFILE      = Makefile
DEPFILE     = ${MKFILE}.dep
NOINCL      = ci clean spotless
NEEDINCL    = ${filter ${NOINCL}, ${MAKECMDGOALS}}
GMAKE       = ${MAKE} --no-print-directory
COMPILECPP  = g++ -g -O0 -Wall -Wextra -std=gnu++11
MAKEDEPCPP  = g++ -MM -std=gnu++11

MODULES     = debug graphics interp rgbcolor shape util
CPPHEADER   = ${MODULES:=.h}
CPPSOURCE   = ${MODULES:=.cpp} main.cpp
TEMPLATES   = util.tcc
GENFILES    = colors.cppgen
OTHERS      = ${MKFILE} README mk-colors.perl
ALLSOURCES  = ${CPPHEADER} ${TEMPLATES} ${CPPSOURCE} ${OTHERS}
EXECBIN     = gdraw
OBJECTS     = ${CPPSOURCE:.cpp=.o}
LINKLIBS    = -lGL -lGLU -lglut -lm

HOST 		= $(findstring ucsc,$(shell hostname))
TARFILE		= $(PROJECT).tar.gz
CLASS       = cmps109-wm.u13
PROJECT     = asg3

all : ${EXECBIN}
ifeq ($(HOST),ucsc)
	- checksource ${ALLSOURCES}
endif

${EXECBIN} : ${OBJECTS}
	${COMPILECPP} -o $@ ${OBJECTS} ${LINKLIBS}

%.o : %.cpp
	${COMPILECPP} -c $<

colors.cppgen: mk-colors.perl
	mk-colors.perl >colors.cppgen

clean :
	- rm ${OBJECTS} ${DEPFILE} core ${GENFILES}

spotless : clean
	- rm ${EXECBIN} ${LISTING} ${LISTING:.ps=.pdf}


submit : ${ALLSOURCES}
ifeq ($(HOST),ucsc)
	- checksource ${ALLSOURCES}
	submit ${CLASS} ${PROJECT} ${ALLSOURCES}
endif

cp : tar
	scp ${TARFILE} ggreving@unix.ucsc.edu:Private/${PROJECT}

tar : 
	tar cvf ${TARFILE} ${ALLSOURCES}

dep : ${CPPSOURCE} ${CPPHEADER} ${GENFILES}
	@ echo "# ${DEPFILE} created `LC_TIME=C date`" >${DEPFILE}
	${MAKEDEPCPP} ${CPPSOURCE} >>${DEPFILE}

${DEPFILE} :
	@ touch ${DEPFILE}
	${GMAKE} dep

again :
	${GMAKE} spotless dep all

man :
	man ../asg4-oop-inheritance.tt

ifeq (${NEEDINCL}, )
include ${DEPFILE}
endif

