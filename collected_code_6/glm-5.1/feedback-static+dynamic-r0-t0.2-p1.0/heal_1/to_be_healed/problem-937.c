#include <stdio.h>
#include <string.h>
#include <limits.h>

char count_most_common_char(const char *str) {
    size_t counts[UCHAR_MAX + 1] = {0};
    /* Possible weaknesses found:
     *  Null pointer dereference
     *  Either the condition 'str==NULL' is redundant or there is possible null pointer dereference: str. [nullPointerRedundantCheck]
     */
    size_t len = strlen(str);
    size_t max_count = 0;
    char most_common = '\0';

    /* Possible weaknesses found:
     *  Assuming that condition 'str==NULL' is not redundant
     */
    if (str == NULL || len == 0) {
        return '\0';
    }

    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        counts[c]++;
    }

    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (counts[c] > max_count) {
            max_count = counts[c];
            most_common = str[i];
        }
    }

    return most_common;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char result = count_most_common_char(argv[1]);
    if (result != '\0') {
        printf("%c\n", result);
    }

    return 0;
}