#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *data;
    size_t length;
} StringSpan;

char *concatenate_elements(const StringSpan elements[], size_t count)
{
    if (count != 0 && elements == NULL) {
        return NULL;
    }

    size_t total_length = 0;

    for (size_t i = 0; i < count; ++i) {
        if (elements[i].data == NULL) {
            return NULL;
        }

        if (i != 0) {
            if (total_length == SIZE_MAX) {
                return NULL;
            }
            ++total_length;
        }

        if (elements[i].length > SIZE_MAX - total_length) {
            return NULL;
        }

        total_length += elements[i].length;
    }

    if (total_length == SIZE_MAX) {
        return NULL;
    }

    char *result = malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t offset = 0;

    for (size_t i = 0; i < count; ++i) {
        if (i != 0) {
            result[offset++] = ' ';
        }

        for (size_t j = 0; j < elements[i].length; ++j) {
            result[offset++] = elements[i].data[j];
        }
    }

    result[offset] = '\0';
    return result;
}

int main(void)
{
    static const StringSpan elements[] = {
        { "", 0 },
        { "", 0 },
        { "hello", sizeof("hello") - 1 },
        { "there", sizeof("there") - 1 },
        { "have", sizeof("have") - 1 },
        { "a", sizeof("a") - 1 },
        { "rocky", sizeof("rocky") - 1 },
        { "day", sizeof("day") - 1 }
    };

    const size_t count = sizeof elements / sizeof elements[0];
    char *result = concatenate_elements(elements, count);

    if (result == NULL) {
        return EXIT_FAILURE;
    }

    if (puts(result) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}