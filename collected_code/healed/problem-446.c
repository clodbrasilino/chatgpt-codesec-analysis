#include <stdio.h>

void countOccurrence(const int list[], const int listSize, const int tuple[], const int tupleSize) {
    int count;

    for (int i = 0; i < tupleSize; i++) {
        count = 0;

        for (int j = 0; j < listSize; j++) {
            if (list[j] == tuple[i]) {
                count++;
            }
        }

        printf("Element %d occurs %d time(s)\n", tuple[i], count);
    }
}

int main() {
    int list[] = {1, 2, 3, 4, 5};
    int tuple[] = {1, 2, 3, 2, 1};

    int listSize = sizeof(list) / sizeof(list[0]);
    int tupleSize = sizeof(tuple) / sizeof(tuple[0]);

    countOccurrence(list, listSize, tuple, tupleSize);

    return 0;
}