#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char *first_repeated_word(const char *str) {
    if (str == NULL) {
        return "None";
    }
    const char *p = str;
    while (*p != '\0') {
        while (*p != '\0' && isspace((unsigned char)*p)) {
            p++;
        }
        if (*p == '\0') {
            break;
        }
        const char *start = p;
        while (*p != '\0' && !isspace((unsigned char)*p)) {
            p++;
        }
        size_t len = (size_t)(p - start);
        const char *q = str;
        while (q < start) {
            while (q < start && isspace((unsigned char)*q)) {
                q++;
            }
            if (q >= start) {
                break;
            }
            const char *wstart = q;
            while (q < start && !isspace((unsigned char)*q)) {
                q++;
            }
            size_t wlen = (size_t)(q - wstart);
            if (wlen == len && strncmp(wstart, start, len) == 0) {
                char *buf = malloc(len + 1);
                if (buf == NULL) {
                    return NULL;
                }
                memcpy(buf, start, len);
                buf[len] = '\0';
                return buf;
            }
        }
    }
    return "None";
}

int main(void) {
    const char str[] = "cat dog cat dog";
    const char *word = first_repeated_word(str);
    if (word == NULL) {
        printf("None\n");
    } else {
        printf("%s\n", word);
        if (word != "None") {
            free((void*)word);
        }
    }
    return 0;
}