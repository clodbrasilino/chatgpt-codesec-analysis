#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#define MAX_ELEMENTS 5
#define MAX_LENGTH 12

void removeDigits(char *str, size_t length) {
    if (str == NULL)
        return;

    char *ptr = str;

    while (*str != '\0' && (ptr - str) < length) {
        if (!isdigit((unsigned char)*str)) {
            *ptr++ = *str;
        }
        str++;
    }
    *ptr = '\0';
}

/* Possible weaknesses found:
 *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
 */
void removeDigitsFromList(char (*list)[MAX_LENGTH], size_t size, size_t *lengths) {
    if (list == NULL || lengths == NULL)
        return;

    size = size > MAX_ELEMENTS ? MAX_ELEMENTS : size;

    for (size_t i = 0; i < size; i++) {
        lengths[i] = lengths[i] > MAX_LENGTH - 1 ? MAX_LENGTH - 1 : lengths[i];
        removeDigits(list[i], lengths[i]);
    }
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char list[MAX_ELEMENTS][MAX_LENGTH] = {"abc123", "def456", "ghi789", "jkl"};
    size_t size = sizeof(list) / sizeof(list[0]);
    size_t lengths[MAX_ELEMENTS] = {6, 6, 6, 3};

    removeDigitsFromList(list, size, lengths);

    for (size_t i = 0; i < size; i++) {
        printf("%s\n", list[i]);
    }
    return 0;
}