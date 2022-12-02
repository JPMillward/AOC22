/*
    BrokenMaze
*/
#include "utilities.c"

#define JHIN 4444 //Best ADC Execute

int SortInto( int Value, int* Array, int ArraySize )
{
    /* Take in a pointer and an Array to an int
       Returns the position of the value or -1 */
    int ValueLocation = -1;
    int Index = 0;
    for( int Index = 0; Index < ArraySize; Index++ )
    {
        if( Value < Array[ Index ] )
        {
            continue;
        }
        else if( Index == 0 )
        {
            Array[ Index ] = Value;
        }
        else
        {
            Array[ Index - 1 ] = Array[ Index ];
            Array[ Index ] = Value;
        }
        ValueLocation = Index;
    }

    return ValueLocation;
}


int DayOne( char** Input, int ArraySize )
{
    //Puzzle Vars
    int* FattestElves = ( int* ) calloc( ArraySize, sizeof( int ) ); //assign and init memory to 0
    int MostCalories = 0;
    int ElfCalories = 0;
    
    //Parsing
    const char* digits = "^[[:digit:]]+"; //From the start of string match [0-9] at least once
    int success; // 0 is true in c
    
    int Index = 0;
    while( Input[ Index ] ) 
    {
        char* result;
        success = SearchFor( digits, Input[ Index ], &result, 1 ); 
        if( success != 0 ) //If we don't find a number it's a new line
        {
            SortInto( ElfCalories, FattestElves, ArraySize );
            ElfCalories = 0;
        }
        else
        {
            ElfCalories += atoi( result );
        }
        free( result );
        ++Index;
    }

    Index = 0;
    while( Index < ArraySize )
    {
        MostCalories += FattestElves[ Index ];
        ++Index;
    }
    free( FattestElves ); 
    return MostCalories;
}


int main()
{
    int answer;
    const char* path = "../inputs/day1.txt";
    size_t FileSize; //will store size of file.
    size_t TotalLines; //Stores total number of lines
    char** input = ReadLinesFromFile( path, &FileSize, &TotalLines, JHIN ); //Read Entire file or 4444 Lines
    
    answer = DayOne( input, 1 );
    printf( "Answer to Part One is: %d\n", answer);
    answer = DayOne( input, 3 );
    printf( "Answer to Part Two is: %d\n", answer );
    FreePointerArray( ( void** ) input );
}