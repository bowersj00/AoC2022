#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAMESIZE 13
#define DIRSIZE 185
#define CHILDSIZE 20
#define FILESIZE 20

int dirIndex = 1;
int dirSizes[DIRSIZE];
int dirSizeIndex = 1;

struct Dir {
    char name[NAMESIZE];
    char parent[NAMESIZE];
    char children[CHILDSIZE][NAMESIZE];
    char files[FILESIZE][NAMESIZE];
    long long int size;
};

int getDirIndex(char name[NAMESIZE], struct Dir dirs[DIRSIZE]){
    int i = 0;
    while(strcmp(dirs[i].name, name) != 0){
        i++;
    }
    return i;
}

int getNextChildIndex(struct Dir dir){
    for(int i = 0; i < CHILDSIZE; i++){
        if(strcmp(dir.children[i], "") == 0){
            return i;
        }
    }
    return -1;
}

int getNextFileIndex(struct Dir dir){
    for(int i = 0; i < FILESIZE; i++){
        if(strcmp(dir.files[i], "") == 0){
            return i;
        }
    }
    return -1;
}

int containsDir(struct Dir dir, struct Dir dirs[DIRSIZE]){
    for(int i = 0; i < dirIndex+1; i++){
        if(strcmp(dirs[i].name, dir.name) == 0){
            return 1;
        }
    }
    return 0;
}

int containsFile(struct Dir dir, char name[NAMESIZE]){
    for(int i = 0; i < FILESIZE; i++){
        if(strcmp(dir.files[i], name) == 0){
            return 1;
        }
    }
    return 0;
}

int calculateSizes(struct Dir dir, struct Dir dirs[DIRSIZE]){
    int numChildren = getNextChildIndex(dir);
    if(numChildren == 0){
        // printf("found: %ld from %s\n", dir.size, dir.name);
        dirSizes[dirSizeIndex] = dir.size;
        dirSizeIndex++;
        return dir.size;
    }
    long int count;
    for(int i = 0; i < numChildren; i++){
        count += calculateSizes(dirs[getDirIndex(dir.children[i], dirs)], dirs);
    }
    count+=dir.size;
    dirSizes[dirSizeIndex] = count;
    dirSizeIndex++;
    return count;

}

int main(void){
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    long long int c1 = 0;
    long long int c2 = 0;

    struct Dir dirs[DIRSIZE];

    strcpy(dirs[0].name, "root");
    strcpy(dirs[0].parent, "");
    strcpy(dirs[0].children[0], "");
    dirs[0].size = 0;

    char curName[NAMESIZE];
    int curIndex = 0;

    fp = fopen("aoc2022Day7Input.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        if(line[0] == '$'){
            if(line[2] == 'c'){
                if(line[5] == '/'){
                    strcpy(curName, "root");
                    curIndex = 0;
                }else if(line[5] == '.'){
                    strcpy(curName, dirs[getDirIndex(curName, dirs)].parent);
                    curIndex = getDirIndex(curName, dirs);
                }else{
                    sscanf(line, "$ cd %s", curName);
                    curIndex = getDirIndex(curName, dirs);
                }
            }
        }else{
            if(line[0] == 'd'){
                struct Dir thisDir;
                char name[NAMESIZE];
                sscanf(line, "dir %s", name);

                strcpy(thisDir.name, name);
                strcpy(thisDir.parent, curName);

                strcpy(dirs[getDirIndex(curName, dirs)].children[getNextChildIndex(dirs[getDirIndex(curName, dirs)])], name);

                if(!containsDir(thisDir, dirs)){
                    dirs[dirIndex] = thisDir;
                    dirIndex++;
                }
            }else{
                int fileSize = 0;
                char fileName[NAMESIZE];
                sscanf(line, "%d %s", &fileSize, fileName);
                if(!containsFile(dirs[getDirIndex(curName, dirs)], fileName)){
                    strcpy(dirs[getDirIndex(curName, dirs)].files[getNextFileIndex(dirs[getDirIndex(curName, dirs)])], fileName);
                    dirs[getDirIndex(curName, dirs)].size += fileSize;
                }
            }
        }
    }

    dirSizes[0] = calculateSizes(dirs[0], dirs);

    for(int i = 0; i < DIRSIZE; i++){
        c1 += dirSizes[i] < 100000? dirSizes[i] : 0;
    }


    printf("Part 1: %lld\nPart 2: %lld\n", c1, c2);

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}