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
    int i;

    for (i = 0; text[i] != '\0'; i++) {
        unsigned char c = (unsigned char)text[i];
        counts[c]++;
        if (counts[c] > max_count) {
            max_count = counts[c];
        }
    }

    if (max_count == 0) {
        *result_count = 0;
        *result = NULL;
        return;
    }

    int count_max_elements = 0;
    for (i = 0; i < MAX_CHARS; i++) {
        if (counts[i] == max_count) {
            count_max_elements++;
        }
    }

    *result = (CharCount *)malloc(count_max_elements * sizeof(CharCount));
    if (*result == NULL) {
        *result_count = 0;
        return;
    }

    *result_count = count_max_elements;
    int index = 0;
    for (i = 0; i < MAX_CHARS; i++) {
        if (counts[i] == max_count) {
            (*result)[index].character = (char)i;
            (*result)[index].count = max_count;
            index++;
        }
    }
}

int main(void) {
    const char *text = "hello world, this is a test string to find the most common elements.";
    CharCount *result = NULL;
    int result_count = 0;

    find_most_common_elements(text, &result, &result_count);

    if (result != NULL && result_count > 0) {
        printf("Most common element(s) (count: %d):\n", result[0].count);
        for (int i = 0; i < result_count; i++) {
            if (isprint((unsigned char)result[i].character)) {
                printf("'%c'\n", result[i].character);
            } else {
                printf("0x%02X\n", (unsigned char)result[i].character);
            }
        }
        free(result);
        result = NULL;
    } else {
        printf("No elements found or memory allocation failed.\n");
    }

    return 0;
}