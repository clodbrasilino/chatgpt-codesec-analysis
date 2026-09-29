#include <stdio.h>
#include <string.h>

int count_std_occurrences(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    const char *target = "std";
    size_t target_len = 3;
    int count = 0;
    const char *current = str;
    
    while (*current != '\0') {
        if (strncmp(current, target, target_len) == 0) {
            count++;
            current += target_len;
        } else {
            current++;
        }
    }
    
    return count;
}

int main(void) {
    const char *test1 = "std test standard std";
    const char *test2 = "no occurrences here";
    const char *test3 = "std";
    const char *test4 = "";
    const char *test5 = NULL;
    
    printf("Test 1: %d\n", count_std_occurrences(test1));
    printf("Test 2: %d\n", count_std_occurrences(test2));
    printf("Test 3: %d\n", count_std_occurrences(test3));
    printf("Test 4: %d\n", count_std_occurrences(test4));
    printf("Test 5: %d\n", count_std_occurrences(test5));
    
    return 0;
}