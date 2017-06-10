#!perl
use strict;
my $arg0=@ARGV[0];
my $pwd_=`pwd`;chmod($pwd_);

if ( @ARGV==0 ){
	$arg0=$pwd_;
	@ARGV[0]=$pwd_;
}

my $IP_ADDR = `ifconfig | grep 192.168 `; 
$IP_ADDR =~ s/^\s+?(\w)/\1/;
my @IP_arr = split m/ /, $IP_ADDR ; 
$IP_ADDR = @IP_arr[1];


my $user_name_host_name=`whoami`.'@'.$IP_ADDR;
$user_name_host_name =~ s/\n//g;

map{

my $abs_path=`readlink -f "$_"`;
chomp( $abs_path );
chomp( $abs_path );



my $scp_to_x = qq( scp -r $user_name_host_name:$abs_path \$t/ ). qq(\n);
my $scp_from_x = qq( scp -r \$t/xx $user_name_host_name:$abs_path ). qq(\n);

#my $print_out_scp_statement = ' scp -r '."$user_name_host_name:$abs_path";
#chomp($print_out_scp_statement);
chomp( $scp_to_x ); 
#chomp( $scp_from_x ); 

if ($scp_to_x =~ m/\n/){
print $scp_to_x;
#print $scp_from_x;
}
else{
print $scp_to_x;print "\n";
#print $scp_from_x;print "\n";
;
}

}@ARGV; 

print qq(\n);

map{

my $abs_path=`readlink -f "$_"`;
chomp( $abs_path );
chomp( $abs_path );



my $scp_to_x = qq( scp -r $user_name_host_name:$abs_path \$t/ ). qq(\n);
my $scp_from_x = qq( scp -r \$t/xx $user_name_host_name:$abs_path ). qq(\n);

#my $print_out_scp_statement = ' scp -r '."$user_name_host_name:$abs_path";
#chomp($print_out_scp_statement);
chomp( $scp_to_x ); 
chomp( $scp_from_x ); 

if ($scp_to_x =~ m/\n/){
#print $scp_to_x;
print $scp_from_x;
}
else{
#print $scp_to_x;print "\n";
print $scp_from_x;print "\n";
;
}

}@ARGV; 


