#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

bool contains_z(const char *word) {
    if (word == NULL) {
        return false;
    }
    const char *p = word;
    while (*p != '\0') {
        if (*p == 'z' || *p == 'Z') {
            return true;
        }
        p++;
    }
    return false;
}

int main(void) {
    const char *words[] = {
        "apple",
        "zalmon",
        "Zebra",
        "grape",
        "pizza",
        NULL
    };
    size_t i = 0;
    while (words[i] != NULL) {
        if (contains_z(words[i])) {
            printf("%s contains 'z'\n", words[i]);
        } else {
            printf("%s does not contain 'z'\n", words[i]);
        }
        i++;
    }
    return 0;
}