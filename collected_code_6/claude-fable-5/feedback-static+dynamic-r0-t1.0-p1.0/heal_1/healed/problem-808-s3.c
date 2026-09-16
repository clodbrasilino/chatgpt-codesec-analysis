#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    int first;
    int second;
} Tuple;

bool check_k(const Tuple *tuples, size_t count, int k)
{
    if (tuples == NULL || count == 0) {
        return false;
    }

    for (size_t i = 0; i < count; i++) {
        if (tuples[i].first == k || tuples[i].second == k) {
            return true;
        }
    }

    return false;
}

static void report(const Tuple *tuples, size_t count, int k)
{
    if (check_k(tuples, count, k)) {
        printf("Tuples contain %d\n", k);
    } else {
        printf("Tuples do not contain %d\n", k);
    }
}

int main(void)
{
    Tuple tuples1[] = { {3, 4}, {5, 6}, {7, 8}, {9, 10} };
    Tuple tuples2[] = { {1, 2}, {2, 3}, {4, 4} };
    size_t count1 = sizeof(tuples1) / sizeof(tuples1[0]);
    size_t count2 = sizeof(tuples2) / sizeof(tuples2[0]);

    report(tuples1, count1, 7);
    report(tuples2, count2, 9);
    report(NULL, 0, 5);

    return 0;
}