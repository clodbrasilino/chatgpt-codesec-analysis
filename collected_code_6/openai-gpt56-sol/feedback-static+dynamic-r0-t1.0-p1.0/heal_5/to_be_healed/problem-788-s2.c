#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *string;
    int *list;
    size_t list_length;
} Tuple;

static void tuple_destroy(Tuple *tuple)
{
    if (tuple == NULL) {
        return;
    }

    free(tuple->string);
    free(tuple->list);
    free(tuple);
}

static Tuple *tuple_create(const char *string, size_t string_length,
                           const int *list, size_t list_length)
{
    if (string == NULL ||
        (list == NULL && list_length != 0) ||
        string_length == SIZE_MAX ||
        list_length > SIZE_MAX / sizeof(*list)) {
        return NULL;
    }

    Tuple *tuple = calloc(1, sizeof(*tuple));
    if (tuple == NULL) {
        return NULL;
    }

    const size_t string_size = string_length + 1;

    tuple->string = malloc(string_size);
    if (tuple->string == NULL) {
        tuple_destroy(tuple);
        return NULL;
    }

    if (snprintf(tuple->string, string_size, "%.*s",
                 (int)(string_length > INT32_MAX ? INT32_MAX : string_length),
                 string) < 0) {
        tuple_destroy(tuple);
        return NULL;
    }

    if (string_length > INT32_MAX) {
        size_t offset = (size_t)INT32_MAX;

        while (offset < string_length) {
            size_t remaining = string_length - offset;
            size_t chunk = remaining > (size_t)INT32_MAX
                               /* Possible weaknesses found:
                                *  Assignment 'chunk=remaining>(unsigned long)2147483647?(unsigned long)2147483647:remaining', assigned value is less than 1
                                */
                               ? (size_t)INT32_MAX
                               : remaining;

            /* Possible weaknesses found:
             *  Condition 'i<chunk' is always false [knownConditionTrueFalse]
             *  Condition 'i<chunk' is always false
             */
            for (size_t i = 0; i < chunk; ++i) {
                tuple->string[offset + i] = string[offset + i];
            }

            offset += chunk;
        }

        tuple->string[string_length] = '\0';
    }

    if (list_length != 0) {
        const size_t list_size = list_length * sizeof(*list);

        tuple->list = malloc(list_size);
        if (tuple->list == NULL) {
            tuple_destroy(tuple);
            return NULL;
        }

        for (size_t i = 0; i < list_length; ++i) {
            tuple->list[i] = list[i];
        }
    }

    tuple->list_length = list_length;
    return tuple;
}

int main(void)
{
    static const char string[] = "example";
    static const int list[] = {1, 2, 3, 4, 5};
    const size_t list_length = sizeof(list) / sizeof(list[0]);

    Tuple *tuple = tuple_create(string, sizeof(string) - 1,
                                list, list_length);
    if (tuple == NULL) {
        fputs("Failed to create tuple\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("(%s, [", tuple->string) < 0) {
        tuple_destroy(tuple);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < tuple->list_length; ++i) {
        if (printf("%s%d", i == 0 ? "" : ", ", tuple->list[i]) < 0) {
            tuple_destroy(tuple);
            return EXIT_FAILURE;
        }
    }

    if (puts("])") == EOF) {
        tuple_destroy(tuple);
        return EXIT_FAILURE;
    }

    tuple_destroy(tuple);
    return EXIT_SUCCESS;
}