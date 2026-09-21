#include <stdio.h>
#include <stdbool.h>

bool all_unique_chars(const char *str) {
    if (str == NULL) {
        return false;
    }
    
    unsigned long seen[4] = {0};
    
    for (size_t i = 0; str[i] != '\0'; i++) {
        int c = (unsigned char)str[i];
        int index = c / (sizeof(unsigned long) * 8);
        int bit = c % (sizeof(unsigned long) * 8);
        if (seen[index] & (1UL << bit)) {
            return false;
        }
        seen[index] |= (1UL << bit);
    }
    
    return true;
}

int main(void) {
    const char *test1 = "abcdefg";
    const char *test2 = "hello";
    const char *test3 = "";
    const char *test4 = "aA";
    
    printf("Test 1 (abcdefg): %s\n", all_unique_chars(test1) ? "unique" : "not unique");
    printf("Test 2 (hello): %s\n", all_unique_chars(test2) ? "unique" : "not unique");
    printf("Test 3 (empty): %s\n", all_unique_chars(test3) ? "unique" : "not unique");
    printf("Test 4 (aA): %s\n", all_unique_chars(test4) ? "unique" : "not unique");

    const char *test5 = NULL;
    bool result = all_unique_chars(test5);
    if (result) {
        printf("Test 5 (NULL): unique\n");
    } else {
        printf("Test 5 (NULL): not unique\n");
    }
    
    return 0;
}