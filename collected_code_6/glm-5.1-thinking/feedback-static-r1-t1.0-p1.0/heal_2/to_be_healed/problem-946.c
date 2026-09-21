#include <stdio.h>
#include <string.h>
#include <ctype.h>

void find_most_common(const char *text, size_t len) {
    if (text == NULL || len == 0) {
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
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    find_most_common(sample, strlen(sample));
    find_most_common(NULL, 0);
    find_most_common("", 0);
    return 0;
}