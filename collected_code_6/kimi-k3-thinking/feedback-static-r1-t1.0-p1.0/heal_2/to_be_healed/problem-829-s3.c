#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 4096

static size_t bounded_length(const char *str, size_t max_len)
{
    size_t len = 0;

    while (len < max_len && str[len] != '\0') {
        len++;
    }

    return len;
}

static char *copy_string(const char *src)
{
    size_t len;
    size_t dest_size;
    char *dest;

    if (src == NULL) {
        return NULL;
    }

    len = bounded_length(src, MAX_STRING_LENGTH);
    if (len >= MAX_STRING_LENGTH) {
        return NULL;
    }

    /* Possible weaknesses found:
     *  dest_size is assigned 'len+1' here.
     */
    dest_size = len + 1;
    dest = malloc(dest_size);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (dest == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     *  Condition 'len+1>dest_size' is always false
     *  Condition 'len+1>dest_size' is always false [knownConditionTrueFalse]
     */
    if (len + 1 > dest_size) {
        free(dest);
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dest, src, len + 1);
    dest[dest_size - 1] = '\0';

    return dest;
}

char *second_most_frequent(const char *sequence[], size_t count)
{
    const char **unique;
    size_t *frequencies;
    size_t unique_count = 0;
    size_t i;
    size_t j;
    char *result = NULL;

    if (sequence == NULL || count == 0) {
        return NULL;
    }

    unique = malloc(count * sizeof(*unique));
    if (unique == NULL) {
        return NULL;
    }

    frequencies = calloc(count, sizeof(*frequencies));
    if (frequencies == NULL) {
        free(unique);
        return NULL;
    }

    for (i = 0; i < count; i++) {
        int found = 0;

        if (sequence[i] == NULL) {
            continue;
        }

        for (j = 0; j < unique_count; j++) {
            if (strncmp(unique[j], sequence[i], MAX_STRING_LENGTH) == 0) {
                frequencies[j]++;
                found = 1;
                break;
            }
        }

        if (!found) {
            unique[unique_count] = sequence[i];
            frequencies[unique_count] = 1;
            unique_count++;
        }
    }

    if (unique_count >= 2) {
        size_t first_idx = 0;
        size_t second_idx = 0;
        int have_first = 0;
        int have_second = 0;

        for (i = 0; i < unique_count; i++) {
            if (!have_first || frequencies[i] > frequencies[first_idx]) {
                if (have_first) {
                    second_idx = first_idx;
                    have_second = 1;
                }
                first_idx = i;
                have_first = 1;
            } else if (frequencies[i] < frequencies[first_idx] &&
                       (!have_second || frequencies[i] > frequencies[second_idx])) {
                second_idx = i;
                have_second = 1;
            }
        }

        if (have_second) {
            result = copy_string(unique[second_idx]);
        }
    }

    free(unique);
    free(frequencies);

    return result;
}

int main(void)
{
    const char *sequence[] = {
        "apple", "banana", "apple", "cherry",
        "banana", "apple", "banana", "apple",
        "cherry"
    };
    size_t count = sizeof(sequence) / sizeof(sequence[0]);
    char *second = second_most_frequent(sequence, count);

    if (second != NULL) {
        printf("Second most frequent string: %s\n", second);
        free(second);
    } else {
        printf("No second most frequent string exists.\n");
    }

    return 0;
}