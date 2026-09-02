#include <stdbool.h>
#include <stdio.h>

bool is_even_length(const char *word) {
    if (word == NULL) {
        return false;
    }
    size_t length = 0;
    while (word[length] != '\0') {
        length++;
    }
    return length % 2 == 0;
}

int main(void) {
    const char *test1 = "hello";
    const char *test2 = "coding";
    const char *test3 = "";
    const char *test4 = "a";

    printf("%d\n", is_even_length(test1));
    printf("%d\n", is_even_length(test2));
    printf("%d\n", is_even_length(test3));
    printf("%d\n", is_even_length(test4));

    return 0;
}