#include <stdio.h>
#include <string.h>

const char *find_last_occurrence(const char *str, int c) {
    if (str == NULL) {
        return NULL;
    }

    const char *ptr = NULL;
    const char *iter = str;

    while (*iter != '\0') {
        if (*iter == c) {
            ptr = iter;
        }
        iter++;
    }

    if (c == '\0') {
        return iter;
    }

    return ptr;
}

int main(void) {
    const char *text = "hello world";
    char target = 'o';

    const char *result = find_last_occurrence(text, target);

    if (result != NULL) {
        printf("Last occurrence of '%c' found at position: %td\n", target, result - text);
    } else {
        printf("Character '%c' not found.\n", target);
    }

    return 0;
}