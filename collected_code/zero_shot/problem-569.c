#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to compare two strings, used for sorting
int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

// Function to sort sublist of strings in a given list of lists
void sortSublists(char ***list, int numOfLists, int *listLengths) {
    for (int i = 0; i < numOfLists; i++) {
        qsort(list[i], listLengths[i], sizeof(char *), compare);
    }
}