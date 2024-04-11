#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_MATCHES 100

void split_string_with_regex(char *str, char *regex_pattern) {
    regex_t regex_compiled;
    regmatch_t group_array[MAX_MATCHES];

    if (regcomp(&regex_compiled, regex_pattern, REG_EXTENDED)) {
        printf("Could not compile regular expression.\n");
        return;
    };

    char *cursor = str;
    while (!regexec(&regex_compiled, cursor, MAX_MATCHES, group_array, 0)) {
        int offset = group_array[0].rm_eo;
        char cursor_copy[strlen(cursor) + 1];
        strcpy(cursor_copy, cursor);
        cursor_copy[offset] = 0;
        printf("%s\n", cursor_copy);
        cursor += offset;
    } 

    regfree(&regex_compiled);
}

int main() {
    char str[] = "Hello, World! This is a test string.";
    char regex_pattern[] = "[^ ,.!]+";
    split_string_with_regex(str, regex_pattern);
    return 0;
}