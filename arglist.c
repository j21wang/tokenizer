#include <stdio.h>

int main( int argc, char ** argv )
{
	int i;

	for ( i = 0 ; i < argc ; i++ )
	{
		printf("newline is %d",'\n');
		printf( "command line argv[%d] is %s\n", i, argv[i] );
	}
	return 0;
}
