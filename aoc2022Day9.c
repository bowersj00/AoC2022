#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1000

int countBoard(int board[SIZE][SIZE]){
    int count = 0;
    for(int r = 0; r < SIZE; r++){
        for(int c = 0; c < SIZE; c++){
            if(board[r][c] != 0){
                count++;
            }
        }
    }
    return count;
}

void checkTail(int *hX, int *hY, int *tX, int *tY){
    int dX = *hX - *tX;
    int dY = *hY - *tY;

    if(dX>1 && dY == 0){
        (*tX)++;
    }else if(dX < -1 && dY == 0){
        (*tX)--;
    }else if(dY > 1 && dX == 0){
        (*tY)++;
    }else if(dY < -1 && dX == 0){
        (*tY)--;
    }

    if((dX > 1 && dY > 0) || (dX > 0 && dY > 1)){
        (*tX)++;
        (*tY)++;
    }else if((dX < -1 && dY < 0) || (dX < 0 && dY < -1)){
        (*tX)--;
        (*tY)--;
    }if((dX > 1 && dY < 0) || (dX > 0 && dY < -1)){
        (*tX)++;
        (*tY)--;
    }else if((dX < -1 && dY > 0) || (dX < 0 && dY > 1)){
        (*tX)--;
        (*tY)++;
    }
}

int main(void){
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    int c1 = 0;
    int c2 = 0;

    int board[SIZE][SIZE] = {{0}};
    int board2[SIZE][SIZE] = {{0}};

    int hX = SIZE/2;
    int hY = SIZE/2;
    int tX = SIZE/2;
    int tY = SIZE/2;

    int spots[10][2] = {{SIZE/2, SIZE/2}, {SIZE/2, SIZE/2}, {SIZE/2, SIZE/2}, 
                        {SIZE/2, SIZE/2}, {SIZE/2, SIZE/2}, {SIZE/2, SIZE/2}, 
                        {SIZE/2, SIZE/2}, {SIZE/2, SIZE/2}, {SIZE/2, SIZE/2}, {SIZE/2, SIZE/2}};

    fp = fopen("aoc2022Day9Input.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        int times;
        char move;
        sscanf(line, "%s %d", &move, &times);

        for(int i = 0; i < times; i++){
            if(move == 'U'){
                hY--;
                spots[0][1]--;
            }else if(move == 'L'){
                hX--;
                spots[0][0]--;
            }else if(move == 'D'){
                hY++;
                spots[0][1]++;
            }else if(move == 'R'){
                hX++;
                spots[0][0]++;
            }

            checkTail(&hX, &hY, &tX, &tY);
            board[tX][tY]++;
            for (int j = 0; j < 9; j++){
                checkTail(&spots[j][0], &spots[j][1], &spots[j+1][0], &spots[j+1][1]);
                if(j==8){
                    board2[spots[j+1][0]][spots[j+1][1]]++;
                }
            }
        }
    }

    c1 = countBoard(board);
    c2 = countBoard(board2);

    printf("Part 1: %d\nPart 2: %d\n", c1, c2);

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}