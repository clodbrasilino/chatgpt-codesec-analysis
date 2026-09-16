#include <stdio.h>

int count_occurrences(int tuple[], int size, int element) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (tuple[i] == element) {
            count++;
        }
    }
    return count;
}

int main() {
    int tuple[] = {1, 2, 3, 2, 4, 2, 5};
    int size = sizeof(tuple) / sizeof(tuple[0]);
    int element = 2;
    int result = count_occurrences(tuple, size, element);
    printf("%d\n", result);
    return 0;
}