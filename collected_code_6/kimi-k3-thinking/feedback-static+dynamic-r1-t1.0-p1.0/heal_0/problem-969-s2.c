#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REST 16

typedef struct {
    int first;
    int rest[MAX_REST];
    size_t rest_count;
} Tuple;

static int find_index_by_first(const Tuple *tuples, size_t count, int first, size_t *index)
{
    size_t i;

    if (tuples == NULL || index == NULL) {
        return 0;
    }

    for (i = 0; i < count; i++) {
        if (tuples[i].first == first) {
            *index = i;
            return 1;
        }
    }

    return 0;
}

size_t join_tuples(const Tuple *input, size_t input_count, Tuple *output, size_t output_capacity)
{
    size_t out_count = 0;
    size_t i;
    size_t j;
    size_t idx;
    size_t count;

    if (input == NULL || output == NULL || output_capacity == 0) {
        return 0;
    }

    for (i = 0; i < input_count; i++) {
        count = input[i].rest_count;
        if (count > MAX_REST) {
            count = MAX_REST;
        }

        if (find_index_by_first(output, out_count, input[i].first, &idx)) {
            for (j = 0; j < count; j++) {
                if (output[idx].rest_count < MAX_REST) {
                    output[idx].rest[output[idx].rest_count] = input[i].rest[j];
                    output[idx].rest_count++;
                }
            }
        } else {
            if (out_count >= output_capacity) {
                break;
            }
            output[out_count].first = input[i].first;
            output[out_count].rest_count = 0;
            for (j = 0; j < count; j++) {
                output[out_count].rest[j] = input[i].rest[j];
            }
            output[out_count].rest_count = count;
            out_count++;
        }
    }

    return out_count;
}

static void print_tuples(const Tuple *tuples, size_t count)
{
    size_t i;
    size_t j;

    if (tuples == NULL) {
        return;
    }

    for (i = 0; i < count; i++) {
        printf("(%d", tuples[i].first);
        for (j = 0; j < tuples[i].rest_count; j++) {
            printf(", %d", tuples[i].rest[j]);
        }
        printf(")\n");
    }
}

int main(void)
{
    Tuple input[] = {
        {1, {2, 3}, 2},
        {4, {5}, 1},
        {1, {6}, 1},
        {7, {8, 9}, 2},
        {4, {10}, 1}
    };
    Tuple output[16];
    size_t input_count = sizeof(input) / sizeof(input[0]);
    size_t output_count;

    output_count = join_tuples(input, input_count, output, sizeof(output) / sizeof(output[0]));

    printf("Joined tuples:\n");
    print_tuples(output, output_count);

    return 0;
}