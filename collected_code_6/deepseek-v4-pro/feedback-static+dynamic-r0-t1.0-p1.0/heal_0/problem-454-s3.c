#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

bool contains_z_word(const char *text) {
    if (text == NULL) {
        return false;
    }

    const char *p = text;
    while (*p != '\0') {
        while (*p != '\0' && !isalpha((unsigned char)*p)) {
            p++;
        }
        if (*p == '\0') {
            break;
        }
        const char *word_start = p;
        while (*p != '\0' && isalpha((unsigned char)*p)) {
            p++;
        }
        size_t word_len = (size_t)(p - word_start);
        if (word_len > 0) {
            for (size_t i = 0; i < word_len; i++) {
                if (tolower((unsigned char)word_start[i]) == 'z') {
                    return true;
                }
            }
        }
    }
    return false;
}

int main(void) {
    const char *test1 = "The quick brown fox jumps over the lazy dog";
    const char *test2 = "Hello world";
    const char *test3 = "Zebra";
    const char *test4 = "";
    const char *test5 = NULL;

    printf("Test1: %s\n", contains_z_word(test1) ? "true" : "false");
    printf("Test2: %s\n", contains_z_word(test2) ? "true" : "false");
    printf("Test3: %s\n", contains_z_word(test3) ? "true" : "false");
    printf("Test4: %s\n", contains_z_word(test4) ? "true" : "false");
    printf("Test5: %s\n", contains_z_word(test5) ? "true" : "false");

    return 0;
}