#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CHARS 256

void find_most_common_characters(const char *text) {
    if (text == NULL) {
        return;
    }

    int counts[MAX_CHARS] = {0};
    int max_count = 0;

    for (size_t i = 0; text[i] != '\0'; i++) {
        unsigned char c = (unsigned char)text[i];
        counts[c]++;
        if (counts[c] > max_count) {
            max_count = counts[c];
        }
    }

    if (max_count == 0) {
        return;
    }

    printf("Most common element(s) with count %d:\n", max_count);
    for (int i = 0; i < MAX_CHARS; i++) {
        if (counts[i] == max_count) {
            if (isprint(i)) {
                printf("'%c'\n", i);
            } else {
                printf("0x%02X\n", i);
            }
        }
    }
}

int main(void) {
    const char *sample_text = "hello world! this is a test text.";
    find_most_common_characters(sample_text);
    return 0;
}