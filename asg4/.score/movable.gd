# $Id: movable.gd,v 1.1 2014-05-20 14:06:02-07 - - $
# Some things to check on moving.
define sq square 90
define ci circle 90
draw red sq 100 100
draw green sq 300 100
draw blue sq 500 100
draw cyan ci 100 300
draw magenta ci 300 300
draw yellow ci 500 300
border white 8
moveby 10
#
# Grader, test each of the arrow keys and hjkl to
# see if the selected object moves around.
#
# Press nnn and ppp to see if different objects are selected.
# Press the digit keys to see if objects are selected.
# Objects are numbered 0 to 5.
# Pressing keys 6 to 9 should have no effect.
#
