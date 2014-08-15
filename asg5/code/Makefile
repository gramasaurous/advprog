# Graham Greving
# ggreving@ucsc.edu
# asg5: Makefile

GPP        = g++ -g -O0 -Wall -Wextra -std=gnu++11

DEPFILE    = Makefile.dep
HEADERS    = sockets.h signal_action.h cix_protocol.h logstream.h util.h
CPPLIBS    = sockets.cpp signal_action.cpp cix_protocol.cpp util.cpp
CPPSRCS    = ${CPPLIBS} cix-daemon.cpp cix-client.cpp cix-server.cpp
LIBOBJS    = ${CPPLIBS:.cpp=.o}
CLIENTOBJS = cix-client.o ${LIBOBJS}
SERVEROBJS = cix-server.o ${LIBOBJS}
DAEMONOBJS = cix-daemon.o ${LIBOBJS}
OBJECTS    = ${CLIENTOBJS} ${SERVEROBJS} ${DAEMONOBJS}
EXECBINS   = cix-client cix-server cix-daemon
LISTING    = Listing.ps
SOURCES    = ${HEADERS} ${CPPSRCS} Makefile README

CLASS       = cmps109-wm.u14
PROJECT     = asg5

all: ${DEPFILE} ${EXECBINS}

cix-client: ${CLIENTOBJS}
	${GPP} -o $@ ${CLIENTOBJS}

cix-server: ${SERVEROBJS}
	${GPP} -o $@ ${SERVEROBJS}

cix-daemon: ${DAEMONOBJS}
	${GPP} -o $@ ${DAEMONOBJS}

%.o: %.cpp
	${GPP} -c $<

test : ${EXECBINS}
	cp cix-server ../test/remote
	cp cix-daemon ../test/remote
	cp cix-client ../test/local1
	cp cix-client ../test/local2

clean:
	- rm ${OBJECTS}

spotless: clean
	- rm ${EXECBINS}

submit : ${SOURCES}
	- checksource ${SOURCES}
	submit ${CLASS} ${PROJECT} ${SOURCES}

dep:
	- rm ${DEPFILE}
	make --no-print-directory ${DEPFILE}

${DEPFILE}:
	${GPP} -MM ${CPPSRCS} >${DEPFILE}

again: ${SOURCES}
	make --no-print-directory spotless all

include ${DEPFILE}

