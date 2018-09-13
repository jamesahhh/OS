#include <stdio.h>
#include <stdlib.h>

#define max 9   //number of slots in a row/column
#define true 1  //non-zero is true
#define false 0 //zero is false

/*
Program takes an valid input file of foramt specified in the assignment. It will create one parent thread which spawns
27 other worker threads to check the requirements for Sudoku Vailidity.
*/

const char take[2] = "\\t";
char line[50], *ptr = NULL;
int i, j = 0;
int sudoku[max][max];
int columnsChecked[max];
int rowsChecked[max];
int subsChecked[max];

typedef int boolean;
typedef struct elements
{
    int topRow;
    int bottomRow;
    int leftColumn;
    int rightColumn;
} elements;

int main(int argc, char **argv[])
{
    char *file_name = argv[1];
    open_read(file_name);
    printSudo();
};

void open_read(const char* file_name){
    char c;
    int current;
    FILE *fp = fopen(file_name, "r");
    if (!fp)
    {
        perror("Error while opening the file: Does not exist.");
        exit(-1);
    };
    while(EOF != fscanf(stdin, "%s", line)){
        printf("\n Read Line: %s\n", line);
        ptr = strtok(line, take);
        sudoku[i][j++] = ptr;
        //printf(sudoku[i][j-1]);
        while(NULL != (ptr = strtok(NULL, take))){
            sudoku[i][j] = ptr;
            //printf("inside");
            //printf(sudoku[i][j]);
            j++;
        };
        j = 0;
        i++;
    };
    fclose(fp);
};

void printSudo(){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j<9; j++){
            printf(sudoku[i][j]);
        };
        printf("\n");
    };
};

/* get thread id for tid array
pthread_id_np_t   tid;
tid = pthread_getthreadid_np();
*/