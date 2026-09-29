#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

static int is_numeric(const char *s)
{
    size_t i = 0;

    if (s == NULL || s[0] == '\0') {
        return 0;
    }
    if (s[0] == '+' || s[0] == '-') {
        i = 1;
        if (s[1] == '\0') {
            return 0;
        }
    }
    for (; s[i] != '\0'; i++) {
        if (!isdigit((unsigned char)s[i])) {
            return 0;
        }
    }
    return 1;
}

static char *duplicate_string(const char *s)
{
    size_t len;
    char *copy;

    if (s == NULL) {
        return NULL;
    }
    len = strlen(s) + 1;
    copy = malloc(len);
    if (copy == NULL) {
        return NULL;
    }
    memcpy(copy, s, len);
    return copy;
}

static void free_string_array(char **arr, size_t n)
{
    size_t i;

    if (arr == NULL) {
        return;
    }
    for (i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['Dart', '368', 'is', '100', '181', 'Super', '18'], got <no output>
  *  test case 2 failed: expected ['Flutter', '484', 'is', '77', '129', 'Magnificent', '45'], got <no output>
  *  test case 0 failed: expected ['MSM', '240', 'is', '104', '129', 'best', '10'], got <no output>
  */

static char **increment_numeric_strings(const char *const *input, size_t n, long k)
{
    char **result;
    size_t i;

    if (input == NULL || n == 0) {
        return NULL;
    }
    result = calloc(n, sizeof(char *));
    if (result == NULL) {
        return NULL;
    }
    for (i = 0; i < n; i++) {
        if (input[i] == NULL) {
            free_string_array(result, i);
            return NULL;
        }
        if (is_numeric(input[i])) {
            long value;
            char *endptr;
            char buffer[64];
            int written;

            errno = 0;
            value = strtol(input[i], &endptr, 10);
            if (errno == ERANGE || *endptr != '\0') {
                free_string_array(result, i);
                return NULL;
            }
            if ((k > 0 && value > LONG_MAX - k) ||
                (k < 0 && value < LONG_MIN - k)) {
                free_string_array(result, i);
                return NULL;
            }
            value += k;
            written = snprintf(buffer, sizeof(buffer), "%ld", value);
            if (written < 0 || (size_t)written >= sizeof(buffer)) {
                free_string_array(result, i);
                return NULL;
            }
            result[i] = duplicate_string(buffer);
        } else {
            result[i] = duplicate_string(input[i]);
        }
        if (result[i] == NULL) {
            free_string_array(result, i);
            return NULL;
        }
    }
    return result;
}

int main(void)
{
    const char *const strings[] = { "MSM", "234", "is", "98", "123", "best", "4" };
    size_t count = sizeof(strings) / sizeof(strings[0]);
    long k = 6;
    char **updated;
    size_t i;

    updated = increment_numeric_strings(strings, count, k);
    if (updated == NULL) {
        fprintf(stderr, "Failed to process strings\n");
        return EXIT_FAILURE;
    }
    for (i = 0; i < count; i++) {
        if (printf("%s\n", updated[i]) < 0) {
            free_string_array(updated, count);
            return EXIT_FAILURE;
        }
    }
    free_string_array(updated, count);
    return EXIT_SUCCESS;
}