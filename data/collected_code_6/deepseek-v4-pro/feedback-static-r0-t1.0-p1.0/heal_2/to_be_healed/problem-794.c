#include <stdio.h>
#include <string.h>

int match_a_anything_b(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    if (str[0] != 'a') {
        return 0;
    }
    
    size_t len = strnlen(str, 2);
    if (len < 2 && str[0] == 'a') {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);
    if (len < 2) {
        return 0;
    }
    
    if (str[len - 1] != 'b') {
        return 0;
    }
    
    return 1;
}

int main(void) {
    const char *test1 = "a12345b";
    const char *test2 = "ab";
    const char *test3 = "a";
    const char *test4 = "b";
    const char *test5 = "12a34b";
    const char *test6 = "aXb";
    
    printf("%d\n", match_a_anything_b(test1));
    printf("%d\n", match_a_anything_b(test2));
    printf("%d\n", match_a_anything_b(test3));
    printf("%d\n", match_a_anything_b(test4));
    printf("%d\n", match_a_anything_b(test5));
    printf("%d\n", match_a_anything_b(test6));
    
    return 0;
}