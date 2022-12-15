#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    int count = 0;

    fp = fopen("aoc2022Day2Input.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        int roundScore = 0;
        
        roundScore = (line[2] == 'X') ? 0 : ((line[2] == 'Y') ? 3 : 6);

        if(roundScore == 0){
            if(line[0] == 'A'){
                roundScore += 3;
            }else if(line[0] == 'B'){
                roundScore += 1;
            }else{
                roundScore += 2;
            }
        }else if(roundScore == 3){
            if(line[0] == 'A'){
                roundScore += 1;
            }else if(line[0] == 'B'){
                roundScore += 2;
            }else{
                roundScore += 3;
            }
        }else{
            if(line[0] == 'A'){
                roundScore += 2;
            }else if(line[0] == 'B'){
                roundScore += 3;
            }else{
                roundScore += 1;
            }
        }
        count += roundScore;

    }

    printf("Part 1: %d\n", count);

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}