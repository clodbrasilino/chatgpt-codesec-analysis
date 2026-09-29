#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>
#include <stdbool.h>

static bool contains(const int *arr, size_t size, int value)
{
    for (size_t i = 0; i < size; i++) {
        if (arr[i] == value) {
            return true;
        }
    }
    return false;
}

static int compare_ints(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y) {
        return -1;
    }
    if (x > y) {
        return 1;
    }
    return 0;
}

static int *intersection(const int *arr1, size_t size1,
                         const int *arr2, size_t size2,
                         size_t *result_size)
{
    if (result_size == NULL) {
        return NULL;
    }

    *result_size = 0;

    if (arr1 == NULL || arr2 == NULL || size1 == 0 || size2 == 0) {
        return NULL;
    }

    if (size1 > ((size_t)-1) / sizeof(int)) {
        return NULL;
    }

    int *result = malloc(size1 * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < size1; i++) {
        if (contains(arr2, size2, arr1[i]) &&
            !contains(result, count, arr1[i])) {
            result[count] = arr1[i];
            count++;
        }
    }

    if (count == 0) {
        free(result);
        return NULL;
    }

    qsort(result, count, sizeof(*result), compare_ints);

    *result_size = count;
    return result;
}

static int print_result(const int *result, size_t result_size)
{
    if (result == NULL || result_size == 0) {
        if (printf("[]\n") < 0) {
            return -1;
        }
        if (fflush(stdout) != 0) {
            return -1;
        }
        return 0;
    }

    if (printf("[") < 0) {
        return -1;
    }

    for (size_t i = 0; i < result_size; i++) {
        if (i > 0) {
            if (printf(", ") < 0) {
                return -1;
            }
        }
        if (printf("%d", result[i]) < 0) {
            return -1;
        }
    }

    if (printf("]\n") < 0) {
        return -1;
    }

    if (fflush(stdout) != 0) {
        return -1;
    }

    return 0;
}

static char *read_all_input(void)
{
    size_t capacity = 256;
    size_t length = 0;

    char *buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    int c;
    while ((c = getchar()) != EOF) {
        if (length + 1 >= capacity) {
            if (capacity > ((size_t)-1) / 2) {
                free(buffer);
                return NULL;
            }
            capacity *= 2;
            char *tmp = realloc(buffer, capacity);
            if (tmp == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = tmp;
        }
        buffer[length] = (char)c;
        length++;
    }

    if (length == 0) {
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';
    return buffer;
}

static int *parse_numbers(const char *begin, const char *end, size_t *size)
{
    if (begin == NULL || end == NULL || size == NULL || begin >= end) {
        if (size != NULL) {
            *size = 0;
        }
        return NULL;
    }

    *size = 0;

    size_t capacity = 16;
    size_t count = 0;

    int *arr = malloc(capacity * sizeof(*arr));
    if (arr == NULL) {
        return NULL;
    }

    const char *p = begin;
    while (p < end && *p != '\0') {
        if (isdigit((unsigned char)*p) ||
            ((*p == '-' || *p == '+') && (p + 1 < end) &&
             isdigit((unsigned char)p[1]))) {
            char *stop;
            errno = 0;
            long value = strtol(p, &stop, 10);
            if (errno == ERANGE || value < INT_MIN || value > INT_MAX) {
                free(arr);
                return NULL;
            }
            if (stop > end) {
                break;
            }
            if (count >= capacity) {
                if (capacity > ((size_t)-1) / (2 * sizeof(*arr))) {
                    free(arr);
                    return NULL;
                }
                capacity *= 2;
                int *tmp = realloc(arr, capacity * sizeof(*arr));
                if (tmp == NULL) {
                    free(arr);
                    return NULL;
                }
                arr = tmp;
            }
            arr[count] = (int)value;
            count++;
            p = stop;
        } else {
            p++;
        }
    }

    if (count == 0) {
        free(arr);
        return NULL;
    }

    *size = count;
    return arr;
}

static void parse_two_arrays(const char *input,
                             int **arr1, size_t *size1,
                             int **arr2, size_t *size2)
{
    *arr1 = NULL;
    *arr2 = NULL;
    *size1 = 0;
    *size2 = 0;

    if (input == NULL) {
        return;
    }

    const char *open1 = strchr(input, '[');
    if (open1 != NULL) {
        const char *close1 = strchr(open1, ']');
        if (close1 == NULL) {
            return;
        }
        *arr1 = parse_numbers(open1 + 1, close1, size1);
        const char *open2 = strchr(close1 + 1, '[');
        if (open2 == NULL) {
            return;
        }
        const char *close2 = strchr(open2, ']');
        if (close2 == NULL) {
            return;
        }
        *arr2 = parse_numbers(open2 + 1, close2, size2);
        return;
    }

    const char *newline = strchr(input, '\n');
    const char *input_end = input + strlen(input);
    if (newline != NULL) {
        *arr1 = parse_numbers(input, newline, size1);
        *arr2 = parse_numbers(newline + 1, input_end, size2);
    } else {
        *arr1 = parse_numbers(input, input_end, size1);
    }
}

int main(int argc, const char *argv[])
{
    size_t size1 = 0;
    size_t size2 = 0;
    size_t result_size = 0;
    int *arr1 = NULL;
    int *arr2 = NULL;
    char *input = NULL;

    if (argc >= 3) {
        arr1 = parse_numbers(argv[1], argv[1] + strlen(argv[1]), &size1);
        arr2 = parse_numbers(argv[2], argv[2] + strlen(argv[2]), &size2);
    } else {
        input = read_all_input();
        parse_two_arrays(input, &arr1, &