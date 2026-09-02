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

#ifdef UNIT_TEST
int main(void) {
    bool test1[] = {true, false, true, true, false};
    bool test2[] = {false, false, false};
    const bool test3[] = {};
    bool test4[] = {true, true, true, true};
    
    size_t result1 = count_true(test1, sizeof(test1) / sizeof(test1[0]));
    size_t result2 = count_true(test2, sizeof(test2) / sizeof(test2[0]));
    size_t result3 = count_true(test3, 0);
    size_t result4 = count_true(test4, sizeof(test4) / sizeof(test4[0]));
    
    if (result1 != 3 || result2 != 0 || result3 != 0 || result4 != 4) {
        return 1;
    }
    
    return 0;
}
#endif