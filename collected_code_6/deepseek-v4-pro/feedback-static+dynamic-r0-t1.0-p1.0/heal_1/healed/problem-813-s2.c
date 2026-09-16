#include <stdio.h>
#include <string.h>

size_t string_length(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    size_t length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

int main(void) {
    const char *test_strings[] = {
        "Hello, World!",
        "",
        "C Programming",
        "A",
        NULL
    };
    
    for (int i = 0; test_strings[i] != NULL; i++) {
        size_t length = string_length(test_strings[i]);
        printf("String: \"%s\" | Length: %zu\n", test_strings[i], length);
    }
    
    printf("NULL string length: %zu\n", string_length(NULL));
    
    return 0;
}