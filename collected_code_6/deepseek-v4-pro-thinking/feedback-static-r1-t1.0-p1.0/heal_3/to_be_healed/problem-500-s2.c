#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list_node {
    const char *data;
    struct list_node *next;
} list_node;

static size_t safe_strlen(const char *s, size_t maxlen) {
    const char *p = memchr(s, '\0', maxlen);
    return p ? (size_t)(p - s) : maxlen;
}

#define MAX_STRING_LENGTH ((size_t)1024)

char *concatenate_list(const list_node *head) {
    const list_node *cur;
    size_t total = 0;
    char *result;
    char *pos;
    size_t len;
    /* Possible weaknesses found:
     *  The scope of the variable 'remaining' can be reduced. [variableScope]
     */
    size_t remaining;

    for (cur = head; cur != NULL; cur = cur->next) {
        if (cur->data == NULL) {
            return NULL;
        }

        len = safe_strlen(cur->data, MAX_STRING_LENGTH);
        if (len == MAX_STRING_LENGTH) {
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

    result = malloc(total + 1);
    if (result == NULL) {
        return NULL;
    }

    pos = result;
    for (cur = head; cur != NULL; cur = cur->next) {
        if (cur->data == NULL) {
            free(result);
            return NULL;
        }

        len = safe_strlen(cur->data, MAX_STRING_LENGTH);
        if (len == MAX_STRING_LENGTH) {
            free(result);
            return NULL;
        }

        remaining = total - (size_t)(pos - result);
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
    list_node *head;
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
    head = n1;

    result = concatenate_list(head);
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