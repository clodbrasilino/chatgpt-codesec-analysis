#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_substring_in_list(const char **list, size_t size, const char *substr, size_t substr_len) {
    if (list == NULL || substr == NULL) {
        return 0;
    }

    if (substr[0] == '\0') {
        return 1;
    }

    for (size_t i = 0; i < size; i++) {
        if (list[i] != NULL) {
            if (strstr(list[i], substr) != NULL) {
                return 1;
            }
        }
    }

    return 0;
}

int main(void) {
    const char *string_list[] = {
        "apple",
        "banana",
        "cherry",
        "date",
        NULL
    };

    size_t list_size = sizeof(string_list) / sizeof(string_list[0]) - 1;

    const char *search1 = "nan";
    const char *search2 = "berry";
    const char *search3 = "";
    const char *search4 = NULL;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int result1 = check_substring_in_list(string_list, list_size, search1, strlen(search1));
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int result2 = check_substring_in_list(string_list, list_size, search2, strlen(search2));
    int result3 = check_substring_in_list(string_list, list_size, search3, 0);
    int result4 = check_substring_in_list(string_list, list_size, search4, 0);

    printf("Search '%s': %d\n", search1, result1);
    printf("Search '%s': %d\n", search2, result2);
    printf("Search '': %d\n", result3);
    printf("Search NULL: %d\n", result4);

    return 0;
}