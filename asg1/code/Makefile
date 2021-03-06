# Graham Greving
# ggreving@ucsc.edu


MKFILE      = Makefile
DEPFILE     = ${MKFILE}.dep
NOINCL      = submit git clean spotless
NEEDINCL    = ${filter ${NOINCL}, ${MAKECMDGOALS}}
GMAKE       = ${MAKE} --no-print-directory

COMPILECPP  = g++ -g -O0 -Wall -Wextra -rdynamic -std=gnu++11
MAKEDEPCPP  = g++ -MM

CPPSOURCE   = commands.cpp debug.cpp inode.cpp util.cpp main.cpp
CPPHEADER   = commands.h debug.h inode.h util.h
EXECBIN     = yshell
OBJECTS     = ${CPPSOURCE:.cpp=.o}
OTHERS      = ${MKFILE} README
ALLSOURCES  = ${CPPHEADER} ${CPPSOURCE} ${OTHERS}
LISTING     = Listing.ps

all: ${EXECBIN}
#	- checksource ${ALLSOURCES}

${EXECBIN}: ${OBJECTS}
	${COMPILECPP} -o $@ ${OBJECTS}

%.o: %.cpp
	${COMPILECPP} -c $<

#ci: ${ALLSOURCES}
#	cid + ${ALLSOURCES}
#	- checksource ${ALLSOURCES}

lis: ${ALLSOURCES}
	mkpspdf ${LISTING} ${ALLSOURCES} ${DEPFILE}

clean:
	- rm ${OBJECTS} ${DEPFILE} core ${EXECBIN}.errs

spotless: clean
	- rm ${EXECBIN} ${LISTING} ${LISTING:.ps=.pdf}

dep: ${CPPSOURCE} ${CPPHEADER}
	@ echo "# ${DEPFILE} created `LC_TIME=C date`" >${DEPFILE}
	${MAKEDEPCPP} ${CPPSOURCE} >>${DEPFILE}

${DEPFILE}: ${MKFILE}
	@ touch ${DEPFILE}
	${GMAKE} dep

again:
	${GMAKE} spotless dep all lis

git:
	git commit

submit: spotless
	submit 

ifeq (${NEEDINCL}, )
include ${DEPFILE}
endif

