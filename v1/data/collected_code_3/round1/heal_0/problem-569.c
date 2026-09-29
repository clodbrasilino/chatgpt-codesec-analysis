#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

void sortSublist(char arr[MAX][MAX], int n) {
    char temp[MAX];
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (strcmp(arr[i], arr[j]) > 0) {
                strcpy(temp, arr[i]);
                strcpy(arr[i], arr[j]);
                strcpy(arr[j], temp);
            }
        }
    }
}

void sortList(char arr[MAX][MAX][MAX], int n, int m) {
    for (int i = 0; i < n; i++) {
        sortSublist(arr[i], m);
    }
}

int main() {
    char arr[MAX][MAX][MAX] = {
        {"apple", "banana", "cherry"},
        {"dog", "cat", "elephant"},
        {"grape", "fig", "honeydew"}
    };

    int n = 3;
    int m = 3;

    sortList(arr, n, m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%s ", arr[i][j]);
        }
        printf("\n");
    }

    return 0;
}