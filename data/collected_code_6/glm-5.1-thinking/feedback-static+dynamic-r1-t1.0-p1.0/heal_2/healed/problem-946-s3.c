#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stddef.h>

typedef struct {
    char character;
    size_t count;
} CharCount;

int find_most_common_elements(const char *text, size_t text_len, CharCount *results, int max_results) {
    if (text == NULL || results == NULL || max_results <= 0) {
        return -1;
    }

    size_t freq[UCHAR_MAX + 1] = {0};

    for (size_t i = 0; i < text_len; i++) {
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
    const char text[] = "hello world";
    CharCount results[UCHAR_MAX + 1];
    size_t len = sizeof(text) - 1;
    int count = find_most_common_elements(text, len, results, UCHAR_MAX + 1);

    if (count < 0) {
        printf("Error\n");
        return 1;
    }

    for (int i = 0; i < count; i++) {
        printf("Character: '%c', Count: %zu\n", results[i].character, results[i].count);
    }

    return 0;
}