#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int find_common_first(Tuple *tuples, int length) {
    if (tuples == NULL || length <= 0) {
        return -1;
    }

    int candidate = tuples[0].first;
    int count = 1;

    for (int i = 1; i < length; i++) {
        if (tuples[i].first == candidate) {
            count++;
        } else {
            count--;
            if (count == 0) {
                candidate = tuples[i].first;
                count = 1;
            }
        }
    }

    count = 0;
    for (int i = 0; i < length; i++) {
        if (tuples[i].first == candidate) {
            count++;
        }
    }

    if (count > length / 2) {
        return candidate;
    }

    return -1;
}

int main(void) {
    Tuple tuples[] = {
        {1, 10},
        {2, 20},
        {1, 30},
        {1, 40},
        {3, 50},
        {1, 60},
        {1, 70}
    };
    int length = sizeof(tuples) / sizeof(tuples[0]);

    int result = find_common_first(tuples, length);

    if (result != -1) {
        printf("Common first element: %d\n", result);
    } else {
        printf("No common first element found\n");
    }

    return 0;
}