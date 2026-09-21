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

    /* Possible weaknesses found:
     *  Assignment 'search1="nan"', assigned value is "nan"
     */
    const char *search1 = "nan";
    /* Possible weaknesses found:
     *  Assignment 'search2="berry"', assigned value is "berry"
     */
    const char *search2 = "berry";
    const char *search3 = "";
    const char *search4 = NULL;

    size_t len1 = 0;
    /* Possible weaknesses found:
     *  Condition 'search1!=NULL' is always true
     *  Condition 'search1!=NULL' is always true [knownConditionTrueFalse]
     */
    if (search1 != NULL) {
        len1 = strnlen(search1, 1024);
    }

    size_t len2 = 0;
    /* Possible weaknesses found:
     *  Condition 'search2!=NULL' is always true
     *  Condition 'search2!=NULL' is always true [knownConditionTrueFalse]
     */
    if (search2 != NULL) {
        len2 = strnlen(search2, 1024);
    }

    int result1 = check_substring_in_list(string_list, list_size, search1, len1);
    int result2 = check_substring_in_list(string_list, list_size, search2, len2);
    int result3 = check_substring_in_list(string_list, list_size, search3, 0);
    int result4 = check_substring_in_list(string_list, list_size, search4, 0);

    printf("Search '%s': %d\n", search1, result1);
    printf("Search '%s': %d\n", search2, result2);
    printf("Search '': %d\n", result3);
    printf("Search NULL: %d\n", result4);

    return 0;
}