#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *filter_alphanumeric(const char *input);

char *filter_alphanumeric(const char *input) {
    regex_t regex;
    char *output;
    const char *cursor;
    char *write_ptr;
    regmatch_t match[1];
    size_t len;
    size_t chunk_size;
    size_t remaining;

    if (input == NULL) {
        return NULL;
    }

    if (regcomp(&regex, "[^a-zA-Z0-9]+", REG_EXTENDED) != 0) {
        return NULL;
    }

    len = strlen(input);
    output = malloc(len + 1);
    if (output == NULL) {
        regfree(&regex);
        return NULL;
    }

    cursor = input;
    write_ptr = output;

    while (regexec(&regex, cursor, 1, match, 0) == 0) {
        if (match[0].rm_so > 0) {
            chunk_size = (size_t)match[0].rm_so;
            memcpy(write_ptr, cursor, chunk_size);
            write_ptr += chunk_size;
        }
        cursor += match[0].rm_eo;
    }

    remaining = strlen(cursor);
    if (remaining > 0) {
        memcpy(write_ptr, cursor, remaining);
        write_ptr += remaining;
    }
    *write_ptr = '\0';

    regfree(&regex);
    return output;
}

int main(void) {
    const char *original = "C0d!ng is f#un & 100% r3w@rd!ng!!";
    char *cleaned;

    cleaned = filter_alphanumeric(original);
    if (cleaned != NULL) {
        printf("%s\n", cleaned);
        free(cleaned);
    }

    return 0;
}