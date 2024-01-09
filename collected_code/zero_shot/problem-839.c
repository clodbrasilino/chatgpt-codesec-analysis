#include <stdio.h>
#include <string.h>

void sortTuples(char tuples[][2], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (strcmp(tuples[j], tuples[j + 1]) > 0) {
                char temp[2];
                strcpy(temp, tuples[j]);
                strcpy(tuples[j], tuples[j + 1]);
                strcpy(tuples[j + 1], temp);
            }
        }
    }
}

int main() {
    char tuples[][2] = {{"b", "2"}, {"a", "1"}, {"c", "3"}};
    int size = sizeof(tuples) / sizeof(tuples[0]);

    sortTuples(tuples, size);

    for (int i = 0; i < size; i++) {
        printf("(%s, %s) ", tuples[i][0], tuples[i][1]);
    }

    return 0;
}