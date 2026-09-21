#include <stdio.h>
#include <stdbool.h>

bool is_length_even(const char *word, size_t max_len) {
    if (word == NULL) {
        return false;
    }
    size_t len = 0;
    while (len < max_len && word[len] != '\0') {
        len++;
    }
    if (len == max_len && word[len] != '\0') {
        return false;
    }
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
    
    for (int i = 0; i < 4; i++) {
        bool result = is_length_even(test_words[i], 1024);
        if (result) {
            printf("%s is even\n", test_words[i]);
        } else {
            printf("%s is odd\n", test_words[i]);
        }
    }

    if (is_length_even(NULL, 0)) {
        printf("NULL is even\n");
    } else {
        printf("NULL is odd\n");
    }

    return 0;
}