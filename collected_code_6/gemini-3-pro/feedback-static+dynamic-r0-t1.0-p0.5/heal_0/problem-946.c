#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CHARS 256

typedef struct {
    char character;
    int count;
} CharCount;

void find_most_common_elements(const char *text, CharCount **result, int *result_count) {
    if (text == NULL || result == NULL || result_count == NULL) {
        return;
    }

    int counts[MAX_CHARS] = {0};
    int max_count = 0;
    int unique_max_chars = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        unsigned char c = (unsigned char)text[i];
        counts[c]++;
        if (counts[c] > max_count) {
            max_count = counts[c];
        }
    }

    if (max_count == 0) {
        *result = NULL;
        *result_count = 0;
        return;
    }

    for (int i = 0; i < MAX_CHARS; i++) {
        if (counts[i] == max_count) {
            unique_max_chars++;
        }
    }

    *result = (CharCount *)malloc(unique_max_chars * sizeof(CharCount));
    if (*result == NULL) {
        *result_count = 0;
        return;
    }

    int index = 0;
    for (int i = 0; i < MAX_CHARS; i++) {
        if (counts[i] == max_count) {
            (*result)[index].character = (char)i;
            (*result)[index].count = max_count;
            index++;
        }
    }

    *result_count = unique_max_chars;
}

int main(void) {
    const char *text = "hello world, this is a test string to find the most common elements.";
    CharCount *most_common = NULL;
    int count = 0;

    find_most_common_elements(text, &most_common, &count);

    if (most_common != NULL && count > 0) {
        printf("Most common element(s) with count %d:\n", most_common[0].count);
        for (int i = 0; i < count; i++) {
            if (isprint((unsigned char)most_common[i].character)) {
                printf("'%c'\n", most_common[i].character);
            } else {
                printf("'\\x%02x'\n", (unsigned char)most_common[i].character);
            }
        }
        free(most_common);
    } else {
        printf("No elements found or memory allocation failed.\n");
    }

    return 0;
}