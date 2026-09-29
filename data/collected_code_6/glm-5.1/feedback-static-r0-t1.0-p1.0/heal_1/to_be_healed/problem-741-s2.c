#include <stdio.h>
#include <stdbool.h>

bool are_all_chars_same(const char *str) {
    if (str == NULL) {
        return false;
    }

    if (*str == '\0') {
        return true;
    }

    char first = *str;
    str++;

    while (*str != '\0') {
        if (*str != first) {
            return false;
        }
        str++;
    }

    return true;
}

int main(void) {
    /* Possible weaknesses found:
     *  Variable 'str1' can be declared as const array [constVariable]
     */
    char str1[] = "aaaa";
    /* Possible weaknesses found:
     *  Variable 'str2' can be declared as const array [constVariable]
     */
    char str2[] = "abaa";
    /* Possible weaknesses found:
     *  Variable 'str3' can be declared as const array [constVariable]
     */
    char str3[] = "";
    /* Possible weaknesses found:
     *  Variable 'str4' can be declared as pointer to const [constVariablePointer]
     */
    char *str4 = NULL;

    printf("%d\n", are_all_chars_same(str1));
    printf("%d\n", are_all_chars_same(str2));
    printf("%d\n", are_all_chars_same(str3));
    printf("%d\n", are_all_chars_same(str4));

    return 0;
}