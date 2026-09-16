#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

bool contains_z(const char *word) {
    if (word == NULL) {
        return false;
    }
    
    while (*word != '\0') {
        if (tolower((unsigned char)*word) == 'z') {
            return true;
        }
        word++;
    }
    return false;
}

int main(void) {
    const char *test_words[] = {
        "zebra",
        "amazing",
        "hello",
        "Zoo",
        "",
        "pizza",
        NULL
    };
    
    for (int i = 0; test_words[i] != NULL; i++) {
        if (contains_z(test_words[i])) {
            printf("\"%s\" contains 'z'\n", test_words[i]);
        } else {
            printf("\"%s\" does not contain 'z'\n", test_words[i]);
        }
    }
    
    return 0;
}