#include <stdio.h>
#include <string.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  'SIZE_MAX' is defined in header '<stdint.h>'; this is probably fixable by adding '#include <stdint.h>'
  */

char most_common_char(const char *str) {
    if (str == NULL) {
        return '\0';
    }

    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     *  use of undeclared identifier 'SIZE_MAX'
     *  'SIZE_MAX' undeclared (first use in this function)
     */
    size_t len = strnlen(str, SIZE_MAX);
    if (len == 0) {
        return '\0';
    }

    size_t count[UCHAR_MAX + 1] = {0};
    size_t max_count = 0;
    char result = '\0';

    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        count[c]++;
    }

    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (count[c] > max_count) {
            max_count = count[c];
            result = str[i];
        }
    }

    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char res = most_common_char(argv[1]);
    if (res == '\0') {
        fprintf(stderr, "Input string is empty or invalid.\n");
        return 1;
    }

    printf("%c\n", res);
    return 0;
}