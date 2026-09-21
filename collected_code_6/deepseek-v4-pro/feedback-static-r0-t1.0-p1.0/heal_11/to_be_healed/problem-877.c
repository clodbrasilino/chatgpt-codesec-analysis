#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compare_chars(const void *a, const void *b) {
    unsigned char ca = *(const unsigned char *)a;
    unsigned char cb = *(const unsigned char *)b;
    if (ca < cb) return -1;
    if (ca > cb) return 1;
    return 0;
}

void sort_string(char *str, size_t len) {
    if (str == NULL || len == 0) return;
    qsort(str, len, sizeof(char), compare_chars);
}

int main(void) {
    char *str = NULL;
    size_t len = 0;
    size_t buf_size = 256;
    int c;
    size_t i = 0;

    str = malloc(buf_size);
    if (str == NULL) {
        return 1;
    }

    printf("Enter a string: ");

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            break;
        }
        if (i + 1 >= buf_size) {
            char *tmp;
            if (buf_size > (size_t)-1 / 2) {
                free(str);
                return 1;
            }
            buf_size *= 2;
            tmp = realloc(str, buf_size);
            if (tmp == NULL) {
                free(str);
                return 1;
            }
            str = tmp;
        }
        if (i < buf_size - 1) {
            str[i++] = (char)c;
        }
    }

    if (i == 0 && c == EOF) {
        free(str);
        return 1;
    }

    if (i < buf_size) {
        str[i] = '\0';
    } else {
        str[buf_size - 1] = '\0';
    }
    len = i;

    if (len > 0) {
        sort_string(str, len);
    }

    printf("Sorted string: %s\n", str);

    free(str);
    return 0;
}