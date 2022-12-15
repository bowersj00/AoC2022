#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHECK_CYCLE_NUM if((cycle-20) % 40 == 0){c1+=x*cycle;}
#define CHECK_SPRITE if(abs((cycle%40)- x - 1) < 2){pixels[cycle/40][(cycle%40)-1]++;}

#define CHECKS cycle++; CHECK_CYCLE_NUM CHECK_SPRITE

void printPixels(int pixels[6][40]){
    printf(".........................................\n");
    for(int r = 0; r < 6; r++){
        printf(".");
        for(int c = 0; c < 39; c++){
            if(pixels[r][c] > 0){
                printf("#");
            }else{
                printf(".");
            }
        }
        printf(".\n");
    }
    printf(".........................................\n");
}

int main(void)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    int c1 = 0;

    int cycle = 0;
    int x = 1;

    int pixels[6][40] = {0};

    fp = fopen("aoc2022Day10Input.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {

        if(line[0] == 'a'){
            CHECKS
            CHECKS
            int num;
            sscanf(line, "addx %d", &num);
            x+=num;
        }else{
            CHECKS
        }
    }

    printf("Part 1: %d\nPart 2:\n", c1);
    printPixels(pixels);
    printf("\n");

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}