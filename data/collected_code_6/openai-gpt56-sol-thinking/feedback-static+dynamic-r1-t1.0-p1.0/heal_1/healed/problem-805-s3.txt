#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    FIND_SUCCESS = 0,
    FIND_INVALID_ARGUMENT,
    FIND_SUM_OVERFLOW
} FindResult;

FindResult find_highest_sum_list(
    const int64_t *const *lists,
    const size_t *lengths,
    size_t list_count,
    const int64_t **highest_list,
    size_t *highest_length,
    int64_t *highest_sum)
{
    size_t best_index = 0;
    int64_t best_sum = 0;

    if (highest_list == NULL || highest_length == NULL || highest_sum == NULL) {
        return FIND_INVALID_ARGUMENT;
    }

    *highest_list = NULL;
    *highest_length = 0;
    *highest_sum = 0;

    if (lists == NULL || lengths == NULL || list_count == 0) {
        return FIND_INVALID_ARGUMENT;
    }

    for (size_t i = 0; i < list_count; ++i) {
        int64_t current_sum = 0;

        if (lists[i] == NULL && lengths[i] != 0) {
            return FIND_INVALID_ARGUMENT;
        }

        for (size_t j = 0; j < lengths[i]; ++j) {
            const int64_t value = lists[i][j];

            if ((value > 0 && current_sum > INT64_MAX - value) ||
                (value < 0 && current_sum < INT64_MIN - value)) {
                return FIND_SUM_OVERFLOW;
            }

            current_sum += value;
        }

        if (i == 0 || current_sum > best_sum) {
            best_index = i;
            best_sum = current_sum;
        }
    }

    *highest_list = lists[best_index];
    *highest_length = lengths[best_index];
    *highest_sum = best_sum;

    return FIND_SUCCESS;
}

static int print_int64(FILE *stream, int64_t value)
{
    char digits[20];
    size_t count = 0;
    uint64_t magnitude;

    if (value < 0) {
        if (fputc('-', stream) == EOF) {
            return -1;
        }

        magnitude = (uint64_t)(-(value + 1)) + UINT64_C(1);
    } else {
        magnitude = (uint64_t)value;
    }

    do {
        digits[count++] = (char)('0' + magnitude % UINT64_C(10));
        magnitude /= UINT64_C(10);
    } while (magnitude != 0);

    while (count > 0) {
        if (fputc((unsigned char)digits[--count], stream) == EOF) {
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    static const int64_t list1[] = {1, 2, 3};
    static const int64_t list2[] = {10, -2, 5};
    static const int64_t list3[] = {4, 4, 4};

    static const int64_t *const lists[] = {
        list1,
        list2,
        list3
    };

    static const size_t lengths[] = {
        sizeof(list1) / sizeof(list1[0]),
        sizeof(list2) / sizeof(list2[0]),
        sizeof(list3) / sizeof(list3[0])
    };

    const int64_t *highest_list = NULL;
    size_t highest_length = 0;
    int64_t highest_sum = 0;

    const FindResult result = find_highest_sum_list(
        lists,
        lengths,
        sizeof(lists) / sizeof(lists[0]),
        &highest_list,
        &highest_length,
        &highest_sum
    );

    if (result != FIND_SUCCESS) {
        if (fputs("Unable to find the highest-sum list.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    if (fputs("Highest-sum list: [", stdout) == EOF) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < highest_length; ++i) {
        if (i != 0 && fputs(", ", stdout) == EOF) {
            return EXIT_FAILURE;
        }

        if (print_int64(stdout, highest_list[i]) != 0) {
            return EXIT_FAILURE;
        }
    }

    if (fputs("]\nSum: ", stdout) == EOF) {
        return EXIT_FAILURE;
    }

    if (print_int64(stdout, highest_sum) != 0) {
        return EXIT_FAILURE;
    }

    if (fputc('\n', stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}