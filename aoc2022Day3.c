#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    FILE * fp = fopen("aoc2022Day3Input.txt", "r");

    int count1 = 0;
    int count2 = 0;

    char lines[512][512];

    int index = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        strcpy(lines[index], line);
        index++;
        
        int init_size = strlen(line);

        char string1[256] = "";
        char string2[256] = "";

        char keyChar = '\0';

        int where;
        for(int i = 0;i < init_size/2; i++){
            string1[i]=line[i];
            where = i+1;
        }
        string1[where]='\0';

        strcpy(string2, line);

        int where2 = 0;
        for(int j = 0; j < init_size/2; j++){
            for(int i = 0; i < init_size; i++){
                string2[i] = string2[i+1];
                where2 = i+1;
            }
        }
        string2[where2] = '\0';

        for(int i = 0; i < init_size/2; i++){
            for(int j = 0; j < init_size/2; j++){
                if(string1[i] == string2[j]){
                keyChar = string1[i];
                break;
                }
            }
        }

        if(isupper(keyChar)){
            count1+=keyChar-65+27;
        }else{
            count1+=keyChar-96;
        }

        strcpy(string1, "");
        strcpy(string2, "");

    }

    char first[1000];
    char second[1000];
    char third[1000];
    char key = '\0';

    for(int i = 0; i < 300; i++){
        if(i%3 == 0){
            strcpy(first, lines[i]);
        }else if(i%3 == 1){
            strcpy(second, lines[i]);
        }else{
            strcpy(third, lines[i]);
            for(int i = 0; i < strlen(first); i++){
                for(int j = 0; j < strlen(second); j++){
                    for(int k = 0; k < strlen(third); k++){
                        if(first[i] == second[j] && second[j] == third[k]){
                            key = first[i];
                            break;
                        }
                    }
                    if(key != '\0'){
                        break;
                    }
                }
                if(key != '\0'){
                    break;
                }
            }
            if(isupper(key)){
                count2+=key-65+27;
            }else{
                count2+=key-96;
            }
            key = '\0';
        }
    }
    printf("Part 1: %d Part 2: %d\n", count1, count2);
    fclose(fp);
    if (line)
        free(line);
}