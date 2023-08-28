#include <stdio.h>

void adjacentConcat(const char* tupleList[], int size) {
    for (int i = 0; i < size - 1; i++) {
        printf("%s", tupleList[i]);
        if (i != size - 2) {
            printf("%s", tupleList[i + 1]);
        }
    }
}

int main() {
    const char* tupleList[] = {"Hello ", "World ", "of ", "AI"};
    int size = sizeof(tupleList) / sizeof(tupleList[0]);

    adjacentConcat(tupleList, size);

    return 0;
}