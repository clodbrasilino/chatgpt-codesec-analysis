#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int min_rotations_same_string(const char *str) {
    if (str == NULL) return -1;
    
    size_t len = strlen(str);
    if (len == 0) return 0;
    
    char *doubled = (char *)malloc(2 * len + 1);
    if (doubled == NULL) return -1;
    
    strcpy(doubled, str);
    strcat(doubled, str);
    
    int result = -1;
    
    for (size_t i = 1; i <= len; i++) {
        if (strncmp(doubled + i, str, len) == 0) {
            result = (int)i;
            break;
        }
    }
    
    free(doubled);
    return result;
}

int main(void) {
    const char *test1 = "aaaa";
    const char *test2 = "abab";
    const char *test3 = "abcde";
    const char *test4 = "";
    const char *test5 = "a";
    
    printf("%d\n", min_rotations_same_string(test1));
    printf("%d\n", min_rotations_same_string(test2));
    printf("%d\n", min_rotations_same_string(test3));
    printf("%d\n", min_rotations_same_string(test4));
    printf("%d\n", min_rotations_same_string(test5));
    
    return 0;
}