#include <stdio.h>
#include <string.h>

int count_std_occurrences(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    int count = 0;
    size_t len = strlen(str);
    
    for (size_t i = 0; i + 2 < len + 1; i++) {
        if (i + 2 >= len) {
            if (str[i] == 's' && str[i+1] == 't' && str[i+2] == 'd') {
                count++;
            }
        } else if (str[i] == 's' && str[i+1] == 't' && str[i+2] == 'd') {
            count++;
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