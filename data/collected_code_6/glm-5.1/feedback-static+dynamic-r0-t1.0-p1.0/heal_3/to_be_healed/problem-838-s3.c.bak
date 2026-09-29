#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 0, got <no output>
  *  test case 1 failed: expected 2, got <no output>
  *  test case 0 failed: expected 1, got <no output>
  */

int min_swaps(const char *s1, const char *s2) {
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);

    if (len1 != len2) {
        return -1;
    }

    size_t len = len1;
    size_t xy = 0;
    size_t yx = 0;

    for (size_t i = 0; i < len; i++) {
        if (s1[i] != s2[i]) {
            if (s1[i] == '0') {
                xy++;
            } else {
                yx++;
            }
        }
    }

    if ((xy + yx) % 2 != 0) {
        return -1;
    }

    return (xy / 2) + (yx / 2) + (xy % 2) + (yx % 2);
}

int main(void) {
    char s1[1024];
    char s2[1024];

    while (scanf("%1023s %1023s", s1, s2) == 2) {
        int result = min_swaps(s1, s2);
        printf("%d\n", result);
        fflush(stdout);
    }

    return 0;
}