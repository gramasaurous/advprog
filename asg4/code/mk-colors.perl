#!/usr/bin/perl
# $Id: mk-colors.perl,v 1.3 2014-05-21 15:40:52-07 - - $
use strict;
use warnings;

my %colors;
my $file = "/usr/share/X11/rgb.txt";
open RGB_TXT, "<$file" or die "$0: $file: $!";
while (my $line = <RGB_TXT>) {
   $line =~ m/^\s*(\d+)\s+(\d+)\s+(\d+)\s+(.*)/
         or die "$0: invalid line: $line";
   my ($red, $green, $blue, $name) = ($1, $2, $3, $4);
   $name =~ s/\s+/-/g;
   $colors{$name} = [$red, $green, $blue];
}
close RGB_TXT;

print "// Data taken from source file $file\n";
print "const unordered_map<string,rgbcolor> color_names = {\n";
printf "   {%-24s, rgbcolor (%3d, %3d, %3d)},\n",
                  "\"$_\"", @{$colors{$_}}
       for sort {lc $a cmp lc $b} keys %colors;
print "};\n";

