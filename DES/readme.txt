
-------------------------------------ReadMe ( using ) --------------------------------------

Sample data is provided in keys.txt file
######################################  Encrypt :  #########################################

Provide basic inputs like:
-> Key ( 64 bit )
-> Message ( 64 bit )
-> PC1 ( for key initial permutation )( 8*8 )
-> PC2 ( for key final permutation ) ( 8*7 )
-> IP  ( for message initial permutation ) ( 8*8 )
-> IP2 ( for message final permutation ) ( 8*8 )
-> E ( expansion table ) ( 8*6 )
-> P ( after each round permutation for R'i ) ( 8*4 )
-> S1-S8 ( S boxes ) ( 4*16 )

Usage:
-> compile ( gcc encrypt.c )
-> run ( a.exe for windows ./a.out for unix )
-> for running with sample values add " < encrypt.txt " in the run command
	 ( a.exe < encrypt.txt )

######################################  Encrypt :  #########################################

######################################  Decrypt:  #########################################

Provide basic inputs like:
-> Key ( 64 bit )
-> Cipher text ( 64 bit )
-> PC1 ( for key initial permutation )( 8*8 )
-> PC2 ( for key final permutation ) ( 8*7 )
-> IP  ( for message initial permutation ) ( 8*8 )
-> IP2 ( for message final permutation ) ( 8*8 )
-> E ( expansion table ) ( 8*6 )
-> P ( after each round permutation for R'i ) ( 8*4 )
-> S1-S8 ( S boxes ) ( 4*16 )

Usage:
-> compile ( gcc decrypt.c )
-> run ( a.exe for windows ./a.out for unix )
-> for running with sample values add " < decrypt.txt " in the run command
	 ( a.exe < decrypt.txt )

######################################  Decrypt:  #########################################
