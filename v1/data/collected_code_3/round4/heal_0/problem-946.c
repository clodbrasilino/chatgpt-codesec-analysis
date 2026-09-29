#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ASCII_SIZE 256

struct CharCount {
    char ch;
    int count;
};

void findMostCommonElements(char* str, struct CharCount* countArr) {
    int len = strlen(str);
    int i;

    for (i = 0; i < len; i++)
        countArr[str[i]].count++;

    for (i = 0; i < ASCII_SIZE; i++)
        countArr[i].ch = i;
}

int compare(const void* a, const void* b) {
    return ((struct CharCount*)b)->count - ((struct CharCount*)a)->count;
}

void printMostCommonElements(struct CharCount* countArr) {
    int i;
    for (i = 0; i < ASCII_SIZE; i++) {
        if (countArr[i].count > 0)
            printf("%c, count = %d\n", countArr[i].ch, countArr[i].count);
    }
}

int main() {
    char str[] = "Find the most common elements in this string";
    struct CharCount countArr[ASCII_SIZE] = {0};

    findMostCommonElements(str, countArr);

    qsort((void*)countArr, ASCII_SIZE, sizeof(countArr[0]), compare);

    printMostCommonElements(countArr);

    return 0;
}