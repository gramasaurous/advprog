#!/usr/bin/perl
# $Id: pkeyvalue.perl,v 1.1 2010-02-12 13:40:44-08 - - $
#
# Documentation:  see assignment specifications.
#
use strict;
use warnings;

$0 =~ s|^(.*/)([^/]+)/*$|$2|;
my $exit_status = 0;
END {exit $exit_status}
$SIG{'__WARN__'} = sub {print STDERR "$0: @_"; $exit_status = 1};
$SIG{'__DIE__'} = sub {warn @_; exit};

my %map;

sub printkeyval ($) {
   my ($key) = @_;
   my $val = $map{$key};
   print $key, defined $val ? " = $val\n" : ": key not found\n";
}

for my $filename (@ARGV ? @ARGV : "-") {
   open my $file, "<$filename" or do {warn "$filename: $!\n"; next};
   while (defined (my $line = <$file>)) {
      chomp $line;
      printf "%s: %d: %s\n", $filename, $., $line;
      next if $line =~ m/^\s*(#|$)/;
      my ($key, $val) = map {m/^\s*(.*?)\s*$/g} split m/=/, $line, 2;
      unless (defined $val) {
         printkeyval $key;
      }elsif (length $key) {
         if ($key eq "/") {
            map {printkeyval $_ unless length $val and $map{$_} ne $val}
                sort {$b cmp $a} keys %map; }
         elsif (length $val) {
            $map{$key} = $val; printkeyval $key;
         }else {
            delete $map{$key}
         }
      }else {
         map {printkeyval $_ unless length $val and $map{$_} ne $val}
             sort keys %map; }
   }
}

