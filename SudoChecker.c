#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define max 9   //number of slots in a row/column

/*
Program takes an valid input file of foramt specified in the assignment. It will create one parent thread which spawns
27 other worker threads to check the requirements for Sudoku Vailidity.
*/

const char take[4] = " \\t";
int i, j, colc, rowc, subc = 0;     //counter for columns, rows, subs
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
        //printf("Read Line: %s\n", line);
        ptr = strtok(line, take);
        sudoku[i][j++] = atoi(ptr);
        //printf("ptr: %d\n", atoi(ptr));
        while(NULL != (ptr = strtok(NULL, take))){
            sudoku[i][j] = atoi(ptr);
            //printf("ptr: %d\n", sudoku[i][j]);
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
    int top = data -> topRow;
    int bottom = data -> bottomRow;
    int left = data -> leftColumn;
    int right = data -> rightColumn;
    int i;
    for (i = 0; i <= max - 1; i++){
        int cell = sudoku[i][left];
    }
}

void *checkRow( void *element){
    elements *data = (elements *) element;
    int start = data -> leftColumn;
    int end = data -> rightColumn;
    int row = data ->topRow;
    int i;
    for (i = start; start <= end; start++){
        int cell = sudoku[row][start];
    }
}

void *checkGrids ( void *element){
    elements *data = (elements *) element;
    int start = data -> leftColumn;
    int end = data -> rightColumn;
    int top = data ->topRow;
    int bot = data -> bottomRow;
    int i;
    for (i = start; start <= end; start++){
        int cell = sudoku[i][end];
    }
}

int main(int argc, char *argv[])
{

    char *file_name = "";
    if(argc > 1){
        file_name = argv[1];
    } else { file_name = "SudokuPuzzle.txt"; }
    open_read(file_name);
    //printSudo();

    pthread_t tid_row[max], tid_col[max], tid_subgrid[max];
    //thread creation
    int l;
    for(l = 0; l < 9; l++){
        int m;
        for (m = 0; m < 9; m++){
            if( m%3 == 0 && m%3 == 0){
                elements *gridData = (elements *)malloc(sizeof(elements));
                gridData -> topRow = l;
                gridData -> bottomRow = l + 2;
                gridData -> leftColumn = m;
                gridData -> rightColumn = m + 2;
                pthread_create(&tid_subgrid[subc++], NULL, checkGrids, gridData);
                printf("%ld\n", tid_subgrid[subc-1]);
            }
            if(l = 0){
                elements *colData = (elements *)malloc(sizeof(elements));
                colData -> topRow = l;
                colData -> bottomRow = max - 1;
                colData -> leftColumn = m;
                colData -> rightColumn = m;
                printf("colthread\n");
                pthread_create(&tid_col[colc++], NULL, checkColumn, colData);
            }
            if(m = 0){
                elements *rowData = (elements *)malloc(sizeof(elements));
                rowData -> topRow = l;
                rowData -> bottomRow = l;
                rowData -> leftColumn = m;
                rowData -> rightColumn = max - 1;
                printf("rowthread\n");
                pthread_create(&tid_row[rowc++], NULL, checkRow, rowData);
            }
            
        }
    }
}


/* get thread id for tid array
pthread_id_np_t   tid;
tid = pthread_getthreadid_np();
*/