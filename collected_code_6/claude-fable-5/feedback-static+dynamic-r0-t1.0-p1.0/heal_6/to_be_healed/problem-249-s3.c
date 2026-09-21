#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

static bool contains(const int *arr, size_t size, int value)
{
    size_t i;

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
  *  test case 2 failed: expected [10], got <no output>
  *  test case 0 failed: expected [1, 2, 8, 9], got <no output>
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

    return 0;
}

static char *read_line(void)
{
    char *line;
    size_t capacity;
    size_t length;
    int c;

    capacity = 128;
    length = 0;

    line = malloc(capacity);
    if (line == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = getchar()) != EOF && c != '\n') {
        if (length + 1 >= capacity) {
            char *tmp;

            if (capacity > ((size_t)-1) / 2) {
                free(line);
                return NULL;
            }
            capacity *= 2;
            tmp = realloc(line, capacity);
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
    int *arr;
    size_t capacity;
    size_t count;
    const char *p;
    char *end;
    long value;

    if (line == NULL || size == NULL) {
        return NULL;
    }

    *size = 0;

    capacity = 16;
    count = 0;

    arr = malloc(capacity * sizeof(*arr));
    if (arr == NULL) {
        return NULL;
    }

    p = line;
    while (*p != '\0') {
        if (isdigit((unsigned char)*p) ||
            ((*p == '-' || *p == '+') && isdigit((unsigned char)p[1]))) {
            value = strtol(p, &end, 10);
            if (count >= capacity) {
                int *tmp;

                if (capacity > ((size_t)-1) / (2 * sizeof(*arr))) {
                    free(arr);
                    return NULL;
                }
                capacity *= 2;
                tmp = realloc(arr, capacity * sizeof(*arr));
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
    /* Possible weaknesses found:
     *  The scope of the variable 'line' can be reduced. [variableScope]
     */
    char *line;
    /* Possible weaknesses found:
     *  The scope of the variable 'arr' can be reduced. [variableScope]
     */
    int *arr;

    if (size == NULL) {
        return NULL;
    }

    *size = 0;

    for (;;) {
        line = read_line();
        if (line == NULL) {
            return NULL;
        }

        arr = parse_array(line, size);
        free(line);

        if (arr != NULL) {
            return arr;
        }
    }
}

int main(void)
{
    int *arr1;
    int *arr2;
    size_t size1;
    size_t size2;
    size_t result_size;
    int *result;

    size1 = 0;
    size2 = 0;
    result_size = 0;

    arr1 = read_array(&size1);
    arr2 = read_array(&size2);

    result = intersection(arr1, size1, arr2, size2, &result_size);

    free(arr1);
    free(arr2);

    if (result == NULL || result_size == 0) {
        free(result);
        if (printf("[]\n") < 0) {
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