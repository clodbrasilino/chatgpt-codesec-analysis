#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_reverse(const char *str1, const char *str2) {
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    if (len1 != len2) {
        return 0;
    }

    for (size_t i = 0; i < len1; i++) {
        if (str1[i] != str2[len1 - 1 - i]) {
            return 0;
        }
    }

    return 1;
}

int count_reverse_pairs(const char **string_list, size_t list_size) {
    if (string_list == NULL || list_size == 0) {
        return 0;
    }

    int count = 0;

    for (size_t i = 0; i < list_size; i++) {
        if (string_list[i] == NULL) {
            continue;
        }
        for (size_t j = i + 1; j < list_size; j++) {
            if (string_list[j] == NULL) {
                continue;
            }
            if (is_reverse(string_list[i], string_list[j])) {
                count++;
            }
        }
    }

    return count;
}

int main(void) {
    const char *strings[] = {
        "hello",
        "world",
        "olleh",
        "dlrow",
        "test",
        "tset",
        "abc",
        "cba",
        NULL
    };

    size_t size = 0;
    while (strings[size] != NULL) {
        size++;
    }

    int pairs = count_reverse_pairs(strings, size);
    printf("Number of reverse pairs: %d\n", pairs);

    return 0;
}