#include <stddef.h>
#include <stdio.h>
#include <string.h>

const char *most_frequent_word(const char *strings[], size_t count) {
    if (strings == NULL || count == 0) {
        return NULL;
    }

    const char *result = NULL;
    size_t max_count = 0;

    for (size_t i = 0; i < count; i++) {
        const char *candidate = strings[i];
        if (candidate == NULL) {
            continue;
        }

        size_t current_count = 0;
        for (size_t j = 0; j < count; j++) {
            const char *target = strings[j];
            if (target != NULL && strcmp(candidate, target) == 0) {
                current_count++;
            }
        }

        if (current_count > max_count) {
            max_count = current_count;
            result = candidate;
        }
    }

    return result;
}

int main(void) {
    const char *words[] = {
        "apple", "banana", "apple", "cherry", "banana", "apple"
    };
    size_t count = sizeof(words) / sizeof(words[0]);
    const char *most = most_frequent_word(words, count);

    if (most != NULL) {
        printf("%s\n", most);
    }

    return 0;
}