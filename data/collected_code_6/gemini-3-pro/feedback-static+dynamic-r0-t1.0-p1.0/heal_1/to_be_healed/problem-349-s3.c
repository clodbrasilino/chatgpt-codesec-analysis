#include <stdio.h>
#include <stdbool.h>

bool is_binary_string(const char *str) {
    if (str == NULL) {
        return false;
    }

    if (*str == '\0') {
        return false;
    }

    while (*str != '\0') {
        if (*str != '0' && *str != '1') {
            return false;
        }
        str++;
    }

    return true;
}

int main(void) {
    const char *test1 = "101010";
    const char *test2 = "101a10";
    const char *test3 = "";
    const char *test4 = NULL;

    printf("%s\n", is_binary_string(test1) ? "true" : "false");
    printf("%s\n", is_binary_string(test2) ? "true" : "false");
    printf("%s\n", is_binary_string(test3) ? "true" : "false");
    /* Possible weaknesses found:
     *  Condition 'is_binary_string(test4)' is always false [knownConditionTrueFalse]
     *  Condition 'is_binary_string(test4)' is always false
     *  Calling function 'is_binary_string' returns 0
     */
    printf("%s\n", is_binary_string(test4) ? "true" : "false");

    return 0;
}