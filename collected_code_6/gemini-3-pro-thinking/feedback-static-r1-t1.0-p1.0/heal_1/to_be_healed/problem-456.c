#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_string(char *str);
int reverse_strings_in_list(char **list, size_t count);
char *duplicate_string(const char *src);

void reverse_string(char *str) {
    if (str == NULL) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len <= 1) {
        return;
    }

    char *start = str;
    char *end = str + len - 1;

    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

int reverse_strings_in_list(char **list, size_t count) {
    if (list == NULL) {
        return -1;
    }

    for (size_t i = 0; i < count; i++) {
        if (list[i] != NULL) {
            reverse_string(list[i]);
        }
    }

    return 0;
}

char *duplicate_string(const char *src) {
    if (src == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(src);
    char *dest = (char *)malloc(len + 1);
    if (dest != NULL) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dest, src, len + 1);
    }
    
    return dest;
}

int main(void) {
    const char *initial_strings[] = {
        "Hello",
        "World",
        "C Programming",
        "OpenAI"
    };
    
    size_t count = sizeof(initial_strings) / sizeof(initial_strings[0]);

    char **mutable_list = (char **)malloc(count * sizeof(char *));
    if (mutable_list == NULL) {
        return 1;
    }

    for (size_t i = 0; i < count; i++) {
        mutable_list[i] = duplicate_string(initial_strings[i]);
        if (mutable_list[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(mutable_list[j]);
            }
            free(mutable_list);
            return 1;
        }
    }

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", mutable_list[i]);
    }

    if (reverse_strings_in_list(mutable_list, count) != 0) {
        for (size_t i = 0; i < count; i++) {
            free(mutable_list[i]);
        }
        free(mutable_list);
        return 1;
    }

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", mutable_list[i]);
    }

    for (size_t i = 0; i < count; i++) {
        free(mutable_list[i]);
    }
    free(mutable_list);

    return 0;
}