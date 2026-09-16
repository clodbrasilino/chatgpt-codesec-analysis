#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_length_even(const char *word) {
    if (word == NULL) {
        return false;
    }

    size_t len = strlen(word);

    if (len == 0) {
        return false;
    }

    return len % 2 == 0;
}

int main(void) {
    const char *test_word = "hello";
    
    if (is_length_even(test_word)) {
        printf("Even\n");
    } else {
        printf("Odd\n");
    }

    return 0;
}