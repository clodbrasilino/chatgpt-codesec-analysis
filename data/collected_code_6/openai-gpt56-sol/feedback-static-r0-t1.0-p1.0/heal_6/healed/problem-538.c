#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int append_text(char **buffer, size_t *length, size_t *capacity,
                       const char *text, size_t text_length)
{
    size_t required;
    size_t new_capacity;
    char *resized;

    if (buffer == NULL || length == NULL || capacity == NULL ||
        (text == NULL && text_length != 0) ||
        *length > *capacity ||
        (*buffer == NULL && *capacity != 0)) {
        return -1;
    }

    if (text_length > SIZE_MAX - *length ||
        *length + text_length == SIZE_MAX) {
        return -1;
    }

    required = *length + text_length + 1;

    if (required > *capacity) {
        new_capacity = (*capacity == 0) ? 16 : *capacity;

        while (new_capacity < required) {
            if (new_capacity > SIZE_MAX / 2) {
                new_capacity = required;
                break;
            }
            new_capacity *= 2;
        }

        resized = realloc(*buffer, new_capacity);
        if (resized == NULL) {
            return -1;
        }

        *buffer = resized;
        *capacity = new_capacity;
    }

    if (text_length > 0) {
        memmove(*buffer + *length, text, text_length);
        *length += text_length;
    }

    (*buffer)[*length] = '\0';
    return 0;
}

static char *string_list_to_tuple(const char *const strings[], size_t count)
{
    char *result = NULL;
    size_t length = 0;
    size_t capacity = 0;
    size_t i;

    if (strings == NULL && count != 0) {
        return NULL;
    }

    if (append_text(&result, &length, &capacity, "(", 1) != 0) {
        free(result);
        return NULL;
    }

    for (i = 0; i < count; ++i) {
        const unsigned char *current;

        if (strings[i] == NULL) {
            free(result);
            return NULL;
        }

        if (i != 0 &&
            append_text(&result, &length, &capacity, ", ", 2) != 0) {
            free(result);
            return NULL;
        }

        if (append_text(&result, &length, &capacity, "\"", 1) != 0) {
            free(result);
            return NULL;
        }

        current = (const unsigned char *)strings[i];

        while (*current != '\0') {
            char encoded[2];
            size_t encoded_length;

            if (*current == '"' || *current == '\\') {
                encoded[0] = '\\';
                encoded[1] = (char)*current;
                encoded_length = sizeof encoded;
            } else {
                encoded[0] = (char)*current;
                encoded_length = 1;
            }

            if (append_text(&result, &length, &capacity,
                            encoded, encoded_length) != 0) {
                free(result);
                return NULL;
            }

            ++current;
        }

        if (append_text(&result, &length, &capacity, "\"", 1) != 0) {
            free(result);
            return NULL;
        }
    }

    if (count == 1 &&
        append_text(&result, &length, &capacity, ",", 1) != 0) {
        free(result);
        return NULL;
    }

    if (append_text(&result, &length, &capacity, ")", 1) != 0) {
        free(result);
        return NULL;
    }

    return result;
}

int main(void)
{
    const char *strings[] = {"apple", "banana", "cherry"};
    const size_t count = sizeof strings / sizeof strings[0];
    char *tuple = string_list_to_tuple(strings, count);

    if (tuple == NULL) {
        fputs("Failed to create tuple\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", tuple) < 0) {
        free(tuple);
        return EXIT_FAILURE;
    }

    free(tuple);
    return EXIT_SUCCESS;
}