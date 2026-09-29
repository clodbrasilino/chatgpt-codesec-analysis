#include <stdio.h>
#include <stdbool.h>

int count_true_booleans(const bool *list, size_t length) {
    int count = 0;
    for (size_t i = 0; i < length; ++i) {
        if (list[i]) {
            ++count;
        }
    }
    return count;
}

int main(void) {
    bool list[] = {true, false, true, true, false};
    size_t length = sizeof(list) / sizeof(list[0]);
    int result = count_true_booleans(list, length);
    printf("Number of true values: %d\n", result);
    return 0;
}