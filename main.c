#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define FIB_N   40

unsigned long
fib( int n )
{
    if( n < 0 )     return 0;
    if( n == 0 )    return 1;
    if( n == 1 )    return 1;
    if( n > 1 )     return fib( n-1 ) + fib( n-2 );
}

int
thread( void* arg )
{
    int i = 0;
    unsigned long    ret = 0;

    printf( "sub thread fib calc start...\n" );
    for( i = 0; i < FIB_N; i++ )
    {
//        printf( "for:%d\n", i );
        ret = fib( i );
//        printf( "fib(%d)=%lu\n", i, ret );
    }
    printf( "sub thread fib calc finish!\n" );
    printf( "finish thread!\n" );

    return 0;
}

int
main( void )
{
    int         ret = 0;
    pthread_t   th;

    ret = pthread_create(   &th,
                            NULL,
                            ( void* )thread,
                            NULL );

    printf( "main thread sleep...\n" );
    sleep( 1 );
    printf( "main thread wake up!\n" );

    printf( "do thread cancel.\n" );
    pthread_cancel( th );

    pthread_join( th, NULL );

    return 0;
}

