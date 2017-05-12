#!perl

my $filename = ""; 
my $comment = "";

if (@ARGV>2 || @ARGV<1){
	print "- error , need 2 args\n\tperl git_push.PL txt.txt 'edit_log'\n"; 
	exit 1;
}

$filename = @ARGV[0];

if ( @ARGV == 1){
	$comment = &get_timestamp();
}

if ( @ARGV == 2){
 $comment = @ARGV[1];
}

system ( qq(git commit $filename -m) . qq(').$comment.qq(').qq(  -a ) ); 

system( " expect git_push.exp "); 




sub get_timestamp(){
	my $if_windows = 'False';
	$if_windows = "True"  if @ENV{WINDIR};



	my $time_stamp = `date "+%Y%m%d%H%M"` if $if_windows ne "True";

	if ( $if_windows eq "True"){
		my ($second, $minute, $hour, $date, $month, $yearOffset, $dayOfWeek, $dayOfYear, $daylightSavings) = localtime();
		# 17 16 20 24 7 116 3 236 1
		# 2016-08-24 20:16

		my $year = 1900 + $yearOffset;
		$month = $month + 1 ;
		$month = &add_zero_if_lt_10($month);
		$date = &add_zero_if_lt_10($date);
		$hour = &add_zero_if_lt_10($hour);
		$minute = &add_zero_if_lt_10($minute);
		$time_stamp = "$year$month${date}${hour}$minute";
	}

	chomp( $time_stamp );
	return "".$time_stamp;

}
