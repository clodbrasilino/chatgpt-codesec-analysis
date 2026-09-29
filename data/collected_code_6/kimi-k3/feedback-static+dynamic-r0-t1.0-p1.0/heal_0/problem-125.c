#include <stdio.h>
#include <string.h>
#include <limits.h>

int max_difference(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    int max_diff = INT_MIN;
    int current_diff = 0;
    size_t len = strlen(str);
    
    for (size_t i = 0; i < len; i++) {
        if (str[i] == '0') {
            current_diff++;
        } else if (str[i] == '1') {
            current_diff--;
        } else {
            return 0;
        }
        
        if (current_diff > max_diff) {
            max_diff = current_diff;
        }
        
        if (current_diff < 0) {
            current_diff = 0;
        }
    }
    
    return (max_diff == INT_MIN) ? 0 : max_diff;
}

int main(void) {
    const char *test1 = "11000010001";
    const char *test2 = "111111";
    const char *test3 = "0000";
    const char *test4 = "101";
    
    printf("Max difference in '%s': %d\n", test1, max_difference(test1));
    printf("Max difference in '%s': %d\n", test2, max_difference(test2));
    printf("Max difference in '%s': %d\n", test3, max_difference(test3));
    printf("Max difference in '%s': %d\n", test4, max_difference(test4));
    
    return 0;
}