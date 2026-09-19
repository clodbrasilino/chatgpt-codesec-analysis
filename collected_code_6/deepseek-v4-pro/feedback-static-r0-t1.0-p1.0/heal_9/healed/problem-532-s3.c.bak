#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

static int compare_chars(const void *a, const void *b) {
    unsigned char ca = *(const unsigned char *)a;
    unsigned char cb = *(const unsigned char *)b;
    return (ca > cb) - (ca < cb);
}

bool are_permutations(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return false;
    }
    
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    
    if (len1 != len2) {
        return false;
    }
    
    if (len1 == 0) {
        return true;
    }
    
    char *copy1 = malloc(len1 + 1);
    char *copy2 = malloc(len2 + 1);
    
    if (copy1 == NULL || copy2 == NULL) {
        free(copy1);
        free(copy2);
        return false;
    }
    
    strcpy(copy1, str1);
    strcpy(copy2, str2);
    
    qsort(copy1, len1, sizeof(char), compare_chars);
    qsort(copy2, len2, sizeof(char), compare_chars);
    
    bool result = (strcmp(copy1, copy2) == 0);
    
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
    bool result5 = are_permutations(test5_a, test5_b);
    printf("%s\n", result5 ? "true" : "false");
    
    return 0;
}