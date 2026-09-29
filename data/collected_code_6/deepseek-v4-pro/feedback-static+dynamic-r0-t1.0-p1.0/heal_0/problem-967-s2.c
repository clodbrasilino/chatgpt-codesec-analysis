#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

bool contains_all_vowels(const char *str) {
    if (str == NULL) {
        return false;
    }

    bool has_a = false, has_e = false, has_i = false, has_o = false, has_u = false;

    for (const char *p = str; *p != '\0'; ++p) {
        char c = tolower((unsigned char)*p);
        switch (c) {
            case 'a': has_a = true; break;
            case 'e': has_e = true; break;
            case 'i': has_i = true; break;
            case 'o': has_o = true; break;
            case 'u': has_u = true; break;
            default: break;
        }
    }

    return has_a && has_e && has_i && has_o && has_u;
}

int main(void) {
    const char *test1 = "The quick brown fox jumps over the lazy dog";
    const char *test2 = "Hello World";
    const char *test3 = "AEIOUaeiou";

    printf("Test 1: %s\n", contains_all_vowels(test1) ? "true" : "false");
    printf("Test 2: %s\n", contains_all_vowels(test2) ? "true" : "false");
    printf("Test 3: %s\n", contains_all_vowels(test3) ? "true" : "false");

    return 0;
}