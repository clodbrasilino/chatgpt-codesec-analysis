#include <stdio.h>

typedef struct {
    int first;
    int second;
} Tuple;

int find_common_first(Tuple *tuples, int size) {
    int i, j;
    for(i = 0; i < size; i++) {
        for(j = i + 1; j < size; j++) {
            if(tuples[i].first == tuples[j].first) {
                return tuples[i].first;
            }
        }
    }
    return -1;
}

int main() {
    Tuple tuples[] = {{1, 2}, {3, 4}, {5, 6}, {1, 7}, {8, 9}};
    int size = sizeof(tuples) / sizeof(Tuple);
    int common_first = find_common_first(tuples, size);
    if(common_first != -1) {
        printf("Common first element is: %d\n", common_first);
    } else {
        printf("No common first element found.\n");
    }
    return 0;
}