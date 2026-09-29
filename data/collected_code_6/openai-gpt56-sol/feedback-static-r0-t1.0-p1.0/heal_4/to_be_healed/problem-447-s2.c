#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>

#define MAX_INPUT_LENGTH 4096

static int read_line(char *buffer, size_t capacity)
{
    if (buffer == NULL || capacity < 2) {
        return -1;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(buffer);

    if (length > 0 && buffer[length - 1] == '\n') {
        buffer[length - 1] = '\0';
        return 0;
    }

    if (feof(stdin)) {
        return 0;
    }

    int ch;
    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
    }

    return -1;
}

static int parse_size(const char *text, size_t *result)
{
    if (text == NULL || result == NULL) {
        return -1;
    }

    while (isspace((unsigned char)*text)) {
        ++text;
    }

    if (*text == '\0' || *text == '-' || *text == '+') {
        return -1;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t value = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || value > SIZE_MAX) {
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *result = (size_t)value;
    return 0;
}

static int parse_int64(const char *text, int64_t *result)
{
    if (text == NULL || result == NULL) {
        return -1;
    }

    while (isspace((unsigned char)*text)) {
        ++text;
    }

    if (*text == '\0') {
        return -1;
    }

    errno = 0;
    char *end = NULL;
    intmax_t value = strtoimax(text, &end, 10);

    if (errno == ERANGE || end == text ||
        value < INT64_MIN || value > INT64_MAX) {
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *result = (int64_t)value;
    return 0;
}

static int cube_int64(int64_t value, int64_t *result)
{
    if (result == NULL ||
        value < INT64_C(-2097152) ||
        value > INT64_C(2097151)) {
        return -1;
    }

    *result = value * value * value;
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_INPUT_LENGTH];
    size_t count = 0;

    if (printf("Enter the number of elements: ") < 0 ||
        fflush(stdout) == EOF ||
        read_line(input, sizeof(input)) != 0 ||
        parse_size(input, &count) != 0 ||
        count == 0 ||
        count > SIZE_MAX / sizeof(int64_t)) {
        fprintf(stderr, "Invalid element count.\n");
        return EXIT_FAILURE;
    }

    int64_t *values = malloc(count * sizeof(*values));

    if (values == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (printf("Element %zu: ", i + 1) < 0 ||
            fflush(stdout) == EOF ||
            read_line(input, sizeof(input)) != 0 ||
            parse_int64(input, &values[i]) != 0) {
            fprintf(stderr, "Invalid input.\n");
            free(values);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        int64_t cube = 0;

        if (cube_int64(values[i], &cube) != 0) {
            fprintf(stderr,
                    "Cube of element %zu is outside the int64_t range.\n",
                    i + 1);
            free(values);
            return EXIT_FAILURE;
        }

        if (printf("%" PRId64 "%c",
                   cube, i + 1 == count ? '\n' : ' ') < 0) {
            free(values);
            return EXIT_FAILURE;
        }
    }

    free(values);
    return EXIT_SUCCESS;
}