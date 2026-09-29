#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool is_palindrome(const char *str, size_t max_len) {
    if (str == NULL) {
        return false;
    }
    
    size_t len = strnlen(str, max_len);
    if (len == 0) {
        return true;
    }
    
    size_t left = 0;
    size_t right = len - 1;
    
    while (left < right) {
        if (str[left] != str[right]) {
            return false;
        }
        left++;
        right--;
    }
    
    return true;
}

void find_palindromes(const char *strings[], size_t count, size_t max_len) {
    if (strings == NULL || count == 0) {
        printf("No strings provided.\n");
        return;
    }
    
    printf("Palindromes found:\n");
    bool found_any = false;
    
    for (size_t i = 0; i < count; i++) {
        if (strings[i] != NULL && is_palindrome(strings[i], max_len)) {
            printf("- %s\n", strings[i]);
            found_any = true;
        }
    }
    
    if (!found_any) {
        printf("No palindromes found.\n");
    }
}

int main(void) {
    const char *test_strings[] = {
        "racecar",
        "hello",
        "madam",
        "world",
        "level",
        "programming",
        "noon",
        "civic",
        "example"
    };
    
    size_t count = sizeof(test_strings) / sizeof(test_strings[0]);
    size_t max_len = 256;
    
    find_palindromes(test_strings, count, max_len);
    
    return 0;
}