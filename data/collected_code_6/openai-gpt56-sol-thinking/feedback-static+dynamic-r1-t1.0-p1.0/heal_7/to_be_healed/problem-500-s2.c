#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    if (count > 0 && elements == NULL) {
        return NULL;
    }

    size_t total_length = count > 0 ? count - 1 : 0;

    for (size_t i = 0; i < count; ++i) {
        if (elements[i].length > 0 && elements[i].data == NULL) {
            return NULL;
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
        if (i > 0) {
            result[offset++] = ' ';
        }

        if (elements[i].length > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + offset, elements[i].data, elements[i].length);
            offset += elements[i].length;
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

    const size_t count = sizeof(elements) / sizeof(elements[0]);
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