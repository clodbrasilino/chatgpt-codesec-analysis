#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 100
#define MAX_LIST_LEN 10

void sort_sublist(char list[MAX_LIST_LEN][MAX_STR_LEN], int n) {
    char temp[MAX_STR_LEN];
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (strcmp(list[i], list[j]) > 0) {
                strcpy(temp, list[i]);
                strcpy(list[i], list[j]);
                strcpy(list[j], temp);
            }
        }
    }
}

int main() {
    char list[MAX_LIST_LEN][MAX_STR_LEN] = {"Hello", "World", "C", "Programming", "Sort", "Sublist", "Strings", "List", "Of", "Lists"};
    int n = 10;

    printf("Before sorting:\n");
    for (int i = 0; i < n; i++) {
        printf("%s\n", list[i]);
    }

    sort_sublist(list, n);

    printf("\nAfter sorting:\n");
    for (int i = 0; i < n; i++) {
        printf("%s\n", list[i]);
    }

    return 0;
}