#!perl
# depend on gs = git's ROOT
my $gs = @ENV{gs};
my $filename = ""; 
my $comment = "";

if ( @ARGV == 0 ){
	print "- error , need at least 1 args\n\tperl git_push.PL txt.txt 'edit_log'\n"; 
	exit 1;
}

$filename = @ARGV[0];

my @ARGV_MUST_BE_FILES = ();
if ( @ARGV == 1 ){
	@ARGV_MUST_BE_FILES = @ARGV;
	$comment = &get_timestamp();
}
elsif (@ARGV >= 2){
	@ARGV_MUST_BE_FILES = @ARGV[0..@ARGV-1-1];
	if (! -e @ARGV[-1]){
		$comment = @ARGV[-1];
	}
	else {
		@ARGV_MUST_BE_FILES = @ARGV;		
		$comment = &get_timestamp();
	}
}

$filename = "@ARGV_MUST_BE_FILES";
my $git_add_cmd = qq( git add  $filename );  # need first add 
my $git_commit_cmd =  qq( git commit $filename -m) . qq(') . $comment . qq(') ; 

#print $git_commit_cmd , "\n"; 
system( $git_add_cmd );
system( $git_commit_cmd );
system( " expect $gs/perl_p/git_push.exp "); 




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
