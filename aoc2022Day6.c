#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 14

int check(char nums[SIZE]){
    for(int i = 0; i < SIZE+1; i++){
        for(int j = i+1; j < SIZE+1; j++){
            if(nums[i] == nums[j]){
                return 0;
            }
        }
    }
    return 1;
}

int main(void){
    FILE * fp;
    char * line = NULL;
    size_t len = 0;

    int c1 = 0;
    int c2 = 0;

    fp = fopen("aoc2022Day6Input.txt", "r");
    getline(&line, &len, fp);

    char one = line[0];
    char two = line[1];
    char three = line[2];
    char four = line[3];

    int index = 3;
    while(one == two || one == three || one == four || two == three || two == four || three == four ? 1 : 0){
        /*this snippet by Jonas Ferguson*/
        one = two;
        two = three;
        three = four;
        four = line[index];

        index++;
    }
    c1 = index;

    char nums[SIZE];
    for(int i = 0; i < SIZE; i++) nums[i] = line[i];
    index = SIZE;

    while(!check(nums)){
        nums[index%14] = line[index];
        index++;
    }
    c2 = index;

    printf("Part 1: %d\nPart 2: %d\n", c1, c2);

    fclose(fp);
    line ? free(line) : 0;
}