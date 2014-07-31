#!/usr/bin/perl
# Graham Greving
# ggreving@ucsc.edu
# asg4:mk-colors.perl

use strict;
use warnings;

my %colors;
my $f1 = "../opengl-examples/rgb.txt";
my $f2 = "/usr/share/X11/rgb.txt";
open RGB_TXT, "<$f1" or open RGB_TXT, "<$f2" or die "$0: $f1: $!";
while (my $line = <RGB_TXT>) {
   $line =~ m/^\s*(\d+)\s+(\d+)\s+(\d+)\s+(.*)/
         or die "$0: invalid line: $line";
   my ($red, $green, $blue, $name) = ($1, $2, $3, $4);
   $name =~ s/\s+/-/g;
   $colors{$name} = [$red, $green, $blue];
}
close RGB_TXT;

print "/* Data taken from source file $f1 or $f2.*/\n";
print "const unordered_map<string,rgbcolor> color_names = {\n";
printf "   {%-24s, rgbcolor (%3d, %3d, %3d)},\n",
                  "\"$_\"", @{$colors{$_}}
       for sort {lc $a cmp lc $b} keys %colors;
print "};\n";

