#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

static int compare_chars(const void *a, const void *b) {
    return (*(const unsigned char *)a - *(const unsigned char *)b);
}

bool are_permutations(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return false;
    }
    
    size_t len1 = strnlen(str1, SIZE_MAX);
    size_t len2 = strnlen(str2, SIZE_MAX);
    
    if (len1 != len2) {
        return false;
    }
    
    if (len1 == 0) {
        return true;
    }
    
    if (len1 > SIZE_MAX - 1) {
        return false;
    }
    
    size_t size = len1 + 1;
    char *copy1 = malloc(size);
    char *copy2 = malloc(size);
    
    if (copy1 == NULL || copy2 == NULL) {
        free(copy1);
        free(copy2);
        return false;
    }
    
    if (len1 >= size) {
        free(copy1);
        free(copy2);
        return false;
    }
    
    memcpy(copy1, str1, len1 + 1);
    memcpy(copy2, str2, len1 + 1);
    
    copy1[len1] = '\0';
    copy2[len1] = '\0';
    
    qsort(copy1, len1, sizeof(char), compare_chars);
    qsort(copy2, len2, sizeof(char), compare_chars);
    
    bool result = (memcmp(copy1, copy2, len1) == 0);
    
    memset(copy1, 0, size);
    memset(copy2, 0, size);
    
    free(copy1);
    free(copy2);
    
    return result;
}

int main(void) {
    const char *test1_a = "listen";
    const char *test1_b = "silent";
    printf("%s\n", are_permutations(test1_a, test1_b) ? "true" : "false");
    
    const char *test2_a = "hello";
    const char *test2_b = "world";
    printf("%s\n", are_permutations(test2_a, test2_b) ? "true" : "false");
    
    const char *test3_a = "abc";
    const char *test3_b = "abcd";
    printf("%s\n", are_permutations(test3_a, test3_b) ? "true" : "false");
    
    const char *test4_a = "";
    const char *test4_b = "";
    printf("%s\n", are_permutations(test4_a, test4_b) ? "true" : "false");
    
    const char *test5_a = NULL;
    const char *test5_b = "abc";
    bool result = are_permutations(test5_a, test5_b);
    printf("%s\n", result ? "true" : "false");
    
    return 0;
}