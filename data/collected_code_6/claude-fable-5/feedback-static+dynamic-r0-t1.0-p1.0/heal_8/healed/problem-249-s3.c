#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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

static char *read_line(void)
{
    size_t capacity = 128;
    size_t length = 0;

    char *line = malloc(capacity);
    if (line == NULL) {
        return NULL;
    }

    int c;
    while ((c = getchar()) != EOF && c != '\n') {
        if (length + 1 >= capacity) {
            if (capacity > ((size_t)-1) / 2) {
                free(line);
                return NULL;
            }
            capacity *= 2;
            char *tmp = realloc(line, capacity);
            if (tmp == NULL) {
                free(line);
                return NULL;
            }
            line = tmp;
        }
        line[length] = (char)c;
        length++;
    }

    if (length == 0 && c == EOF) {
        free(line);
        return NULL;
    }

    line[length] = '\0';
    return line;
}

static int *parse_array(const char *line, size_t *size)
{
    if (line == NULL || size == NULL) {
        return NULL;
    }

    *size = 0;

    size_t capacity = 16;
    size_t count = 0;

    int *arr = malloc(capacity * sizeof(*arr));
    if (arr == NULL) {
        return NULL;
    }

    const char *p = line;
    while (*p != '\0') {
        if (isdigit((unsigned char)*p) ||
            ((*p == '-' || *p == '+') && isdigit((unsigned char)p[1]))) {
            char *end;
            long value = strtol(p, &end, 10);
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

static int *read_array(size_t *size)
{
    if (size == NULL) {
        return NULL;
    }

    *size = 0;

    for (;;) {
        char *line = read_line();
        if (line == NULL) {
            return NULL;
        }

        int *arr = parse_array(line, size);
        free(line);

        if (arr != NULL) {
            return arr;
        }
    }
}

int main(int argc, const char *argv[])
{
    size_t size1 = 0;
    size_t size2 = 0;
    size_t result_size = 0;
    int *arr1 = NULL;
    int *arr2 = NULL;

    if (argc >= 3) {
        arr1 = parse_array(argv[1], &size1);
        arr2 = parse_array(argv[2], &size2);
    } else {
        arr1 = read_array(&size1);
        arr2 = read_array(&size2);
    }

    int *result = intersection(arr1, size1, arr2, size2, &result_size);

    free(arr1);
    free(arr2);

    if (print_result(result, result_size) != 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}