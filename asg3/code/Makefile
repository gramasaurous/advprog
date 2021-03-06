# Graham Greving
# ggreving@ucsc.edu
# Makefile

# By default, gmake sets the variable ${CXX}=g++ on a Linux system.
# To use Sun Studio C++ (CC), set the variable CXX=CC, either on
# the command line when calling make, or in an environment variable.

MKFILE      = Makefile
DEPFILE     = ${MKFILE}.dep
NOINCL      = ci clean spotless
NEEDINCL    = ${filter ${NOINCL}, ${MAKECMDGOALS}}
GMAKE       = ${MAKE} --no-print-directory

COMPILECPP  = g++ -g -O0 -Wall -Wextra -std=gnu++0x
MAKEDEPCPP  = g++ -MM

CPPHEADER   = listmap.h trace.h util.h xless.h xpair.h
TEMPLATES   = listmap.tcc util.tcc
CPPSOURCE   = trace.cpp util.cpp main.cpp
ALLCPPSRC   = ${CPPHEADER} ${TEMPLATES} ${CPPSOURCE}
OBJECTS     = ${CPPSOURCE:.cpp=.o}
EXECBIN     = keyvalue
OTHERS      = ${MKFILE} README
ALLSOURCES  = ${ALLCPPSRC} ${OTHERS}

HOST 		= $(findstring ucsc,$(shell hostname))
WARNING 	= $(error CANNOT SUBMIT, NOT ON UNIX.UCSC)
SUBMIT 		= submit cmps109-wm.u14 asg3

TARFILE		= asg3.tar.gz

all : ${EXECBIN}
ifeq ($(HOST),ucsc)
	- checksource ${ALLSOURCES}
endif

${EXECBIN} : ${OBJECTS}
	${COMPILECPP} -o $@ ${OBJECTS}

%.o : %.cpp
	${COMPILECPP} -c $<

git :
	- git commit -a

clean :
	- rm ${OBJECTS} ${DEPFILE} core

spotless : clean
	- rm ${EXECBIN}

dep : ${ALLCPPSRC}
	@ echo "# ${DEPFILE} created `LC_TIME=C date`" >${DEPFILE}
	${MAKEDEPCPP} ${CPPSOURCE} >>${DEPFILE}

submit : spotless
ifeq ($(HOST),ucsc)
	${SUBMIT} ${CPPSOURCE} ${CPPHEADER} ${OTHERS}
endif

cp : tar
	scp ${TARFILE} ggreving@unix.ucsc.edu:Private/

tar : 
	tar cvf ${TARFILE} ${ALLSOURCES}

test:
	./${EXECBIN} file.in

${DEPFILE} :
	@ touch ${DEPFILE}
	${GMAKE} dep

again :
	${GMAKE} spotless dep all

ifeq (${NEEDINCL}, )
include ${DEPFILE}
endif

