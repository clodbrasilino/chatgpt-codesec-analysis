#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *extract_quoted(const char *input)
{
    const char *start;
    const char *end;
    size_t length;
    size_t alloc_size;
    char *result;

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

    if (length >= SIZE_MAX) {
        return NULL;
    }

    /* Possible weaknesses found:
     *  alloc_size is assigned 'length+1U' here.
     */
    alloc_size = length + 1U;
    /* Possible weaknesses found:
     *  Condition 'alloc_size<length' is always false
     *  Condition 'alloc_size<length' is always false [knownConditionTrueFalse]
     */
    if (alloc_size < length) {
        return NULL;
    }

    result = malloc(alloc_size);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (result == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     *  Condition 'length<alloc_size' is always true
     *  Condition 'length<alloc_size' is always true [knownConditionTrueFalse]
     */
    if (length > 0U && length < alloc_size) {
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
    const char *test = "The value is \"hello world\" in this string";
    char *extracted;

    extracted = extract_quoted(test);
    if (extracted == NULL) {
        if (fprintf(stderr, "No quoted value found or allocation failed\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Extracted: %s\n", extracted) < 0) {
        free(extracted);
        return EXIT_FAILURE;
    }

    free(extracted);
    return EXIT_SUCCESS;
}