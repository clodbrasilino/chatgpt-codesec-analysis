#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    FIND_SUCCESS = 0,
    FIND_INVALID_ARGUMENT,
    FIND_SUM_OVERFLOW
} FindResult;

static int write_int64(FILE *stream, int64_t value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[21];
    char *position = buffer + sizeof(buffer);
    uint64_t magnitude;
    size_t length;

    if (stream == NULL) {
        return -1;
    }

    if (value < 0) {
        magnitude = UINT64_C(0) - (uint64_t)value;
    } else {
        magnitude = (uint64_t)value;
    }

    do {
        *--position = (char)('0' + (magnitude % UINT64_C(10)));
        magnitude /= UINT64_C(10);
    } while (magnitude != 0);

    if (value < 0) {
        *--position = '-';
    }

    length = (size_t)((buffer + sizeof(buffer)) - position);

    return fwrite(position, 1, length, stream) == length ? 0 : -1;
}

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

    if (highest_list == NULL ||
        highest_length == NULL ||
        highest_sum == NULL) {
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

int main(void)
{
    const int64_t list1[] = {1, 2, 3};
    const int64_t list2[] = {10, -2, 5};
    const int64_t list3[] = {4, 4, 4};

    const int64_t *const lists[] = {
        list1,
        list2,
        list3
    };

    const size_t lengths[] = {
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
        if (result == FIND_SUM_OVERFLOW) {
            fputs("A list sum exceeds the int64_t range.\n", stderr);
        } else {
            fputs("Invalid argument supplied.\n", stderr);
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

        if (write_int64(stdout, highest_list[i]) != 0) {
            return EXIT_FAILURE;
        }
    }

    if (fputs("]\nSum: ", stdout) == EOF) {
        return EXIT_FAILURE;
    }

    if (write_int64(stdout, highest_sum) != 0) {
        return EXIT_FAILURE;
    }

    if (fputc('\n', stdout) == EOF) {
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}