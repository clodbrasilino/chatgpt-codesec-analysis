#include <stdio.h>
#include <string.h>

int match_pattern(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    size_t len = strlen(str);
    size_t i = 0;
    
    while (i < len) {
        if (str[i] == 'a') {
            size_t b_count = 0;
            size_t j = i + 1;
            
            while (j < len && str[j] == 'b') {
                b_count++;
                j++;
            }
            
            if (b_count >= 2 && b_count <= 3) {
                return 1;
            }
        }
        i++;
    }
    
    return 0;
}

int main(void) {
    const char *test1 = "abb";
    const char *test2 = "abbb";
    const char *test3 = "ab";
    const char *test4 = "abbbb";
    const char *test5 = "xyzabbxyz";
    
    printf("test1: %d\n", match_pattern(test1));
    printf("test2: %d\n", match_pattern(test2));
    printf("test3: %d\n", match_pattern(test3));
    printf("test4: %d\n", match_pattern(test4));
    printf("test5: %d\n", match_pattern(test5));
    
    return 0;
}