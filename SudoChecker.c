#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define max 9   //number of slots in a row/column

typedef enum { false, true}  bool;

typedef struct elements
{
    int topRow;
    int bottomRow;
    int leftColumn;
    int rightColumn;
} elements;
/*
Program takes an valid input file of foramt specified in the assignment. It will create one parent thread which spawns
27 other worker threads to check the requirements for Sudoku Vailidity.
*/

const char take[4] = " \\t";
int i, j, colc, rowc, subc = 0;     //counter for columns, rows, subs
char line[50], *ptr = NULL;
int sudoku[max][max];
bool columnsChecked[max];
bool rowsChecked[max];
bool subsChecked[max];

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
        //printf("Read Line: %s\n", line);              // debug line read
        ptr = strtok(line, take);
        sudoku[i][j++] = atoi(ptr);
        //printf("ptr: %d\n", atoi(ptr));               //display what is at strtok ptr
        while(NULL != (ptr = strtok(NULL, take))){      
            sudoku[i][j] = atoi(ptr);
            //printf("ptr: %d\n", sudoku[i][j]);        //Display whats put in cell
            j++;
        }
        j = 0;
        i++;
    }
    fclose(fp);
}

/**
 * 
 * Print Sudoku to make sure file read in correctly
 * Not used in final submission
 * */
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
    int slots[10] = {false};
    long id = pthread_self();
    int u;
    for (u = top; u < bottom; u++){
        int val = sudoku[u][left];
        if(slots[val] != false){
            printf("\n0x%lx TRow: %d, BRow: %d, LCol: %d, RCol: %d invalid!", id, top, bottom, left, right);
            pthread_exit(NULL);
        }else slots[val] = true;
    }
    columnsChecked[left] = true;
    printf("\n0x%lx TRow: %d, BRow: %d, LCol: %d, RCol: %d valid!", id, top, bottom, left, right);
    pthread_exit(NULL);
}

void *checkRow( void *element){
    elements *data = (elements *) element;
    int top = data -> topRow;
    int bottom = data -> bottomRow;
    int left = data -> leftColumn;
    int right = data -> rightColumn;
    bool slots[10] = {false};
    long id = pthread_self();
    int u;
    for (u = left; u <= right; u++){
        int val = sudoku[top][u];
        //printf("\nCheck Value: %d", val);         //debug
        if(slots[val] != false){
            printf("\n0x%lx TRow: %d, BRow: %d, LCol: %d, RCol: %d invalid!", id, top, bottom, left, right);
            pthread_exit(NULL);
        }else {
            slots[val] = true;
        }
    }
    rowsChecked[top] = true;
    printf("\n0x%lx TRow: %d, BRow: %d, LCol: %d, RCol: %d valid!", id, top, bottom, left, right);
    pthread_exit(NULL);
}

void *checkGrids ( void *element){
    elements *data = (elements *) element;
    int left = data -> leftColumn;
    int right = data -> rightColumn;
    int top = data ->topRow;
    int bottom = data -> bottomRow;
    bool slots[10] = {false};
    long id = pthread_self();
    int y;
    for (y = top; y <= bottom; y++){
        int z;
        for( z = left; z <= right; z++){
            int val = sudoku[y][z];
            if(slots[val] != false){
            printf("\n0x%lx TRow: %d, BRow: %d, LCol: %d, RCol: %d invalid!", id, top, bottom, left, right);
            pthread_exit(NULL);
            }else {
            slots[val] = true;
            }
        }
    }
    subsChecked[j++] = true;
    printf("\n0x%lx TRow: %d, BRow: %d, LCol: %d, RCol: %d valid!", id, top, bottom, left, right);
    pthread_exit(NULL);
}

void joinThreads(pthread_t threads[]){
    int b;
    for( b = 0; b< 9; b++){
        pthread_join(threads[0], NULL);
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

    pthread_t tid_row[max], tid_col[max], tid_subgrid[max], dummy[max];
    
    //thread creation and checking
    int count = 0;
    int l;
    for(l = 0; l < 9; l++){
        int m;
        for (m = 0; m < 9; m++){
            if( l%3 == 0 && m%3 == 0){
                //count++;
                elements *gridData = (elements *)malloc(sizeof(elements));
                gridData -> topRow = l;
                gridData -> bottomRow = l + 2;
                gridData -> leftColumn = m;
                gridData -> rightColumn = m + 2;
                pthread_create(&tid_subgrid[subc++], NULL, checkGrids, gridData);
                //printf("grid pass: %d tid: 0x%lx\n", count, tid_subgrid[subc-1]); //debug passes
            }
            if(l == 0){
                //count++;
                elements *colData = (elements *)malloc(sizeof(elements));
                colData -> topRow = l;
                colData -> bottomRow = max - 1;
                colData -> leftColumn = m;
                colData -> rightColumn = m;
                pthread_create(&tid_col[colc++], NULL, checkColumn, colData);
                //printf("col pass: %d tid: 0x%lxd\n", count, tid_col[colc-1]); //debug passes
            }
            if(m == 0){
                //count++;
                elements *rowData = (elements *)malloc(sizeof(elements));
                rowData -> topRow = l;
                rowData -> bottomRow = l;
                rowData -> leftColumn = m;
                rowData -> rightColumn = max - 1;
                pthread_create(&tid_row[rowc++], NULL, checkRow, rowData);
                //printf("row pass: %d tid: 0x%lxd\n", count, tid_row[rowc-1]); //debug passes
            }
            
        }
    }

    joinThreads(tid_subgrid);
    joinThreads(tid_col);
    joinThreads(tid_row);

    int f;
    for(f = 0; f < 9; f++){
        char *validity = "";
        if(columnsChecked[f] == true){
            validity = "valid";
        }else validity = "invalid";
        printf("\nSubgrid: 0x%lx %s", tid_subgrid[f], validity);
    }


    for(f = 0; f < 9; f++){
        char *validity = "";
        if(columnsChecked[f] == true){
            validity = "valid";
        }else validity = "invalid";
        printf("\nColumn: 0x%lx %s", tid_col[f], validity);
    }

    for(f = 0; f < 9; f++){
        char *validity = "";
        if(columnsChecked[f] == true){
            validity = "valid";
        }else validity = "invalid";
        printf("\nRow: 0x%lx %s", tid_row[f], validity);
    }
}


/* get thread id for tid array
pthread_id_np_t   tid;
tid = pthread_getthreadid_np();

can also put pointer into pthread_id array
*/