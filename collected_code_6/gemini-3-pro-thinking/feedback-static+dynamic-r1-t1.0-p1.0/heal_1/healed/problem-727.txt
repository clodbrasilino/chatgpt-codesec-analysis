#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LEN 8192

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
    size_t available;

    if (input == NULL) {
        return NULL;
    }

    if (regcomp(&regex, "[^a-zA-Z0-9]+", REG_EXTENDED) != 0) {
        return NULL;
    }

    len = strnlen(input, MAX_INPUT_LEN);
    output = malloc(len + 1);
    if (output == NULL) {
        regfree(&regex);
        return NULL;
    }

    cursor = input;
    write_ptr = output;
    available = len;

    while (regexec(&regex, cursor, 1, match, 0) == 0) {
        if (match[0].rm_so > 0) {
            chunk_size = (size_t)match[0].rm_so;
            if (chunk_size > available) {
                chunk_size = available;
            }
            if (chunk_size > 0) {
                memcpy(write_ptr, cursor, chunk_size);
                write_ptr += chunk_size;
                available -= chunk_size;
            }
        }
        
        if (cursor + match[0].rm_eo >= input + len) {
            cursor = input + len;
            break;
        }
        cursor += match[0].rm_eo;
    }

    remaining = strnlen(cursor, available);
    if (remaining > available) {
        remaining = available;
    }
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