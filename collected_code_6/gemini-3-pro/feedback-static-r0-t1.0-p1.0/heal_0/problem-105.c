#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

size_t count_true_booleans(const bool *list, size_t length) {
    size_t count = 0;
    
    if (list == NULL) {
        return 0;
    }
    
    for (size_t i = 0; i < length; i++) {
        if (list[i]) {
            count++;
        }
    }
    
    return count;
}

int main(void) {
    bool bool_list[] = {true, false, true, true, false, true};
    size_t length = sizeof(bool_list) / sizeof(bool_list[0]);
    
    size_t true_count = count_true_booleans(bool_list, length);
    
    printf("Number of true booleans: %zu\n", true_count);
    
    return 0;
}