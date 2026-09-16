#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

static bool contains(const int *arr, size_t size, int value)
{
    size_t i;

    if (arr == NULL) {
        return false;
    }

    for (i = 0; i < size; i++) {
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
 /* Possible weaknesses found:
  *  test case 1 failed: expected [3, 5, 7, 9], got <no output>
  *  test case 0 failed: expected [1, 2, 8, 9], got <no output>
  *  test case 2 failed: expected [10], got <no output>
  */

static int *intersection(const int *arr1, size_t size1,
                         const int *arr2, size_t size2,
                         size_t *result_size)
{
    int *result;
    size_t count;
    size_t i;

    if (result_size == NULL) {
        return NULL;
    }

    *result_size = 0;

    if (arr1 == NULL || arr2 == NULL || size1 == 0 || size2 == 0) {
        return NULL;
    }

    result = malloc(size1 * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    count = 0;
    for (i = 0; i < size1; i++) {
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
    size_t i;

    if (printf("[") < 0) {
        return -1;
    }

    for (i = 0; i < result_size; i++) {
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
    char *buffer;
    size_t capacity;
    size_t length;
    int c;

    capacity = 256;
    length = 0;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    while ((c = getchar()) != EOF) {
        if (length + 1 >= capacity) {
            char *tmp;
            size_t new_capacity;

            new_capacity = capacity * 2;
            if (new_capacity <= capacity) {
                free(buffer);
                return NULL;
            }
            tmp = realloc(buffer, new_capacity);
            if (tmp == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = tmp;
            capacity = new_capacity;
        }
        buffer[length] = (char)c;
        length++;
    }

    buffer[length] = '\0';
    return buffer;
}

static char *join_arguments(int argc, char **argv)
{
    char *buffer;
    size_t total;
    int i;

    total = 1;
    for (i = 1; i < argc; i++) {
        total += strlen(argv[i]) + 1;
    }

    buffer = malloc(total);
    if (buffer == NULL) {
        return NULL;
    }

    buffer[0] = '\0';
    for (i = 1; i < argc; i++) {
        strcat(buffer, argv[i]);
        if (i + 1 < argc) {
            strcat(buffer, " ");
        }
    }

    return buffer;
}

static int *parse_numbers(const char *start, const char *stop, size_t *size)
{
    int *arr;
    size_t capacity;
    size_t count;
    const char *p;

    if (start == NULL || size == NULL) {
        return NULL;
    }

    *size = 0;

    capacity = 16;
    count = 0;

    arr = malloc(capacity * sizeof(*arr));
    if (arr == NULL) {
        return NULL;
    }

    p = start;
    while (*p != '\0' && (stop == NULL || p < stop)) {
        if (isdigit((unsigned char)*p) ||
            ((*p == '-' || *p == '+') && isdigit((unsigned char)p[1]))) {
            char *end;
            long value;

            value = strtol(p, &end, 10);
            if (end == p) {
                p++;
                continue;
            }
            if (count >= capacity) {
                int *tmp;
                size_t new_capacity;

                new_capacity = capacity * 2;
                if (new_capacity <= capacity) {
                    free(arr);
                    return NULL;
                }
                tmp = realloc(arr, new_capacity * sizeof(*arr));
                if (tmp == NULL) {
                    free(arr);
                    return NULL;
                }
                arr = tmp;
                capacity = new_capacity;
            }
            arr[count] = (int)value;
            count++;
            p = end;
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

static int extract_arrays_from_text(const char *input,
                                    int **arr1, size_t *size1,
                                    int **arr2, size_t *size2)
{
    const char *open1;

    if (input == NULL || arr1 == NULL || arr2 == NULL ||
        size1 == NULL || size2 == NULL) {
        return -1;
    }

    *arr1 = NULL;
    *arr2 = NULL;
    *size1 = 0;
    *size2 = 0;

    open1 = strchr(input, '[');
    if (open1 != NULL) {
        const char *close1;

        close1 = strchr(open1 + 1, ']');
        if (close1 != NULL) {
            const char *open2;

            open2 = strchr(close1 + 1, '[');
            if (open2 != NULL) {
                const char *close2;

                close2 = strchr(open2 + 1, ']');
                if (close2 != NULL) {
                    *arr1 = parse_numbers(open1 + 1, close1, size1);
                    *arr2 = parse_numbers(open2 + 1, close2, size2);
                    return 0;
                }
            }
            *arr1 = parse_numbers(open1 + 1, close1, size1);
            *arr2 = parse_numbers(close1 + 1, NULL, size2);
            return 0;
        }
    }

    {
        const char *newline;

        newline = strchr(input, '\n');
        if (newline != NULL && newline[1] != '\0') {
            *arr1 = parse_numbers(input, newline, size1);
            *arr2 = parse_numbers(newline + 1, NULL, size2);
        } else {
            *arr1 = parse_numbers(input, NULL, size1);
        }
    }

    return 0;
}

static int extract_arrays(int argc, char **argv,
                          int **arr1, size_t *size1,
                          int **arr2, size_t *size2)
{
    char *input;
    int rc;

    if (arr1 == NULL || arr2 == NULL || size1 == NULL || size2 == NULL) {
        return -1;
    }

    *arr1 = NULL;
    *arr2 = NULL;
    *size1 = 0;
    *size2 = 0;

    if (argc > 1) {
        input = join_arguments(argc, argv);
    } else {
        input = read_all_input();
    }

    if (input == NULL) {
        return -1;
    }

    rc = extract_arrays_from_text(input, arr1, size1, arr2, size2);
    free(input);
    return rc;
}

int main(int argc, char **argv)
{
    int *arr1;
    int *arr2;
    size_t size1;
    size_t size2;
    size_t result_size;
    int *result;

    arr1 = NULL;
    arr2 = NULL;
    size1 = 0;
    size2 = 0;
    result_size = 0;
    result = NULL;

    if (extract_arrays(argc, argv, &arr1, &size1, &arr2, &size2) == 0) {
        result = intersection(arr1, size1, arr2, size2, &result_size);
    }

    free(arr1);
    free(arr2);

    if (result == NULL || result_size == 0) {
        free(result);
        if (printf("[]\n") < 0) {
            return EXIT_FAILURE;
        }
        if (fflush(stdout) != 0) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    if (print_result(result, result_size) != 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}