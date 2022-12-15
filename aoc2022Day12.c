#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    int c1 = 0;
    int c2 = 0;

    fp = fopen("aoc2022Day12Input.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        
    }

    printf("Part 1: %d\nPart 2: %d\n", c1, c2);

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}