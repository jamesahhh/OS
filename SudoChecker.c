#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max 9   //number of slots in a row/column

/*
Program takes an valid input file of foramt specified in the assignment. It will create one parent thread which spawns
27 other worker threads to check the requirements for Sudoku Vailidity.
*/

const char take[4] = " \\t";
int i, j = 0;
char line[50], *ptr = NULL;
int sudoku[max][max];
int columnsChecked[max];
int rowsChecked[max];
int subsChecked[max];

typedef enum { false, true}  bool;
typedef struct elements
{
    int topRow;
    int bottomRow;
    int leftColumn;
    int rightColumn;
} elements;


void open_read(char *file_name){
    char c;
    int current;
    FILE *fp = fopen(file_name, "r");
    if (!fp)
    {
        perror("Error while opening the file: Does not exist.");
        exit(-1);
    }
    while(!feof(fp)){
        fgets(line, 50, fp);
        printf("Read Line: %s\n", line);
        ptr = strtok(line, take);
        sudoku[i][j++] = atoi(ptr);
        printf("ptr: %d\n", atoi(ptr));
        while(NULL != (ptr = strtok(NULL, take))){
            sudoku[i][j] = atoi(ptr);
            printf("ptr: %d\n", sudoku[i][j]);
            j++;
        }
        j = 0;
        i++;
    }
    fclose(fp);
}

void printSudo(){
    int i;
    for(i = 0; i < 9; i++){
        int j;
        for(j = 0; j<9; j++){
            printf("%d", sudoku[i][j]);
        }
        printf("\n");
    }
}

void *checkColumn( void *element){
    elements *data = (elements *) element;
    int start = data -> topRow;
    int end = data -> bottomRow;
    int col = data ->leftColumn;
    for (int i = start; start <= end; start++){
        int cell = sudoku[i][col];
    }
}

void *checkRow( void *element){
    elements *data = (elements *) element;
    int start = data -> leftColumn;
    int end = data -> rightColumn;
    int row = data ->topRow;
    for (int i = start; start <= end; start++){
        int cell = sudoku[row][start];
    }
}

void *checkGrids ( void *element){
    elements *data = (elements *) element;
    int start = data -> leftColumn;
    int end = data -> rightColumn;
    int top = data ->topRow;
    int bot = data -> bottomRow;
    for (int i = start; start <= end; start++){
        int cell = sudoku[i][col];
    }
}

int main(int argc, char *argv[])
{
    char *file_name = "";
    if(argc > 1){
        file_name = argv[1];
    } else { file_name = "SudokuPuzzle.txt"; }
    open_read(file_name);
    printSudo();
}


/* get thread id for tid array
pthread_id_np_t   tid;
tid = pthread_getthreadid_np();
*/