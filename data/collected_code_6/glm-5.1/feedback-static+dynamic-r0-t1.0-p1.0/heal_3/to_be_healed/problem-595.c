#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'Not Possible', got -1
  *  test case 2 failed: expected 'Not Possible', got -1
  */

int min_swaps(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL) {
        return -1;
    }

    size_t len1 = 0;
    while (s1[len1] != '\0') {
        len1++;
    }

    size_t len2 = 0;
    while (s2[len2] != '\0') {
        len2++;
    }

    if (len1 != len2 || len1 == 0) {
        return -1;
    }

    int c0 = 0;
    int c1 = 0;

    for (size_t i = 0; i < len1; i++) {
        if ((s1[i] != '0' && s1[i] != '1') || (s2[i] != '0' && s2[i] != '1')) {
            return -1;
        }
        if (s1[i] == '0' && s2[i] == '1') {
            c0++;
        } else if (s1[i] == '1' && s2[i] == '0') {
            c1++;
        }
    }

    if (c0 != c1) {
        return -1;
    }

    return c0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string1> <string2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *s1 = argv[1];
    const char *s2 = argv[2];

    int result = min_swaps(s1, s2);

    if (result == -1) {
        printf("Not Possible\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", result);

    return EXIT_SUCCESS;
}