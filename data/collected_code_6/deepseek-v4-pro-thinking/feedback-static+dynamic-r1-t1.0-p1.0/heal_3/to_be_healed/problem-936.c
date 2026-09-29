#include <stddef.h>
#include <stdio.h>

#define MAX_VALUE_LEN 32

typedef struct {
    int id;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char value[MAX_VALUE_LEN];
} Tuple;

void rearrange_tuples(Tuple *tuples, size_t tuple_count, const int *order, size_t order_count) {
    if (tuples == NULL || order == NULL) {
        return;
    }

    size_t pos = 0;
    for (size_t i = 0; i < order_count && pos < tuple_count; ++i) {
        for (size_t j = pos; j < tuple_count; ++j) {
            if (tuples[j].id == order[i]) {
                if (j != pos) {
                    Tuple temp = tuples[pos];
                    tuples[pos] = tuples[j];
                    tuples[j] = temp;
                }
                ++pos;
                break;
            }
        }
    }
}

int main(void) {
    Tuple tuples[] = {
        {3, "three"},
        {1, "one"},
        {2, "two"},
        {4, "four"}
    };
    int order[] = {2, 1, 4, 3};
    size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    size_t order_count = sizeof(order) / sizeof(order[0]);

    rearrange_tuples(tuples, tuple_count, order, order_count);

    for (size_t i = 0; i < tuple_count; ++i) {
        printf("%d: %s\n", tuples[i].id, tuples[i].value);
    }

    return 0;
}