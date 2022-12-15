#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define SIZE1 5
#define SIZE1 99

void print2DArray(int arr[SIZE1][SIZE1]){
    for(int r = 0; r < SIZE1; r++){
        for(int c = 0; c < SIZE1; c++){
            printf("%d ", arr[r][c]);
        }
        printf("\n");
    }
}

int getCount(int arr[SIZE1][SIZE1]){
    // print2DArray(arr);
    int count = 0;
    for(int r = 1; r < SIZE1-1; r++){
        for(int c = 1; c < SIZE1-1; c++){
            // printf("r: %d c: %d\n", r, c);
            int row = r-1;
            int col = c;
            int vU = 1;
            int vL = 1;
            int vR = 1;
            int vD = 1;
            while(row>=0){
                if(arr[row][col] >= arr[r][c]){
                    // printf("invisible at r: %d c: %d row: %d col: %d\n", r, c, row, col);
                    vL = 0;
                    break;
                }
                row--;
            }
            row = r+1;
            col = c;
            while(row<SIZE1){
                if(arr[row][col] >= arr[r][c]){
                    // printf("invisible at r: %d c: %d row: %d col: %d\n", r, c, row, col);
                    vR = 0;
                    break;
                }
                row++;
            }
            row = r;
            col = c-1;
            while(col>=0){
                if(arr[row][col] >= arr[r][c]){
                    // printf("invisible at r: %d c: %d row: %d col: %d\n", r, c, row, col);
                    vU = 0;
                    break;
                }
                col--;
                
            }
            row = r;
            col = c+1;
            while(col<SIZE1){
                if(arr[row][col] >= arr[r][c]){
                    // printf("invisible at r: %d c: %d row: %d col: %d\n", r, c, row, col);
                    // printf("arr[%d][%d]: %d\n", row, col, arr[row][col]);
                    // printf("arr[r][c]: %d\n", arr[r][c]);
                    vD = 0;
                    break;
                }
                col++;
            }
            if(vR || vL || vU || vD){
                // printf("is visible\n");
                count++;
            }
        }
    }
    return count;
}

int getCount2(int arr[SIZE1][SIZE1]){
    // print2DArray(arr);
    int count = 0;
    for(int r = 1; r < SIZE1-1; r++){
        for(int c = 1; c < SIZE1-1; c++){
            // printf("At r: %d c: %d\n", r, c);
            int vU = 1;
            int row = r-1;
            int col = c;
            while(row > 0 && arr[r][c] > arr[row][col]){
                // printf("Checking up: tree[%d][%d] = %d\n", row, col, arr[row][col]);
                vU++;
                row--;
            }

            int vD = 1;
            row = r+1;
            col = c;
            // printf("test: row: %d col: %d r: %d c: %d\n", row, col, r, c);
            while(row < SIZE1-1 && arr[r][c] > arr[row][col]){
                // printf("Checking down: tree[%d][%d] = %d\n", row, col, arr[row][col]);
                vD++;
                row++;
            }

            int vL = 1;
            row = r;
            col = c-1;
            while(col > 0 && arr[r][c] > arr[row][col]){
                // printf("Checking left: tree[%d][%d] = %d\n", row, col, arr[row][col]);
                vL++;
                col--;
            }

            int vR = 1;
            row = r;
            col = c+1;
            while(col < SIZE1-1 && arr[r][c] > arr[row][col]){
                // printf("Checking right: tree[%d][%d] = %d\n", row, col, arr[row][col]);
                vR++;
                col++;
            }

            // printf("Found count to be: %d x %d x %d x %d = %d\n", vU, vL, vD, vR, (vR * vL * vU * vD));

            if(vR * vL * vU * vD > count){
                count = vR * vL * vU * vD;
            }
        }
    }
    return count;
}

int main(void)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    int c1 = 0;
    int c2 = 0;

    int trees[SIZE1][SIZE1];

    fp = fopen("aoc2022Day8Input.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    int lineNumber = 0;

    while ((read = getline(&line, &len, fp)) != -1) {
        
        int init_size = strlen(line);
        
        for(int i = 0; i < init_size; i++){
            trees[lineNumber][i] = line[i]-'0';
        }
        lineNumber++;

    }

    // print2DArray(trees);

    c1+=getCount(trees);
    c1+= 4*(SIZE1-1);

    c2 += getCount2(trees);

    printf("Part 1: %d\nPart 2: %d\n", c1, c2);

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}