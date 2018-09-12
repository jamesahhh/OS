#include <stdio.h>

#define max 9
#define true 1
#define false 0

/*
Program takes an input file of foramt specified in the assignment. It will create one parent thread which spawns
27 other worker threads to check the requirements for Sudoku Vailidity.
*/

int sudoku[max][max];
int columnsChecked[max];
int rowsChecked[max];
int subsChecked[max];

typedef struct {
    int topRow;
    int bottomRow;
    int leftColumn;
    int rightColumn;
};

int main( int argc, char **argv[] ){
    
}

/* get thread id for tid array
pthread_id_np_t   tid;
tid = pthread_getthreadid_np();
*/