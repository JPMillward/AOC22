/*
    BrokenMaze
*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

void FreePointerArray( void** Pointers );

char** ReadLinesFromFile( const char* FilePath, size_t* FileSize, size_t* LineCount, int MaxLines );

int SearchFor( const char* pattern, const char* searchstring, char** result, int maxmatchcount );
