#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_substring_in_list(const char *substring, const char **string_list, size_t list_size) {
    if (substring == NULL || string_list == NULL) {
        return false;
    }

    for (size_t i = 0; i < list_size; ++i) {
        if (string_list[i] != NULL) {
            if (strstr(string_list[i], substring) != NULL) {
                return true;
            }
        }
    }

    return false;
}

int main(void) {
    const char *strings[] = {
        "apple",
        "banana",
        "cherry",
        "date",
        "elderberry"
    };
    size_t num_strings = sizeof(strings) / sizeof(strings[0]);

    const char *target1 = "nan";
    const char *target2 = "fig";

    if (is_substring_in_list(target1, strings, num_strings)) {
        printf("'%s' found in the list.\n", target1);
    } else {
        printf("'%s' not found in the list.\n", target1);
    }

    if (is_substring_in_list(target2, strings, num_strings)) {
        printf("'%s' found in the list.\n", target2);
    } else {
        printf("'%s' not found in the list.\n", target2);
    }

    return 0;
}