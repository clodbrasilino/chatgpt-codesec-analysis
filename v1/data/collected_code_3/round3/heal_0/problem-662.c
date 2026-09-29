#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

void sortDictionary(char dictionary[][MAX], int n) {
    char temp[MAX];
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(dictionary[i], dictionary[j]) > 0) {
                strcpy(temp, dictionary[i]);
                strcpy(dictionary[i], dictionary[j]);
                strcpy(dictionary[j], temp);
            }
        }
    }
}

int main() {
    char dictionary[MAX][MAX];
    int n;

    printf("Enter number of words: ");
    scanf("%d", &n);

    printf("Enter words: \n");
    for (int i = 0; i < n; i++) {
        scanf("%s", dictionary[i]);
    }

    sortDictionary(dictionary, n);

    printf("Sorted words: \n");
    for (int i = 0; i < n; i++) {
        printf("%s\n", dictionary[i]);
    }

    return 0;
}