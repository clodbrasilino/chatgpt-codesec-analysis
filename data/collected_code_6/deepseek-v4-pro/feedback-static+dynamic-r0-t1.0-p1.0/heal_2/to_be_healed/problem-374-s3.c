#include <stdio.h>
#include <string.h>
#include <stddef.h>

void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

void permute(char *str, size_t left, size_t right) {
    if (left == right) {
        printf("%s\n", str);
        return;
    }
    
    for (size_t i = left; i <= right; i++) {
        swap(&str[left], &str[i]);
        permute(str, left + 1, right);
        swap(&str[left], &str[i]);
    }
}

int main(void) {
    char str[] = "abc";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    
    if (len > 0) {
        permute(str, 0, len - 1);
    }
    
    return 0;
}