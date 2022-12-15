#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{

    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    int first = 0;
    int second = 0;
    int third = 0;
    int count = 0;

    fp = fopen("aoc2022Day1Input.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        // char delim[] = "x";
        // char *ptr = strtok(line, delim);


        if(line[0] != '\n'){
            count+=(int)atoi(line);
        }else{
            if(first<count){
                third = second;
                second = first;
                first = count;
            }else if(first==count){
                third = second;
                second = count;
            }else if(second < count){
                third = second;
                second = count;
            }else if(second==count){
                third = count;
            }else if(third < count){
                third = count;
            }
            count = 0;
        }
    }
    printf("Part 1: %d\nPart 2: %d\n", (first+second+third), count);

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}