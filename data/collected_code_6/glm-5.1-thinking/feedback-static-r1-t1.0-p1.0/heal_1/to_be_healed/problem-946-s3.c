#include <stdio.h>
#include <string.h>
#include <limits.h>

typedef struct {
    char character;
    size_t count;
} CharCount;

int find_most_common_elements(const char *text, CharCount *results, int max_results) {
    if (text == NULL || results == NULL || max_results <= 0) {
        return -1;
    }

    size_t freq[UCHAR_MAX + 1] = {0};
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(text);

    for (size_t i = 0; i < len; i++) {
        freq[(unsigned char)text[i]]++;
    }

    size_t max_count = 0;
    for (int i = 0; i <= UCHAR_MAX; i++) {
        if (freq[i] > max_count) {
            max_count = freq[i];
        }
    }

    if (max_count == 0) {
        return 0;
    }

    int result_count = 0;
    for (int i = 0; i <= UCHAR_MAX; i++) {
        if (freq[i] == max_count) {
            if (result_count < max_results) {
                results[result_count].character = (char)i;
                results[result_count].count = max_count;
                result_count++;
            } else {
                break;
            }
        }
    }

    return result_count;
}

int main(void) {
    const char *text = "hello world";
    CharCount results[UCHAR_MAX + 1];

    int count = find_most_common_elements(text, results, UCHAR_MAX + 1);

    if (count < 0) {
        printf("Error\n");
        return 1;
    }

    for (int i = 0; i < count; i++) {
        printf("Character: '%c', Count: %zu\n", results[i].character, results[i].count);
    }

    return 0;
}