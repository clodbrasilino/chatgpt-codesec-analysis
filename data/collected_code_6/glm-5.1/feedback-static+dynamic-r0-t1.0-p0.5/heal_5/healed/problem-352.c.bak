#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stddef.h>

bool are_characters_unique(const char *str) {
    if (str == NULL) {
        return false;
    }

    size_t len = strlen(str);
    if (len > 256) {
        return false;
    }

    bool char_set[256] = {false};

    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (char_set[c]) {
            return false;
        }
        char_set[c] = true;
    }

    return true;
}

int main(void) {
    const char *test1 = "abcdef";
    const char *test2 = "hello";
    const char *test3 = NULL;
    const char *test4 = "";
    const char *test_ptrs[] = {test1, test2, test3, test4};
    size_t num_tests = sizeof(test_ptrs) / sizeof(test_ptrs[0]);

    for (size_t i = 0; i < num_tests; i++) {
        const char *current = test_ptrs[i];
        bool unique = are_characters_unique(current);
        
        if (current == NULL) {
            if (unique) {
                printf("NULL string has all unique characters\n");
            } else {
                printf("NULL string does not have all unique characters\n");
            }
        } else {
            if (unique) {
                printf("\"%s\" has all unique characters\n", current);
            } else {
                printf("\"%s\" does not have all unique characters\n", current);
            }
        }
    }

    return 0;
}