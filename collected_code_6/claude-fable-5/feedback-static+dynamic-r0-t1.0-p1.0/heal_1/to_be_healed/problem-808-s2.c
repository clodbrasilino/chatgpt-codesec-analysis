#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    int first;
    int second;
} Tuple;

bool check_k(const Tuple *tuples, size_t count, int k)
{
    if (tuples == NULL) {
        return false;
    }

    for (size_t i = 0; i < count; i++) {
        if (tuples[i].first == k || tuples[i].second == k) {
            return true;
        }
    }

    return false;
}

int main(void)
{
    Tuple tuples1[] = { {3, 4}, {5, 6}, {7, 8}, {9, 10} };
    size_t count1 = sizeof(tuples1) / sizeof(tuples1[0]);

    Tuple tuples2[] = { {1, 2}, {3, 4}, {5, 6} };
    size_t count2 = sizeof(tuples2) / sizeof(tuples2[0]);

    if (check_k(tuples1, count1, 7)) {
        printf("Tuples contain 7\n");
    } else {
        printf("Tuples do not contain 7\n");
    }

    if (check_k(tuples2, count2, 9)) {
        printf("Tuples contain 9\n");
    } else {
        printf("Tuples do not contain 9\n");
    }

    /* Possible weaknesses found:
     *  Condition 'check_k(NULL,0,5)' is always false [knownConditionTrueFalse]
     *  Calling function 'check_k' returns 0
     *  Condition 'check_k(NULL,0,5)' is always false
     */
    if (check_k(NULL, 0, 5)) {
        printf("Tuples contain 5\n");
    } else {
        printf("Tuples do not contain 5\n");
    }

    return 0;
}