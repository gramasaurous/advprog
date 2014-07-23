# $Id: nested.gd,v 1.1 2014-05-20 15:25:19-07 - - $
# Testing some nested shapes.
define x64 ellipse 640 480
define x48 ellipse 480 360
define x32 ellipse 320 240
define x24 ellipse 240 180
define x16 ellipse 160 120
define x12 ellipse 120  90
draw red x64 320 240
draw green x48 320 240
draw blue x32 320 240
draw red x24 320 240
draw green x16 320 240
draw blue x12 320 240
