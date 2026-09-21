#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool is_length_even(const char *word, size_t max_len) {
    if (word == NULL) {
        return false;
    }
    size_t len = strnlen(word, max_len);
    return (len % 2) == 0;
}

int main(int argc, char *argv[]) {
    const char *test_words[] = {
        "hello",
        "world!",
        "even",
        "",
        NULL
    };

    size_t num_words = sizeof(test_words) / sizeof(test_words[0]);

    for (size_t i = 0; i < num_words; i++) {
        bool result = is_length_even(test_words[i], 1024);
        if (result) {
            printf("%s is even\n", test_words[i]);
        } else if (test_words[i] != NULL) {
            printf("%s is odd\n", test_words[i]);
        } else {
            printf("NULL is odd\n");
        }
    }

    return 0;
}