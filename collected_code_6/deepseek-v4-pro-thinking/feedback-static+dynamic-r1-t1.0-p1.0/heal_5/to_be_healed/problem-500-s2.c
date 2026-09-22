#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  'errno' is defined in header '<errno.h>'; this is probably fixable by adding '#include <errno.h>'
  */

typedef struct list_node {
    const char *data;
    struct list_node *next;
} list_node;

static size_t safe_strlen(const char *str) {
    const char *end = memchr(str, '\0', SIZE_MAX);
    if (end == NULL) {
        /* Possible weaknesses found:
         *  use of undeclared identifier 'ERANGE'
         *  'ERANGE' undeclared (first use in this function)
         *  use of undeclared identifier 'errno'
         *  each undeclared identifier is reported only once for each function it appears in
         *  'errno' undeclared (first use in this function)
         */
        errno = ERANGE;
        return SIZE_MAX;
    }
    return (size_t)(end - str);
}

char *concatenate_list(const list_node *head) {
    const list_node *cur;
    size_t total = 0;

    for (cur = head; cur != NULL; cur = cur->next) {
        size_t len;
        if (cur->data == NULL) {
            return NULL;
        }
        len = safe_strlen(cur->data);
        if (len == SIZE_MAX) {
            return NULL;
        }
        if (len > SIZE_MAX - total) {
            return NULL;
        }
        total += len;
    }

    if (total == SIZE_MAX) {
        return NULL;
    }

    char *result = malloc(total + 1);
    if (result == NULL) {
        return NULL;
    }

    char *pos = result;
    for (cur = head; cur != NULL; cur = cur->next) {
        size_t len = safe_strlen(cur->data);
        size_t remaining = (result + total) - pos;
        if (len > remaining) {
            free(result);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(pos, cur->data, len);
        pos += len;
    }
    *pos = '\0';

    return result;
}

int main(void) {
    list_node *n1 = malloc(sizeof(*n1));
    list_node *n2 = malloc(sizeof(*n2));
    list_node *n3 = malloc(sizeof(*n3));
    char *result;

    if (n1 == NULL || n2 == NULL || n3 == NULL) {
        free(n1);
        free(n2);
        free(n3);
        return EXIT_FAILURE;
    }

    n1->data = "Hello";
    n1->next = n2;
    n2->data = " ";
    n2->next = n3;
    n3->data = "World";
    n3->next = NULL;

    result = concatenate_list(n1);
    if (result == NULL) {
        free(n1);
        free(n2);
        free(n3);
        return EXIT_FAILURE;
    }

    printf("%s\n", result);

    free(result);
    free(n1);
    free(n2);
    free(n3);

    return EXIT_SUCCESS;
}