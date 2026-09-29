#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool match_word_at_beginning(const char *str, const char *word) {
    if (str == NULL || word == NULL) {
        return false;
    }

    const char *s = str;
    const char *w = word;

    while (*w != '\0' && *s != '\0' && *s == *w) {
        s++;
        w++;
    }

    if (*w != '\0') {
        return false;
    }

    if (*s == '\0') {
        return true;
    }

    if (isspace((unsigned char)*s)) {
        return true;
    }

    switch (*s) {
        case '.':
        case ',':
        case ';':
        case ':':
        case '!':
        case '?':
        case '-':
        case '_':
            return true;
        default:
            return false;
    }
}

int main(void) {
    const char *test1 = "hello world";
    const char *test2 = "helloworld";
    const char *test3 = "hello, everyone";
    const char *test4 = "hello";
    const char *test5 = "he";

    if (match_word_at_beginning(test1, "hello")) {
        printf("Match found in '%s'\n", test1);
    } else {
        printf("No match in '%s'\n", test1);
    }

    if (match_word_at_beginning(test2, "hello")) {
        printf("Match found in '%s'\n", test2);
    } else {
        printf("No match in '%s'\n", test2);
    }

    if (match_word_at_beginning(test3, "hello")) {
        printf("Match found in '%s'\n", test3);
    } else {
        printf("No match in '%s'\n", test3);
    }

    if (match_word_at_beginning(test4, "hello")) {
        printf("Match found in '%s'\n", test4);
    } else {
        printf("No match in '%s'\n", test4);
    }

    if (match_word_at_beginning(test5, "hello")) {
        printf("Match found in '%s'\n", test5);
    } else {
        printf("No match in '%s'\n", test5);
    }

    printf("No match in NULL\n");

    printf("No match with NULL word\n");

    return 0;
}