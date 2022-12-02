#include "utilities.h"

void FreePointerArray( void** Pointers )
{
    int pointerCount = 0;
    while( Pointers[ pointerCount ] )
    {
        free( Pointers[ pointerCount ] );
        ++pointerCount;
    }

    free( Pointers );
    printf( "Freed %d Pointers and their Array\n", pointerCount );
    return;
}


char** ReadLinesFromFile( const char* FilePath, size_t* FileSize, size_t* LineCount, int MaxLines )
{
    FILE* File = fopen( FilePath, "r" );
    *LineCount = 0;
    *FileSize = 0;
    size_t LineSize = 0;
    char** Lines = ( char** ) malloc( sizeof( char* ) * MaxLines );

    while( *LineCount < MaxLines && ( LineSize = getline( &Lines[ *LineCount ], &LineSize, File ) ) != EOF )
    {
        ++*LineCount;
        *FileSize += LineSize;
    }
    if ( *LineCount < MaxLines )
    {
        Lines[ *LineCount ] = NULL; //intended
    }
 
    Lines = realloc( Lines, sizeof( char* ) * *LineCount + 1  );
    return Lines;
}


int SearchFor( const char* pattern, const char* searchstring, char** result, int maxmatchcount )
{
    /* Function that wraps the regular expression library
        TODO: Parameterize regcomp & regexec flagss
    */
    int bufferSize = 100; //Used for regerror
    regmatch_t matches[ maxmatchcount ]; //expected matches
    regex_t expression; //The regular expression

    int32_t isSuccess = regcomp( &expression, pattern, REG_EXTENDED );
    if ( isSuccess != 0 )
    {
        *result =  ( char* ) malloc( bufferSize );
        regerror( isSuccess, &expression, *result, bufferSize );
        regfree( &expression );
        return isSuccess;
    }

    isSuccess = regexec( &expression, searchstring, maxmatchcount, ( regmatch_t* ) &matches, 0 );
    if ( isSuccess != 0 )
    {
        *result = ( char* ) malloc( bufferSize );
        regerror( isSuccess, &expression, *result, bufferSize );
        regfree( &expression );
        return isSuccess;
    }

    //Allocate match memory
    *result = ( char* ) malloc( ( expression.re_nsub + 1 ) * sizeof( char* ) ); //char is always 1;

    for ( int index = 0; index <= expression.re_nsub; index++ )
    {
        int32_t start = ( int ) matches[ index ].rm_so; //start of regex submatch
        int32_t finish = ( int ) matches[ index ].rm_eo; //end of regex submatch
        result[ index ] = ( char* ) malloc( ( finish - start ) + 1 );
        memcpy( ( void* ) result[ index ], ( void* ) &searchstring[ start ], finish - start );
        result[ index ][ finish - start ] = '\0';
    }
    regfree( &expression );
    return isSuccess;
}
