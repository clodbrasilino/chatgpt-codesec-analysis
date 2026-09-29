#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

static char *trim_copy(const char *src)
{
    size_t len;
    size_t start;
    size_t end;
    char *out;

    if (src == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(src);
    start = 0;
    while (start < len && isspace((unsigned char)src[start])) {
        start++;
    }
    end = len;
    while (end > start && isspace((unsigned char)src[end - 1U])) {
        end--;
    }

    out = malloc((end - start) + 1U);
    if (out == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(out, src + start, end - start);
    out[end - start] = '\0';
    return out;
}

static char *remove_pattern(const char *src, const char *pattern)
{
    size_t src_len;
    size_t pat_len;
    size_t out_len;
    const char *cursor;
    const char *hit;
    char *copy;
    char *trimmed;
    char *dest;
    size_t tail;

    if (src == NULL || pattern == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    src_len = strlen(src);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    pat_len = strlen(pattern);

    if (pat_len == 0U) {
        copy = malloc(src_len + 1U);
        if (copy == NULL) {
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, src, src_len + 1U);
        trimmed = trim_copy(copy);
        free(copy);
        return trimmed;
    }

    out_len = 0U;
    cursor = src;
    while ((hit = strstr(cursor, pattern)) != NULL) {
        out_len += (size_t)(hit - cursor);
        cursor = hit + pat_len;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    out_len += strlen(cursor);

    copy = malloc(out_len + 1U);
    if (copy == NULL) {
        return NULL;
    }

    dest = copy;
    cursor = src;
    while ((hit = strstr(cursor, pattern)) != NULL) {
        size_t chunk = (size_t)(hit - cursor);
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dest, cursor, chunk);
        dest += chunk;
        cursor = hit + pat_len;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    tail = strlen(cursor);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dest, cursor, tail);
    dest += tail;
    *dest = '\0';

    trimmed = trim_copy(copy);
    free(copy);
    return trimmed;
}

static void free_word_list(char **list, size_t count)
{
    size_t i;

    if (list == NULL) {
        return;
    }

    for (i = 0; i < count; i++) {
        free(list[i]);
    }
    free(list);
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['Red', '', 'Green', 'Orange', 'White'], got <no output>
  *  test case 1 failed: expected ['Red', '', 'Green', 'Orange', 'White'], got <no output>
  *  test case 2 failed: expected ['Red &', 'Orange+', 'Green', 'Orange', 'White'], got <no output>
  */

static char **remove_words(const char *const *words, size_t count,
                           const char *pattern, size_t *out_count)
{
    char **result;
    size_t kept;
    size_t i;

    if (out_count == NULL) {
        return NULL;
    }

    *out_count = 0;

    if (words == NULL || pattern == NULL || count == 0U) {
        return NULL;
    }

    if (count > SIZE_MAX / sizeof(*result)) {
        return NULL;
    }

    result = malloc(count * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    kept = 0;
    for (i = 0; i < count; i++) {
        if (words[i] == NULL) {
            continue;
        }
        result[kept] = remove_pattern(words[i], pattern);
        if (result[kept] == NULL) {
            free_word_list(result, kept);
            return NULL;
        }
        kept++;
    }

    if (kept == 0U) {
        free(result);
        return NULL;
    }

    if (kept < count) {
        char **shrunk = realloc(result, kept * sizeof(*shrunk));
        if (shrunk != NULL) {
            result = shrunk;
        }
    }

    *out_count = kept;
    return result;
}

static char *read_line(FILE *stream)
{
    size_t capacity = 64;
    size_t length = 0;
    char *buffer;
    int ch;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (length + 1U >= capacity) {
            char *grown;
            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return NULL;
            }
            capacity *= 2U;
            grown = realloc(buffer, capacity);
            if (grown == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = grown;
        }
        buffer[length++] = (char)ch;
    }

    if (ch == EOF && length == 0U) {
        free(buffer);
        return NULL;
    }

    if (length > 0U && buffer[length - 1U] == '\r') {
        length--;
    }
    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char **lines = NULL;
    size_t line_count = 0;
    size_t capacity = 0;
    char *line;
    char **filtered;
    size_t filtered_count;
    size_t word_count;
    const char *pattern;
    size_t i;

    while ((line = read_line(stdin)) != NULL) {
        if (line_count == capacity) {
            size_t new_capacity = (capacity == 0U) ? 8U : capacity * 2U;
            char **grown;
            if (new_capacity > SIZE_MAX / sizeof(*lines)) {
                free(line);
                free_word_list(lines, line_count);
                return EXIT_FAILURE;
            }
            grown = realloc(lines, new_capacity * sizeof(*grown));
            if (grown == NULL) {
                free(line);
                free_word_list(lines, line_count);
                return EXIT_FAILURE;
            }
            lines = grown;
            capacity = new_capacity;
        }
        lines[line_count++] = line;
    }

    if (line_count < 2U) {
        fprintf(stderr, "Not enough input.\n");
        free_word_list(lines, line_count);
        return EXIT_FAILURE;
    }

    word_count = line_count - 1U;
    pattern = lines[line_count - 1U];

    filtered = remove_words((const char *const *)lines, word_count,
                            pattern, &filtered_count);
    if (filtered == NULL) {
        fprintf(stderr, "No words remain or an error occurred.\n");
        free_word_list(lines, line_count);
        return EXIT_FAILURE;
    }

    for (i = 0; i < filtered_count; i++) {
        if (printf("%s\n", filtered[i]) < 0) {
            free_word_list(filtered, filtered_count);
            free_word_list(lines, line_count);
            return EXIT_FAILURE;
        }
    }

    if (fflush(stdout) != 0) {
        free_word_list(filtered, filtered_count);
        free_word_list(lines, line_count);
        return EXIT_FAILURE;
    }

    free_word_list(filtered, filtered_count);
    free_word_list(lines, line_count);
    return EXIT_SUCCESS;
}