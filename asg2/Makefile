# $Id: Makefile,v 7.24 2013-10-17 15:32:22-07 - - $

ALL:= ${basename ${filter %.tex %.mm, ${shell ls -t}}}
NEW:= ${firstword ${ALL}}

GROFFDIR = /afs/cats.ucsc.edu/courses/cmps012b-wm/groff
DEPS     = ${GROFFDIR}/Tmac.mm-etc Makefile
GROFFMM  = groff -mgm -U -b -ww -F${GROFFDIR}/font -I${GROFFDIR}/tmac
PSOPTS   = -spte -Tps
HTOPTS   = -spte -Thtml
TTOPTS   = -st -Tlatin1 -P-cbuo
SQUEEZE  = perl -00pe0

newest : ${NEW}.tt ${NEW}.view ${NEW}.pdf

all : tt ps pdf

ps : ${ALL:%=%.ps}
tt : ${ALL:%=%.tt}
pdf : ${ALL:%=%.pdf}

% : %.view

%. : %.view

%.view : %.ps
	killps ghostview gs gv
	gv --scale=1.1 $< &

%.ps : %.dvi
	dvips -D9600 -Pcmz $< -o $@

%.dvi : %.tex
	cid + $<
	latex $<

%.ps : %.mm ${DEPS}
	cid + $<
	${GROFFMM} ${PSOPTS} -z -rRef=1 $< 2>$*.qrf
	cat -nv $*.qrf
	${GROFFMM} ${PSOPTS} $< >$@
	# Hack to make gv understand this is Letter paper.
	letterbbox $@
	rm -vf $*.qrf

%.tt : %.mm ${DEPS}
	${GROFFMM} ${TTOPTS} -z -rRef=1 $< 2>$*.qrf
	cat -nv $*.qrf
	${GROFFMM} ${TTOPTS} $< | ${SQUEEZE} >$@
	rm -vf $*.qrf

%.pdf : %.ps
	mkpdf $< &

%.html : %.mm ${DEPS}
	${GROFFMM} ${HTOPTS} -z -rRef=1 $< 2>$*.qrf
	cat -nv $*.qrf
	${GROFFMM} ${HTOPTS} $< >$@

.PRECIOUS: %.man
%.man : %.sman
	/usr/lib/sgml/sgml2roff $< >$@

%.html : %.txt
	txt2html $< >$@

