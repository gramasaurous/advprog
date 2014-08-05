# $Id: rectilinear.gd,v 1.2 2014-08-04 18:15:54-07 - - $
# Some rectilinear symbols
define rect rectangle 100 50
define squ square 75
define card diamond 50 100
define tri triangle 0 0 100 50 0 60
define iso isosceles 100 120
define equi equilateral 100 
draw cyan rect 100 100
draw cyan squ 200 100
draw cyan card 300 100
draw magenta tri 100 300
draw magenta iso 200 300
draw magenta equi 300 300
