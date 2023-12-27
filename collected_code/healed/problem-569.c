#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

void sortSublists(char ***list, int numOfLists, const int *listLengths) {
    for (int i = 0; i < numOfLists; i++) {
        if(list[i] != NULL && listLengths[i] > 0) {
            qsort(list[i], listLengths[i], sizeof(char *), compare);
        }
    }
}

int main() {
    char *strArr[] = {"apple", "banana", "cranberry"};
    char **list[] = {strArr};
    const int listLengths[] = {3};
    
    sortSublists(list, 1, listLengths);
    
    for(int i = 0; i < listLengths[i]; i++) {
        printf("%s\n", list[0][i]);
    }
    
    return 0;
}