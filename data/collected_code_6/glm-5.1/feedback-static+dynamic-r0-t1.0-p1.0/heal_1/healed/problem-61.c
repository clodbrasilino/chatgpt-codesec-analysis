#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int count_substrings(const char *s, size_t len) {
    if (s == NULL) {
        return 0;
    }

    int count = 0;

    for (size_t i = 0; i < len; i++) {
        int sum = 0;
        for (size_t j = i; j < len; j++) {
            if (!isdigit((unsigned char)s[j])) {
                break;
            }
            sum += s[j] - '0';
            if (sum == (int)(j - i + 1)) {
                count++;
            } else if (sum > (int)(j - i + 1)) {
                while (j + 1 < len && isdigit((unsigned char)s[j + 1])) {
                    j++;
                    sum += s[j] - '0';
                    if (sum == (int)(j - i + 1)) {
                        count++;
                    }
                }
                break;
            }
        }
    }
    return count;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t len = strnlen(argv[1], SIZE_MAX);
    int result = count_substrings(argv[1], len);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}