#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *data;
    size_t length;
} StringSpan;
 /* Possible weaknesses found:
  *  test case 1 failed: expected '  Hi there How are you', got <no output>
  *  test case 0 failed: expected '  hello there have a rocky day', got <no output>
  *  test case 2 failed: expected '  Part of the journey is end', got <no output>
  */

char *concatenate_elements(const StringSpan elements[], size_t count)
{
    size_t total_length = 0;
    size_t offset = 0;

    if (count != 0 && elements == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        if (elements[i].data == NULL) {
            return NULL;
        }

        if (elements[i].length > SIZE_MAX - total_length) {
            return NULL;
        }

        total_length += elements[i].length;
    }

    if (count > 1) {
        size_t separator_count = count - 1;

        if (separator_count > SIZE_MAX - total_length) {
            return NULL;
        }

        total_length += separator_count;
    }

    if (total_length == SIZE_MAX) {
        return NULL;
    }

    char *result = malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

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
        { "", sizeof("") - 1 },
        { "", sizeof("") - 1 },
        { "hello", sizeof("hello") - 1 },
        { "there", sizeof("there") - 1 },
        { "have", sizeof("have") - 1 },
        { "a", sizeof("a") - 1 },
        { "rocky", sizeof("rocky") - 1 },
        { "day", sizeof("day") - 1 }
    };

    const size_t count = sizeof(elements) / sizeof(elements[0]);
    char *result = concatenate_elements(elements, count);

    if (result == NULL) {
        fputs("Failed to concatenate elements.\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(result) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}