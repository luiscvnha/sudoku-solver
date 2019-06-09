#ifndef general_h
#define general_h


#define SIZE				9			// size of the grid

#define EMPTY				0			// empty field

#define OUT_OF_MEMORY		255			// out of memory error


typedef unsigned char Byte;

typedef char* String;
typedef const char* constString;

typedef enum {false = 0, true = 1} Bool;

typedef Byte Grid[SIZE][SIZE];


#endif
