#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 100
#define MAX_LIST_LEN 10

void sortSublist(char list[MAX_LIST_LEN][MAX_STR_LEN], int n) {
    char temp[MAX_STR_LEN];
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(list[i], list[j]) > 0) {
                strcpy(temp, list[i]);
                strcpy(list[i], list[j]);
                strcpy(list[j], temp);
            }
        }
    }
}

void sortListOfLists(char list[MAX_LIST_LEN][MAX_LIST_LEN][MAX_STR_LEN], int n) {
    for (int i = 0; i < n; i++) {
        sortSublist(list[i], n);
    }
}

int main() {
    char list[MAX_LIST_LEN][MAX_LIST_LEN][MAX_STR_LEN] = {
        {"apple", "banana", "cherry"},
        {"dog", "cat", "elephant"},
        {"grape", "fig", "date"}
    };

    sortListOfLists(list, 3);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%s ", list[i][j]);
        }
        printf("\n");
    }

    return 0;
}