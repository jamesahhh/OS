#include <stdio.h>
#include <stdlib.h>

#define max 9   //number of slots in a row/column
#define true 1  //non-zero is true
#define false 0 //zero is false

/*
Program takes an input file of foramt specified in the assignment. It will create one parent thread which spawns
27 other worker threads to check the requirements for Sudoku Vailidity.
*/

int sudoku[max][max];
int columnsChecked[max];
int rowsChecked[max];
int subsChecked[max];

typedef struct elements
{
    int topRow;
    int bottomRow;
    int leftColumn;
    int rightColumn;
} elements;

int main(int argc, char **argv[])
{
    char *file_name;
    int c;
    FILE *fp;

    file_name = argv[1];
    fp = fopen(file_name, "r");
    if (fp == NULL)
    {
        perror("Error while opening the file: Does not exist.");
        return -1;
    }
    while (!feof(fp))
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                sudoku[i][j] = fgetc(fp);
            };
        };
    };

    for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                printf(sudoku[i][j]);
            };
            printf("\n");
        };
    
};

/* get thread id for tid array
pthread_id_np_t   tid;
tid = pthread_getthreadid_np();
*/