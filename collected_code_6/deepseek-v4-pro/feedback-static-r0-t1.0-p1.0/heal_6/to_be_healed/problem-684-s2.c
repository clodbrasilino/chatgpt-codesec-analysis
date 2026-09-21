#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/* Possible weaknesses found:
 *  'LONG_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
 */
#include <stdint.h>

long count_occurrences(const char *str, char ch, long n) {
    if (str == NULL || n <= 0) {
        return 0;
    }

    size_t len = strnlen(str, 255);
    if (len == 0) {
        return 0;
    }

    if (n > INT64_MAX / 256) {
        return -1;
    }

    long full_repeats = n / (long)len;
    size_t remainder = n % (long)len;
    long count = 0;

    for (size_t i = 0; i < len; i++) {
        if (str[i] == ch) {
            count++;
        }
    }

    /* Possible weaknesses found:
     *  use of undeclared identifier 'LONG_MAX'
     *  each undeclared identifier is reported only once for each function it appears in
     *  'LONG_MAX' undeclared (first use in this function)
     */
    if (count > 0 && full_repeats > LONG_MAX / count) {
        return -1;
    }

    long total = count * full_repeats;

    for (size_t i = 0; i < remainder; i++) {
        if (str[i] == ch) {
            /* Possible weaknesses found:
             *  use of undeclared identifier 'LONG_MAX'
             */
            if (total == LONG_MAX) {
                return -1;
            }
            total++;
        }
    }

    return total;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[320];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[256];
    char ch;
    long n;
    /* Possible weaknesses found:
     *  The scope of the variable 'c' can be reduced. [variableScope]
     */
    int c;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }

    size_t len = strnlen(input, sizeof(input));
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    } else {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
    }

    if (len >= sizeof(input) - 1) {
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder sscanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    int matches = sscanf(input, "%255s %c %ld", word, &ch, &n);
    if (matches != 3) {
        return 1;
    }

    if (n <= 0 || n > 1000000000L) {
        return 1;
    }

    size_t word_len = strnlen(word, sizeof(word));
    if (word_len >= sizeof(word)) {
        return 1;
    }

    long result = count_occurrences(word, ch, n);
    if (result < 0) {
        return 1;
    }

    printf("%ld\n", result);

    return 0;
}