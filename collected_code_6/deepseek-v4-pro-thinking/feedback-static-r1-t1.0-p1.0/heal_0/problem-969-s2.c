#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int first;
    int second;
} Tuple;

static int compare_tuples(const void *a, const void *b) {
    const Tuple *ta = (const Tuple *)a;
    const Tuple *tb = (const Tuple *)b;
    return (ta->first > tb->first) - (ta->first < tb->first);
}

int join_tuples(const Tuple *input, size_t count, Tuple *output, size_t output_capacity, size_t *output_count) {
    if (input == NULL || output == NULL || output_count == NULL) {
        return -1;
    }
    if (output_capacity < count || count > (size_t)-1 / sizeof(Tuple)) {
        return -1;
    }
    if (count == 0) {
        *output_count = 0;
        return 0;
    }

    memmove(output, input, count * sizeof(Tuple));
    qsort(output, count, sizeof(Tuple), compare_tuples);

    size_t out_count = 0;
    size_t i = 0;

    while (i < count) {
        int first = output[i].first;
        long long sum = 0;

        while (i < count && output[i].first == first) {
            long long next = sum + output[i].second;
            if (next > INT_MAX || next < INT_MIN) {
                return -1;
            }
            sum = next;
            i++;
        }

        output[out_count].first = first;
        output[out_count].second = (int)sum;
        out_count++;
    }

    *output_count = out_count;
    return 0;
}

int main(void) {
    enum { MAX_TUPLES = 5 };
    Tuple input[MAX_TUPLES] = {
        {1, 10},
        {2, 20},
        {1, 30},
        {3, 40},
        {2, 50}
    };
    size_t input_count = sizeof(input) / sizeof(input[0]);
    Tuple output[MAX_TUPLES];
    size_t output_count = 0;

    if (join_tuples(input, input_count, output, MAX_TUPLES, &output_count) != 0) {
        return 1;
    }

    for (size_t i = 0; i < output_count; i++) {
        printf("%d %d\n", output[i].first, output[i].second);
    }

    return 0;
}