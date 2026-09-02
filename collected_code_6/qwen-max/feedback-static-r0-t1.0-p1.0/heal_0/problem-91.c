#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_substring_in_list(const char *sub, const char *list[], int list_size) {
    for (int i = 0; i < list_size; ++i) {
        if (strstr(list[i], sub) != NULL) {
            return true;
        }
    }
    return false;
}

int main() {
    const char *test_strings[] = {
        "apple", "banana", "cherry", "date", "elderberry"
    };
    int num_strings = sizeof(test_strings) / sizeof(test_strings[0]);
    const char *substring1 = "ban";
    const char *substring2 = "xyz";

    bool result1 = is_substring_in_list(substring1, test_strings, num_strings);
    printf("Substring '%s' in list: %s\n", substring1, result1 ? "true" : "false");

    bool result2 = is_substring_in_list(substring2, test_strings, num_strings);
    printf("Substring '%s' in list: %s\n", substring2, result2 ? "true" : "false");

    return 0;
}