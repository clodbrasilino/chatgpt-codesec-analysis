#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int count_substrings(const char *s) {
    if (s == NULL) {
        return 0;
    }

    size_t len = strlen(s);
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

int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int result = count_substrings(argv[1]);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}