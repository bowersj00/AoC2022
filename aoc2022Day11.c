#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SIZE 40
#define NUM 9699690

struct Monkey {
    long long int items[SIZE];
    int itemNum;
    char opper;
    int oppNum;
    int test;
    int trueMonk;
    int falseMonk;
    long long int exams;
};

long long findHighest(struct Monkey monkeys[8]){
    long long int first = 0;
    long long int second = 0;
    for(int i = 0; i < 8; i++){
        if(monkeys[i].exams > first){
            second = first;
            first = monkeys[i].exams;
        }else if(monkeys[i].exams > second){
            second = monkeys[i].exams;
        }
    }
    return first * second;
}

void setMonkItems(int curMonkey, struct Monkey monkeys[8], char line[]){
    monkeys[curMonkey].itemNum = 0;
    char items[SIZE];
    sscanf(line, "  Starting items: %s", items);
    char * token = strtok(items, ",");
    while( token != NULL ) {
        monkeys[curMonkey].items[monkeys[curMonkey].itemNum] = atoi(token);
        monkeys[curMonkey].itemNum++;
        token = strtok(NULL, ",");
    }
}

long long int doOp(char opp, long long int num1, long long int num2){
    if(opp == '+'){
        return num1 + num2;
    }else if(opp == 'd'){
        return num1 * num1;
    }else{
        return num1 * num2;
    }
}

void shiftItems(long long int items[SIZE]){
    for(int i = 0; i < SIZE-1; i++){
        items[i] = items[i+1];
    }
}

void takeStep(struct Monkey monkeys[8]){
    for(int i = 0; i < 8; i++){
        while(monkeys[i].itemNum > 0){
            int num = monkeys[i].items[0];
            num = doOp(monkeys[i].opper, num, monkeys[i].oppNum);
            num = num/3;
            int nextMonk = 0;
            if(num % monkeys[i].test == 0){
                nextMonk = monkeys[i].trueMonk;
            }else{
                nextMonk = monkeys[i].falseMonk;
            }
            monkeys[nextMonk].items[monkeys[nextMonk].itemNum] = num;
            monkeys[nextMonk].itemNum++;
            shiftItems(monkeys[i].items);
            monkeys[i].itemNum--;
            monkeys[i].exams++;
        }
    }
}

void takeStep2(struct Monkey monkeys[8]){
    for(int i = 0; i < 8; i++){
        while(monkeys[i].itemNum > 0){
            long long int num = monkeys[i].items[0];
            num = doOp(monkeys[i].opper, num, monkeys[i].oppNum);
            num = num>NUM? num % NUM: num;
            int nextMonk = 0;
            if(num % monkeys[i].test == 0){
                nextMonk = monkeys[i].trueMonk;
            }else{
                nextMonk = monkeys[i].falseMonk;
            }
            monkeys[nextMonk].items[monkeys[nextMonk].itemNum] = num;
            monkeys[nextMonk].itemNum++;
            shiftItems(monkeys[i].items);
            monkeys[i].itemNum--;
            monkeys[i].exams++;
        }
    }
}

int main(void){
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    long long int c1 = 0;
    long long int c2 = 0;

    int lineCount = 0;
    int curMonkey = -1;

    struct Monkey monkeys[8];

    fp = fopen("aoc2022Day11Input.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        if(lineCount % 7 == 0){
            curMonkey++;
        }else if(lineCount % 7 == 1){
            setMonkItems(curMonkey, monkeys, line);
        }else if(lineCount % 7 == 2){
            char opper;
            int oppNum;
            sscanf(line, "  Operation: new = old %c %d", &opper, &oppNum);
            monkeys[curMonkey].opper = opper;
            monkeys[curMonkey].oppNum = oppNum;
        }else if(lineCount % 7 == 3){
            int test;
            sscanf(line, "  Test: divisible by %d", &test);
            monkeys[curMonkey].test = test;
        }else if(lineCount % 7 == 4){
            int trueMonk;
            sscanf(line, "    If true: throw to monkey %d", &trueMonk);
            monkeys[curMonkey].trueMonk = trueMonk;
        }else if(lineCount % 7 == 5){
            int falseMonk;
            sscanf(line, "    If false: throw to monkey %d", &falseMonk);
            monkeys[curMonkey].falseMonk = falseMonk;
        }else{
            monkeys[curMonkey].exams = 0;
        }
        lineCount++;
    }

    struct Monkey monkeys1[8];
    struct Monkey monkeys2[8];

    for(int i = 0; i < 8; i++){
        monkeys1[i] = monkeys[i];
        monkeys2[i] = monkeys[i];
    }

    for(int i = 0; i < 20; i++){
        takeStep(monkeys1);
    }

    c1 = findHighest(monkeys1);

    for(int i = 0; i < 10000; i++){
        takeStep2(monkeys2);
    }

    c2 = findHighest(monkeys2);

    printf("Part 1: %lld\nPart 2: %lld\n", c1, c2);

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}