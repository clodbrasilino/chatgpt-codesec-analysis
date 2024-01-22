#include <stdio.h>
#include <string.h>
#include <stddef.h>

#define BUFFER_SIZE 100
#define MAX_STR_LEN 99

void mergeDictionaries(char dictionary1[][BUFFER_SIZE], char dictionary2[][BUFFER_SIZE], int* size1, const int size2) {
    if(dictionary1 == NULL || dictionary2 == NULL || size1 == NULL) return;

    for (int i = 0; (i < size2) && (*size1 < BUFFER_SIZE); i++) {
        int flag = 0;
        for (int j = 0; j < *size1; j++) {
            if (strcmp(dictionary1[j], dictionary2[i]) == 0) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            strncpy(dictionary1[*size1], dictionary2[i], MAX_STR_LEN);
            dictionary1[*size1][MAX_STR_LEN] = '\0';
            (*size1)++;
        }
    }
}

int main() {
    char dictionary1[BUFFER_SIZE][BUFFER_SIZE] = {0}, dictionary2[BUFFER_SIZE][BUFFER_SIZE] = {0};
    int size1 = 0, size2 = 0;

    printf("Enter the number of elements in the first dictionary: ");
    if(scanf("%d", &size1) != 1) return 1;
    size1 = size1 > BUFFER_SIZE ? BUFFER_SIZE : size1;

    printf("Enter the elements of the first dictionary:\n");
    for (int i = 0; i < size1; i++) {
        scanf("%99s", dictionary1[i]);
    }

    printf("Enter the number of elements in the second dictionary: ");
    if(scanf("%d", &size2) != 1) return 1;
    size2 = size2 > BUFFER_SIZE ? BUFFER_SIZE : size2;

    printf("Enter the elements of the second dictionary:\n");
    for (int i = 0; i < size2; i++) {
        scanf("%99s", dictionary2[i]);
    }

    mergeDictionaries(dictionary1, dictionary2, &size1, size2);

    printf("\nMerged Dictionary:\n");
    for (int i = 0; i < size1; i++) {
        printf("%s\n", dictionary1[i]);
    }

    return 0;
}