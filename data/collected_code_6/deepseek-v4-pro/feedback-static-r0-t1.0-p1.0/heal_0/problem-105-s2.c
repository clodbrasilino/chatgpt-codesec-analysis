#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

size_t count_true(const bool *list, size_t length) {
    size_t count = 0;
    for (size_t i = 0; i < length; i++) {
        if (list[i]) {
            count++;
        }
    }
    return count;
}

int main(void) {
    bool list[] = {true, false, true, true, false};
    size_t length = sizeof(list) / sizeof(list[0]);
    size_t true_count = count_true(list, length);
    
    printf("Number of true booleans: %zu\n", true_count);
    
    return 0;
}