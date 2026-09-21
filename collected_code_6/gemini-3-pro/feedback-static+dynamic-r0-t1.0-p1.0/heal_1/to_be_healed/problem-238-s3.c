#include <stdio.h>
#include <string.h>

unsigned long long count_substrings(const char *str);

unsigned long long count_substrings(const char *str) {
    size_t len;
    
    if (str == NULL) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);
    
    return (unsigned long long)len * (len + 1) / 2;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    int i;
    unsigned long long result;

    if (argc < 2) {
        return 1;
    }

    for (i = 1; i < argc; i++) {
        if (argv[i] != NULL) {
            result = count_substrings(argv[i]);
            printf("%llu\n", result);
        }
    }

    return 0;
}