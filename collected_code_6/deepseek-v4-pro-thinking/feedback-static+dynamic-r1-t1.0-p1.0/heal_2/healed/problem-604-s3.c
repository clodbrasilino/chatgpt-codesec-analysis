#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static void reverse_range(char *begin, char *end) {
    while (begin < end) {
        char tmp = *begin;
        *begin = *end;
        *end = tmp;
        ++begin;
        --end;
    }
}

char *reverse_words(char *str, size_t len) {
    if (str == NULL || len == 0) {
        return str;
    }
    reverse_range(str, str + len - 1);
    char *p = str;
    char *end = str + len;
    while (p < end) {
        if (isspace((unsigned char)*p)) {
            ++p;
        } else {
            char *start = p;
            while (p < end && !isspace((unsigned char)*p)) {
                ++p;
            }
            reverse_range(start, p - 1);
        }
    }
    return str;
}

static char *read_line(FILE *stream) {
    size_t size = 128;
    size_t len = 0;
    char *buffer = malloc(size);
    if (buffer == NULL) {
        return NULL;
    }
    int c;
    while ((c = fgetc(stream)) != EOF && c != '\n') {
        if (len + 1 >= size) {
            size *= 2;
            char *new_buffer = realloc(buffer, size);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = new_buffer;
        }
        buffer[len++] = (char)c;
    }
    if (c == EOF && len == 0) {
        free(buffer);
        return NULL;
    }
    buffer[len] = '\0';
    return buffer;
}

int main(void) {
    char *line;
    while ((line = read_line(stdin)) != NULL) {
        size_t len = strlen(line);
        if (len > 0) {
            reverse_words(line, len);
            puts(line);
        }
        free(line);
    }
    return 0;
}