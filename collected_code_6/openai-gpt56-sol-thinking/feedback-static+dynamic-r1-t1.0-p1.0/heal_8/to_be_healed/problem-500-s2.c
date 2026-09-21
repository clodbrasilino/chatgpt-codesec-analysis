#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *data;
    size_t length;
} StringSpan;

static int checked_add_size(size_t left, size_t right, size_t *result)
{
    if (right > SIZE_MAX - left) {
        return 0;
    }

    *result = left + right;
    return 1;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected '  Hi there How are you', got <no output>
  *  test case 0 failed: expected '  hello there have a rocky day', got <no output>
  *  test case 2 failed: expected '  Part of the journey is end', got <no output>
  */

char *concatenate_elements(const StringSpan elements[], size_t count)
{
    if (count != 0 && elements == NULL) {
        return NULL;
    }

    size_t total_length = 0;

    for (size_t i = 0; i < count; ++i) {
        if (elements[i].length != 0 && elements[i].data == NULL) {
            return NULL;
        }

        if (i != 0 && !checked_add_size(total_length, 1, &total_length)) {
            return NULL;
        }

        if (!checked_add_size(total_length, elements[i].length, &total_length)) {
            return NULL;
        }
    }

    size_t allocation_size;
    if (!checked_add_size(total_length, 1, &allocation_size)) {
        return NULL;
    }

    char *result = malloc(allocation_size);
    if (result == NULL) {
        return NULL;
    }

    size_t offset = 0;

    for (size_t i = 0; i < count; ++i) {
        if (i != 0) {
            if (offset >= total_length) {
                free(result);
                return NULL;
            }

            result[offset++] = ' ';
        }

        if (elements[i].length > total_length - offset) {
            free(result);
            return NULL;
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

    const size_t count = sizeof(elements) / sizeof(elements[0]);
    char *result = concatenate_elements(elements, count);

    if (result == NULL) {
        return EXIT_FAILURE;
    }

    int status = puts(result);
    free(result);

    return status == EOF ? EXIT_FAILURE : EXIT_SUCCESS;
}