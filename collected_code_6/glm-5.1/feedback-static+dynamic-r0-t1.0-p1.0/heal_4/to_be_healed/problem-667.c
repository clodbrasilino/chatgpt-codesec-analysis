#include <stdio.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  'SIZE_MAX' is defined in header '<stdint.h>'; this is probably fixable by adding '#include <stdint.h>'
  */

int count_vowels(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int count = 0;
    const char *p = str;
    while (*p != '\0') {
        char c = tolower((unsigned char)*p);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            count++;
        }
        p++;
    }

    return count;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    /* Possible weaknesses found:
     *  'SIZE_MAX' undeclared (first use in this function)
     *  use of undeclared identifier 'SIZE_MAX'
     *  each undeclared identifier is reported only once for each function it appears in
     */
    size_t len = strnlen(argv[1], SIZE_MAX);
    /* Possible weaknesses found:
     *  use of undeclared identifier 'SIZE_MAX'
     */
    if (len == SIZE_MAX) {
        fprintf(stderr, "Error: Input string is not null-terminated within bounds\n");
        return 1;
    }

    int vowels = count_vowels(argv[1]);
    printf("%d\n", vowels);

    return 0;
}