#include <stdbool.h>
#include <stddef.h>

size_t count_true(const bool *list, size_t length) {
    size_t count = 0;
    for (size_t i = 0; i < length; ++i) {
        if (list[i]) {
            ++count;
        }
    }
    return count;
}

int main(void) {
    bool test_list[] = {true, false, true, true, false, true};
    size_t length = sizeof(test_list) / sizeof(test_list[0]);
    size_t result = count_true(test_list, length);
    (void)result;
    return 0;
}