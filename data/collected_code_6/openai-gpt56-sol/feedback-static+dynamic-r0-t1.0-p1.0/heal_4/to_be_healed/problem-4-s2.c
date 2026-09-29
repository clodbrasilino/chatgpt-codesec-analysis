#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void swap_ints(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void sift_up(int heap[], size_t index)
{
    while (index > 0U) {
        size_t parent = (index - 1U) / 2U;

        if (heap[parent] <= heap[index]) {
            break;
        }

        swap_ints(&heap[parent], &heap[index]);
        index = parent;
    }
}

static void sift_down(int heap[], size_t size, size_t index)
{
    for (;;) {
        size_t smallest = index;
        size_t left;
        size_t right;

        if (size < 2U || index > (size - 2U) / 2U) {
            break;
        }

        left = index * 2U + 1U;
        right = left + 1U;

        if (heap[left] < heap[smallest]) {
            smallest = left;
        }

        if (right < size && heap[right] < heap[smallest]) {
            smallest = right;
        }

        if (smallest == index) {
            break;
        }

        swap_ints(&heap[index], &heap[smallest]);
        index = smallest;
    }
}

static int compare_descending(const void *left, const void *right)
{
    int a = *(const int *)left;
    int b = *(const int *)right;

    return (a < b) - (a > b);
}

static int find_largest(const int numbers[], size_t count,
                        size_t largest_count, int result[])
{
    size_t i;

    if (numbers == NULL || result == NULL || largest_count == 0U ||
        largest_count > count) {
        return -1;
    }

    for (i = 0U; i < largest_count; ++i) {
        result[i] = numbers[i];
        sift_up(result, i);
    }

    for (i = largest_count; i < count; ++i) {
        if (numbers[i] > result[0]) {
            result[0] = numbers[i];
            sift_down(result, largest_count, 0U);
        }
    }

    qsort(result, largest_count, sizeof(result[0]), compare_descending);
    return 0;
}

static int parse_size(const char *text, size_t *value)
{
    char *end;
    unsigned long long parsed;

    if (text == NULL || value == NULL || text[0] == '\0' ||
        text[0] == '-' || text[0] == '+') {
        return -1;
    }

    errno = 0;
    parsed = strtoull(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed == 0ULL || parsed > SIZE_MAX) {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int parse_int(const char *text, int *value)
{
    char *end;
    long parsed;

    if (text == NULL || value == NULL || text[0] == '\0') {
        return -1;
    }

    errno = 0;
    parsed = strtol(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed < INT_MIN || parsed > INT_MAX) {
        return -1;
    }

    *value = (int)parsed;
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    int *numbers = NULL;
    int *largest = NULL;
    size_t count;
    size_t largest_count;
    size_t i;
    int status = EXIT_FAILURE;

    if (argc < 3 || parse_size(argv[1], &largest_count) != 0) {
        fprintf(stderr, "Usage: %s <count> <integer> [integer ...]\n",
                argv[0]);
        return EXIT_FAILURE;
    }

    count = (size_t)argc - 2U;

    if (largest_count > count ||
        count > SIZE_MAX / sizeof(*numbers) ||
        largest_count > SIZE_MAX / sizeof(*largest)) {
        fprintf(stderr, "Invalid count or input size.\n");
        return EXIT_FAILURE;
    }

    numbers = malloc(count * sizeof(*numbers));
    largest = malloc(largest_count * sizeof(*largest));

    if (numbers == NULL || largest == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        goto cleanup;
    }

    for (i = 0U; i < count; ++i) {
        if (parse_int(argv[i + 2U], &numbers[i]) != 0) {
            fprintf(stderr, "Invalid integer: %s\n", argv[i + 2U]);
            goto cleanup;
        }
    }

    if (find_largest(numbers, count, largest_count, largest) != 0) {
        fprintf(stderr, "Unable to find the largest integers.\n");
        goto cleanup;
    }

    for (i = 0U; i < largest_count; ++i) {
        printf("%d%s", largest[i],
               i + 1U == largest_count ? "\n" : " ");
    }

    status = EXIT_SUCCESS;

cleanup:
    free(largest);
    free(numbers);
    return status;
}