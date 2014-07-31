#
# test all shapes
# 
# shape
#    text
#    ellipse (w,h)
#       circle (r)
#    polygon (x0,y0,x1,y1 ...)
#       rectangle (w, h)
#          square (w)
#       diamond (w, h)
#       triangle (x0,y0,x1,y1,x2,y2)
#          right_triangle (w,h)
#          isosceles (w,h)
#          equilateral (w)
#
define title text Helvetica-18 Shape Test!
define e  ellipse 			50 200
define c  circle 				100
define p  polygon 			0 0 20 60 60 80 50 50 80 50 70 30 90 30
define r  rectangle 			30 70
define s  square				15
define d  diamond				378.764 31.3333
define t  triangle 			0 0 300 300 450 900
define rt right_triangle 	150 300.1
define it isosceles		 	150 300.1
define et equilateral	 	150

border LemonChiffon 1

draw NavajoWhite 		title 270 460
draw MintCream 		p 		320 240
draw cornsilk3 		e 		530 200
draw cornsilk2 		c 		110 360
draw DarkOliveGreen1	r 		100 100
draw chartreuse1 		s 		330 380
draw DarkGoldenrod2	d 		405 329
draw tomato3 			t 		300 90
draw LightPink1		rt 	300 90
draw LightPink2		it 	200 90
draw LightPink3		et 	100 90
