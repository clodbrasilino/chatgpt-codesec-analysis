#include <stdio.h>
#include <string.h>
#include <ctype.h>

void find_most_common(const char *text, size_t len) {
    if (text == NULL) {
        return;
    }

    if (len == 0) {
        return;
    }

    int counts[256] = {0};
    for (size_t i = 0; i < len; i++) {
        counts[(unsigned char)text[i]]++;
    }

    int max_count = 0;
    for (size_t i = 0; i < 256; i++) {
        if (counts[i] > max_count) {
            max_count = counts[i];
        }
    }

    if (max_count == 0) {
        return;
    }

    printf("Count: %d, Elements: ", max_count);
    for (size_t i = 0; i < 256; i++) {
        if (counts[i] == max_count) {
            if (isprint((unsigned char)i)) {
                printf("'%c' ", (char)i);
            } else {
                printf("'0x%02X' ", (unsigned int)i);
            }
        }
    }
    printf("\n");
}

int main(void) {
    const char *sample = "hello world";
    find_most_common(sample, strlen(sample));
    find_most_common(NULL, 0);
    find_most_common("", 0);
    return 0;
}