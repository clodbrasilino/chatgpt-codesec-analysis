#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int contains_all_vowels(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int a = 0, e = 0, i = 0, o = 0, u = 0;

    for (size_t idx = 0; str[idx] != '\0'; idx++) {
        switch (str[idx]) {
            case 'a': case 'A': a = 1; break;
            case 'e': case 'E': e = 1; break;
            case 'i': case 'I': i = 1; break;
            case 'o': case 'O': o = 1; break;
            case 'u': case 'U': u = 1; break;
            default: break;
        }

        if (a && e && i && o && u) {
            return 1;
        }
    }

    return a && e && i && o && u;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (contains_all_vowels(argv[1])) {
        printf("Accepted\n");
    } else {
        printf("Rejected\n");
    }

    return EXIT_SUCCESS;
}