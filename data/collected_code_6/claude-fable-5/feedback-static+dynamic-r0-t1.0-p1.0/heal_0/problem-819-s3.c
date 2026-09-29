#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    size_t count;
} RunEntry;

static int count_consecutive_duplicates(const int *numbers, size_t length,
                                        RunEntry **result, size_t *result_length)
{
    RunEntry *runs;
    size_t run_count;
    size_t i;

    if (numbers == NULL || result == NULL || result_length == NULL) {
        return -1;
    }

    if (length == 0) {
        *result = NULL;
        *result_length = 0;
        return 0;
    }

    runs = malloc(length * sizeof(*runs));
    if (runs == NULL) {
        return -1;
    }

    run_count = 0;
    runs[run_count].value = numbers[0];
    runs[run_count].count = 1;

    for (i = 1; i < length; i++) {
        if (numbers[i] == runs[run_count].value) {
            runs[run_count].count++;
        } else {
            run_count++;
            runs[run_count].value = numbers[i];
            runs[run_count].count = 1;
        }
    }
    run_count++;

    *result = runs;
    *result_length = run_count;
    return 0;
}

int main(void)
{
    const int numbers[] = {1, 1, 2, 3, 3, 3, 4, 4, 5, 1, 1};
    const size_t length = sizeof(numbers) / sizeof(numbers[0]);
    RunEntry *runs = NULL;
    size_t run_count = 0;
    size_t i;

    if (count_consecutive_duplicates(numbers, length, &runs, &run_count) != 0) {
        fprintf(stderr, "Failed to count consecutive duplicates\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < run_count; i++) {
        if (printf("Value %d appears %zu time(s) consecutively\n",
                   runs[i].value, runs[i].count) < 0) {
            free(runs);
            return EXIT_FAILURE;
        }
    }

    free(runs);
    runs = NULL;

    return EXIT_SUCCESS;
}