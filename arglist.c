#include <stdio.h>

int main( int argc, char ** argv )
{
	int i;

	printf("double quote is %d\n",'"');
    printf("double quote with slash is %d\n", '\"');
    
	for ( i = 0 ; i < argc ; i++ )
	{
		printf( "command line argv[%d] is %s\n", i, argv[i] );
	}
	return 0;
}
