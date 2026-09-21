#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRINGS 1000
#define MAX_LENGTH 100

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[MAX_LENGTH];
    int count;
} StringCount;

static char *safe_strndup(const char *src, size_t max_len) {
    if (!src || max_len == 0) return NULL;
    size_t len = strnlen(src, max_len);
    if (len >= max_len) len = max_len - 1;
    char *dest = malloc(len + 1);
    if (dest) {
        if (len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(dest, src, len);
        }
        dest[len] = '\0';
    }
    return dest;
}

char *second_most_frequent(const char strings[][MAX_LENGTH], int n) {
    if (n <= 0 || n > MAX_STRINGS) return NULL;

    StringCount *counts = malloc((size_t)n * sizeof(StringCount));
    if (!counts) return NULL;

    int unique_count = 0;

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < unique_count; j++) {
            if (strncmp(counts[j].str, strings[i], MAX_LENGTH - 1) == 0) {
                counts[j].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            size_t len = strnlen(strings[i], MAX_LENGTH);
            if (len >= MAX_LENGTH) len = MAX_LENGTH - 1;
            if (len > 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(counts[unique_count].str, strings[i], len);
            }
            counts[unique_count].str[len] = '\0';
            counts[unique_count].count = 1;
            unique_count++;
            if (unique_count >= n) break;
        }
    }

    if (unique_count < 2) {
        free(counts);
        return NULL;
    }

    int max_count = 0;
    int second_max_count = -1;
    int max_index = 0;
    int second_max_index = -1;

    for (int i = 0; i < unique_count; i++) {
        if (counts[i].count > max_count) {
            second_max_count = max_count;
            second_max_index = max_index;
            max_count = counts[i].count;
            max_index = i;
        } else if (counts[i].count < max_count) {
            if (second_max_count == -1 || counts[i].count > second_max_count) {
                second_max_count = counts[i].count;
                second_max_index = i;
            }
        }
    }

    char *result = NULL;
    if (second_max_index != -1) {
        result = safe_strndup(counts[second_max_index].str, MAX_LENGTH);
    }

    free(counts);
    return result;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char strings[MAX_STRINGS][MAX_LENGTH];
    int n = 0;

    printf("Enter number of strings: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_STRINGS) {
        printf("Invalid input\n");
        return 1;
    }

    int c;
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = getchar()) != '\n' && c != EOF) {}

    printf("Enter %d strings:\n", n);
    for (int i = 0; i < n; i++) {
        if (fgets(strings[i], MAX_LENGTH, stdin)) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(strings[i]);
            if (len > 0 && strings[i][len - 1] == '\n') {
                strings[i][len - 1] = '\0';
            }
        } else {
            strings[i][0] = '\0';
        }
    }

    char *result = second_most_frequent(strings, n);

    if (result) {
        printf("Second most frequent string: %s\n", result);
        free(result);
    } else {
        printf("No second most frequent string found\n");
    }

    return 0;
}