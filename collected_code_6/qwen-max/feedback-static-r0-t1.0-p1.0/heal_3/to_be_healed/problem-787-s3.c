#include <stdio.h>
#include <string.h>

int match_string(const char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     *  Array 'str[2]' accessed at index 2, which is out of bounds. [arrayIndexOutOfBounds]
     *  Array 'str[2]' accessed at index 3, which is out of bounds. [arrayIndexOutOfBounds]
     */
    if (str == NULL || strlen(str) < 4 || str[3] != 'b' || str[2] != 'b' || str[1] != 'b' || str[0] != 'a') return 0;
    return 1;
}

int main() {
    const char *test1 = "abbb";
    const char *test2 = "abc";
    const char *test3 = "abbbc";
    const char *test4 = "a";

    printf("%s: %s\n", test1, match_string(test1) ? "Match" : "No Match");
    printf("%s: %s\n", test2, match_string(test2) ? "Match" : "No Match");
    printf("%s: %s\n", test3, match_string(test3) ? "Match" : "No Match");
    printf("%s: %s\n", test4, match_string(test4) ? "Match" : "No Match");

    return 0;
}