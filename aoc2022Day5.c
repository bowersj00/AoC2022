#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 256

int arr[9][SIZE] = {
    {81, 83, 87, 67, 90, 86, 70, 84},
    {81, 82, 66},
    {66, 90, 84, 81, 80, 77, 83},
    {68, 86, 70, 82, 81, 72},
    {74, 71, 76, 68, 66, 83, 84, 80},
    {87, 82, 84, 90},
    {72, 81, 77, 78, 83, 70, 82, 74},
    {82, 78, 70, 72, 87},
    {74, 90, 84, 81, 80, 82, 66}
};

int loc[] = {7, 2, 6, 5, 7, 3, 7, 4, 6};


int arr2[9][SIZE] = {
    {81, 83, 87, 67, 90, 86, 70, 84},
    {81, 82, 66},
    {66, 90, 84, 81, 80, 77, 83},
    {68, 86, 70, 82, 81, 72},
    {74, 71, 76, 68, 66, 83, 84, 80},
    {87, 82, 84, 90},
    {72, 81, 77, 78, 83, 70, 82, 74},
    {82, 78, 70, 72, 87},
    {74, 90, 84, 81, 80, 82, 66}
};

int loc2[] = {7, 2, 6, 5, 7, 3, 7, 4, 6};

void remove_element(int location){
    arr[location][loc[location]] = arr[location][loc[location]+1];
}

void remove_element2(int location){
    arr2[location][loc2[location]] = arr2[location][loc2[location]+1];
}

void move(int p2, int p3){
    arr[p3][loc[p3]+1] = arr[p2][loc[p2]];
    remove_element(p2);
    loc[p3]++;
    loc[p2]--;
}

void move2(int p2, int p3, int offset){
    arr2[p3][loc2[p3]+1+offset] = arr2[p2][loc2[p2]];
    remove_element2(p2);
    loc2[p2]--;
}

int main(void){
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    int p1, p2, p3;

    fp = fopen("aoc2022Day5Input.txt", "r");

    while ((read = getline(&line, &len, fp)) != -1) {
        sscanf(line, "move %d from %d to %d", &p1, &p2, &p3);

        for(int i = 0; i < p1; i++){
            move(p2-1, p3-1);
        }

        for(int i = p1; i > 0; i--){
            move2(p2-1, p3-1, i-1);
        }
        loc2[p3-1]+=p1;
    }

    printf("Part 1: %c%c%c%c%c%c%c%c%c\n", arr[0][loc[0]], arr[1][loc[1]], arr[2][loc[2]], arr[3][loc[3]], arr[4][loc[4]], arr[5][loc[5]], arr[6][loc[6]], arr[7][loc[7]], arr[8][loc[8]]);
    printf("Part 2: %c%c%c%c%c%c%c%c%c\n", arr2[0][loc2[0]], arr2[1][loc2[1]], arr2[2][loc2[2]], arr2[3][loc2[3]], arr2[4][loc2[4]], arr2[5][loc2[5]], arr2[6][loc2[6]], arr2[7][loc2[7]], arr2[8][loc2[8]]);

    fclose(fp);
    line ? free(line) : 0;
}