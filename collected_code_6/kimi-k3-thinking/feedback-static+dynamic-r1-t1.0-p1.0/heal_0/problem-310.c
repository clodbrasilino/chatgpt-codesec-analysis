#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <stdint.h>

typedef struct {
    long *data;
    size_t size;
} Tuple;

static void tuple_free(Tuple *tuple)
{
    if (tuple != NULL) {
        free(tuple->data);
        tuple->data = NULL;
        tuple->size = 0;
    }
}

static int string_to_tuple(const char *str, Tuple *tuple)
{
    size_t count = 1;
    size_t idx = 0;
    const char *start = NULL;
    const char *p = NULL;
    long *data = NULL;

    if (str == NULL || tuple == NULL || *str == '\0') {
        return -1;
    }

    tuple->data = NULL;
    tuple->size = 0;

    start = str;
    if (*start == '(') {
        start++;
    }
    if (*start == '\0') {
        return -1;
    }

    for (p = start; *p != '\0'; p++) {
        if (*p == ',') {
            count++;
        }
    }

    if (count > SIZE_MAX / sizeof(*data)) {
        return -1;
    }

    data = malloc(count * sizeof(*data));
    if (data == NULL) {
        return -1;
    }

    p = start;
    while (*p != '\0' && *p != ')') {
        char *end = NULL;
        long value;

        while (isspace((unsigned char)*p)) {
            p++;
        }

        errno = 0;
        value = strtol(p, &end, 10);
        if (errno != 0 || end == p) {
            free(data);
            return -1;
        }
        data[idx++] = value;
        p = end;

        while (isspace((unsigned char)*p)) {
            p++;
        }

        if (*p == ',') {
            p++;
        } else if (*p != '\0' && *p != ')') {
            free(data);
            return -1;
        }
    }

    if (idx == 0) {
        free(data);
        return -1;
    }

    tuple->data = data;
    tuple->size = idx;
    return 0;
}

int main(void)
{
    const char *input = "(10, 20, 30, -40, 50)";
    Tuple tuple;
    size_t i;

    if (string_to_tuple(input, &tuple) != 0) {
        fprintf(stderr, "Error: failed to convert string to tuple\n");
        return EXIT_FAILURE;
    }

    printf("Tuple (%zu elements): (", tuple.size);
    for (i = 0; i < tuple.size; i++) {
        printf("%ld%s", tuple.data[i], (i + 1 < tuple.size) ? ", " : "");
    }
    printf(")\n");

    tuple_free(&tuple);
    return EXIT_SUCCESS;
}