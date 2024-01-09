#include <stdio.h>

typedef struct {
    int first;
    int second;
} Tuple;

void extractSymmetricPairs(Tuple list[], int size) {
    for (int i = 0; i < size; i++) {
        Tuple current = list[i];
        for (int j = i+1; j < size; j++) {
            Tuple next = list[j];
            if (current.first == next.second && current.second == next.first) {
                printf("(%d, %d)\n", current.first, current.second);
                break;
            }
        }
    }
}

int main() {
    Tuple list[] = {{1, 2}, {3, 4}, {5, 6}, {2, 1}, {4, 3}};
    int size = sizeof(list) / sizeof(list[0]);
    extractSymmetricPairs(list, size);
    return 0;
}