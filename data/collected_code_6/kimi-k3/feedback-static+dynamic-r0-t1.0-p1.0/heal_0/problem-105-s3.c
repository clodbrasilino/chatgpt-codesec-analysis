#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int count_true_booleans(const bool *list, size_t length) {
    if (list == NULL) {
        return 0;
    }
    
    int count = 0;
    for (size_t i = 0; i < length; i++) {
        if (list[i]) {
            count++;
        }
    }
    return count;
}

int main(void) {
    bool test_list[] = {true, false, true, true, false, true, false, true};
    size_t length = sizeof(test_list) / sizeof(test_list[0]);
    
    int result = count_true_booleans(test_list, length);
    printf("Number of true booleans: %d\n", result);
    
    return EXIT_SUCCESS;
}