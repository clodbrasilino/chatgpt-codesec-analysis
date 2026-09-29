#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int roman_to_int(const char *s) {
    if (s == NULL) {
        return 0;
    }

    size_t len = strlen(s);
    if (len == 0) {
        return 0;
    }

    int result = 0;

    for (size_t i = 0; i < len; i++) {
        int current = 0;
        switch (s[i]) {
            case 'I': current = 1; break;
            case 'V': current = 5; break;
            case 'X': current = 10; break;
            case 'L': current = 50; break;
            case 'C': current = 100; break;
            case 'D': current = 500; break;
            case 'M': current = 1000; break;
            default: return 0;
        }

        if (i + 1 < len) {
            int next = 0;
            switch (s[i + 1]) {
                case 'I': next = 1; break;
                case 'V': next = 5; break;
                case 'X': next = 10; break;
                case 'L': next = 50; break;
                case 'C': next = 100; break;
                case 'D': next = 500; break;
                case 'M': next = 1000; break;
                default: return 0;
            }

            if (current < next) {
                result -= current;
            } else {
                result += current;
            }
        } else {
            result += current;
        }
    }

    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <roman_numeral>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int val = roman_to_int(argv[1]);
    printf("%d\n", val);

    return EXIT_SUCCESS;
}