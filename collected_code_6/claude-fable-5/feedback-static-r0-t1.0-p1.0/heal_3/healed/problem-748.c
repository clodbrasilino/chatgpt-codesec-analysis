#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LEN 4096U

static int safe_copy(char *dest, size_t dest_capacity, size_t dest_offset,
                     const char *src, size_t count)
{
    if (dest == NULL || src == NULL) {
        return -1;
    }
    if (dest_offset > dest_capacity) {
        return -1;
    }
    if (count > (dest_capacity - dest_offset)) {
        return -1;
    }
    memcpy(dest + dest_offset, src, count);
    return 0;
}

char *add_spaces(const char *input)
{
    regex_t regex;
    regmatch_t match;
    char *result;
    size_t len;
    size_t capacity;
    size_t out;
    size_t offset;
    int rc;

    if (input == NULL) {
        return NULL;
    }

    len = strnlen(input, MAX_INPUT_LEN);
    if (len >= MAX_INPUT_LEN) {
        return NULL;
    }

    rc = regcomp(&regex, "[A-Z]", REG_EXTENDED);
    if (rc != 0) {
        return NULL;
    }

    capacity = (2U * len) + 1U;
    result = malloc(capacity);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    out = 0U;
    offset = 0U;
    while ((offset < len) &&
           (regexec(&regex, input + offset, 1U, &match, 0) == 0)) {
        size_t start = offset + (size_t)match.rm_so;
        size_t chunk = (size_t)match.rm_so;

        if ((out + chunk + 2U) > capacity) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        if (safe_copy(result, capacity, out, input + offset, chunk) != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        out += chunk;

        if ((start > 0U) && (input[start - 1U] != ' ')) {
            result[out] = ' ';
            out++;
        }

        result[out] = input[start];
        out++;
        offset = start + 1U;
    }

    if ((out + (len - offset) + 1U) > capacity) {
        free(result);
        regfree(&regex);
        return NULL;
    }

    if (safe_copy(result, capacity, out, input + offset, len - offset) != 0) {
        free(result);
        regfree(&regex);
        return NULL;
    }
    out += len - offset;
    result[out] = '\0';

    regfree(&regex);
    return result;
}

int main(void)
{
    const char *text = "HelloWorldThisIsATestString";
    char *spaced;

    spaced = add_spaces(text);
    if (spaced == NULL) {
        fprintf(stderr, "Failed to process input string\n");
        return EXIT_FAILURE;
    }

    printf("Input : %s\n", text);
    printf("Output: %s\n", spaced);

    free(spaced);
    return EXIT_SUCCESS;
}