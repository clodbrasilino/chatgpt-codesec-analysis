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
    size_t buffer_size;

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

    if (end < start) {
        return NULL;
    }

    length = (size_t)(end - start);
    if (length >= SIZE_MAX - 1) {
        return NULL;
    }

    /* Possible weaknesses found:
     *  buffer_size is assigned 'length+1' here.
     */
    buffer_size = length + 1;
    result = (char *)malloc(buffer_size);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (result == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     *  Condition 'length<buffer_size' is always true [knownConditionTrueFalse]
     *  Condition 'length<buffer_size' is always true
     */
    if (length > 0 && length < buffer_size) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
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