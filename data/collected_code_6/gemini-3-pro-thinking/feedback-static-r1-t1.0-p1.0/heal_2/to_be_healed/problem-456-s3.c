#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 4096

void reverse_string(char *str);
void reverse_string_list(char **list, size_t count);
char *duplicate_string(const char *src);

void reverse_string(char *str) {
    if (str == NULL) {
        return;
    }
    
    size_t len = 0;
    /* Possible weaknesses found:
     *  Array index 'len' is used before limits check. [arrayIndexThenCheck]
     */
    while (str[len] != '\0' && len < MAX_STR_LEN) {
        len++;
    }
    
    if (len == 0) {
        return;
    }
    
    size_t start = 0;
    size_t end = len - 1;
    
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

void reverse_string_list(char **list, size_t count) {
    if (list == NULL || count == 0) {
        return;
    }
    
    for (size_t i = 0; i < count; i++) {
        if (list[i] != NULL) {
            reverse_string(list[i]);
        }
    }
}

char *duplicate_string(const char *src) {
    if (src == NULL) {
        return NULL;
    }
    
    size_t len = 0;
    /* Possible weaknesses found:
     *  Array index 'len' is used before limits check. [arrayIndexThenCheck]
     */
    while (src[len] != '\0' && len < MAX_STR_LEN) {
        len++;
    }
    
    char *dest = (char *)malloc((len + 1) * sizeof(char));
    
    if (dest == NULL) {
        return NULL;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dest, src, len);
    dest[len] = '\0';
    
    return dest;
}

int main(void) {
    const char *initial_data[] = {
        "hello",
        "world",
        "secure coding",
        "",
        "C developer"
    };
    
    size_t count = sizeof(initial_data) / sizeof(initial_data[0]);
    
    char **string_list = (char **)malloc(count * sizeof(char *));
    if (string_list == NULL) {
        return EXIT_FAILURE;
    }
    
    for (size_t i = 0; i < count; i++) {
        string_list[i] = duplicate_string(initial_data[i]);
        if (string_list[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(string_list[j]);
            }
            free(string_list);
            return EXIT_FAILURE;
        }
    }
    
    reverse_string_list(string_list, count);
    
    for (size_t i = 0; i < count; i++) {
        printf("%s\n", string_list[i]);
    }
    
    for (size_t i = 0; i < count; i++) {
        free(string_list[i]);
    }
    free(string_list);
    
    return EXIT_SUCCESS;
}