#!/usr/bin/perl
# Adds a default GRIT snippet to every image in gfx,
# and outputs the list of bitmaps.
# This makes bitmaps suitable for sprites, if you want backgrounds, add
# a -gb to the grit file.

my $grit_default = <<ENDGRIT
# 8 bit bitmap
-gB8

ENDGRIT
;

my @names = <*.png>;

foreach(@names) {
	my $gritname = $_;
	$gritname =~ s/\.png$/.grit/;	
	if( !-e $gritname ) {
		open my $GRIT, ">", $gritname;
		print $GRIT $grit_default;
		close $GRIT;
	}
	my $binname = $_;
        $binname =~ s/\.png$/.bin/;
	print "$_ ";
}
print "\n";
