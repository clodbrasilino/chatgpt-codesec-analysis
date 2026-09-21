#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    if (str == NULL) {
        return 0;
    }
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

void reverse_string(char *str, size_t max_len) {
    if (str == NULL || max_len == 0) {
        return;
    }
    size_t length = safe_strlen(str, max_len);
    if (length == 0) {
        return;
    }
    for (size_t i = 0; i < length / 2; i++) {
        char temp = str[i];
        str[i] = str[length - 1 - i];
        str[length - 1 - i] = temp;
    }
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
void reverse_strings(char (*list)[50], size_t count) {
    if (list == NULL || count == 0) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        list[i][49] = '\0';
        reverse_string(list[i], 50);
    }
}

int main(void) {
    char strings[][50] = {
        "hello",
        "world",
        "example",
        "programming"
    };
    size_t count = sizeof(strings) / sizeof(strings[0]);
    
    for (size_t i = 0; i < count; i++) {
        strings[i][49] = '\0';
    }
    
    reverse_strings(strings, count);
    
    for (size_t i = 0; i < count; i++) {
        printf("%s\n", strings[i]);
    }
    
    return 0;
}