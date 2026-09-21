#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 6, got <no output>
  *  test case 0 failed: expected 6, got <no output>
  *  test case 2 failed: expected 12, got <no output>
  */

int count_substrings(const char *s, size_t len) {
    if (s == NULL) {
        return 0;
    }

    int count = 0;

    for (size_t i = 0; i < len; i++) {
        if (!isdigit((unsigned char)s[i])) {
            continue;
        }
        int sum = 0;
        for (size_t j = i; j < len; j++) {
            if (!isdigit((unsigned char)s[j])) {
                break;
            }
            sum += s[j] - '0';
            if (sum == (int)(j - i + 1)) {
                count++;
            } else if (sum > (int)(j - i + 1)) {
                break;
            }
        }
    }
    return count;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(argv[1]);
    int result = count_substrings(argv[1], len);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}