my @lines;

while(<>) {
	push @lines, $_;
}

for(my $i = 0; $i < length($lines[0]); $i++) {
	print "\"";
	print substr($lines[6], $i, 1);
	print substr($lines[5], $i, 1);
	print substr($lines[4], $i, 1);
	print substr($lines[3], $i, 1);
	print substr($lines[2], $i, 1);
	print substr($lines[1], $i, 1);
	print substr($lines[0], $i, 1);
	print "\" \\";
	print "\n";
}
