#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *extract_quoted(const char *input)
{
    const char *start;
    const char *end;
    char *result;
    size_t length;

    if (input == NULL) {
        return NULL;
    }

    start = strchr(input, '"');
    if (start == NULL) {
        return NULL;
    }
    start++;

    end = strchr(start, '"');
    if (end == NULL) {
        return NULL;
    }

    length = (size_t)(end - start);
    if (length >= SIZE_MAX - 1) {
        return NULL;
    }

    result = malloc(length + 1);
    if (result == NULL) {
        return NULL;
    }

    if (length > 0) {
        memcpy(result, start, length);
    }
    result[length] = '\0';

    return result;
}

int main(void)
{
    const char *text = "He said \"hello world\" to everyone.";
    char *extracted;

    extracted = extract_quoted(text);
    if (extracted == NULL) {
        fprintf(stderr, "No quoted value found or allocation failed.\n");
        return EXIT_FAILURE;
    }

    if (printf("Extracted: %s\n", extracted) < 0) {
        free(extracted);
        return EXIT_FAILURE;
    }

    free(extracted);
    return EXIT_SUCCESS;
}