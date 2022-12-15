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


    fp = fopen("aoc2022Day4Input.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        
        int init_size = strlen(line);
        
        int a, b, c, d;
        sscanf(line, "%d-%d,%d-%d", &a, &b, &c, &d);

        if(a>=c && b<=d){
                c1++;
        }else if(c>=a && d<=b){
                c1++;
        }

        if(a>=c && a <= d){
            c2++;
        }else if(c>=a && c <= b){
            c2++;
        }
    }

    printf("Part 1: %d\nPart 2: %d\n", c1, c2);

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}