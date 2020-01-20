#!/usr/bin/perl
# Palette-merges images using imagemagick.

# Generate palette
print( "Making palette...\n" );
my @names = <*.png>;
my $all_names = join( " ", @names );
system( "convert $all_names +append pal_images/pal.png" );
system( "convert pal_images/pal.png +dither -colors 255 pal_images/pal_reduced.png" );

foreach(@names) {
	print( "Converting $_...\n" );
	system( "convert $_ +dither -map pal_images/pal_reduced.png pal_merged/$_" );
}