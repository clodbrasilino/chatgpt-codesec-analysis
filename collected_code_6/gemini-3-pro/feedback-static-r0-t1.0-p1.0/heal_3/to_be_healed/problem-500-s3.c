#if defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE < 200809L
#undef _POSIX_C_SOURCE
#endif
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char *data;
    size_t data_len;
    struct Node *next;
};

void free_list(struct Node *head) {
    while (head != NULL) {
        struct Node *tmp = head;
        head = head->next;
        free(tmp->data);
        free(tmp);
    }
}

char* concatenate_list(struct Node *head) {
    if (head == NULL) {
        char *empty_str = malloc(1);
        if (empty_str != NULL) {
            empty_str[0] = '\0';
        }
        return empty_str;
    }

    size_t total_length = 0;
    struct Node *current = head;
    while (current != NULL) {
        if (current->data != NULL) {
            total_length += current->data_len;
        }
        current = current->next;
    }

    char *result = malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t remaining = total_length;
    char *dest = result;
    current = head;
    while (current != NULL) {
        if (current->data != NULL) {
            size_t len = current->data_len;
            if (len <= remaining) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(dest, current->data, len);
                dest += len;
                remaining -= len;
            }
        }
        current = current->next;
    }
    *dest = '\0';

    return result;
}

int main(void) {
    struct Node *head = malloc(sizeof(struct Node));
    if (head == NULL) {
        return 1;
    }
    
    struct Node *second = malloc(sizeof(struct Node));
    if (second == NULL) {
        free(head);
        return 1;
    }

    struct Node *third = malloc(sizeof(struct Node));
    if (third == NULL) {
        free(head);
        free(second);
        return 1;
    }

    head->data = strdup("Hello, ");
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    head->data_len = head->data ? strlen(head->data) : 0;
    head->next = second;

    second->data = strdup("world");
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    second->data_len = second->data ? strlen(second->data) : 0;
    second->next = third;

    third->data = strdup("!");
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    third->data_len = third->data ? strlen(third->data) : 0;
    third->next = NULL;

    if (head->data == NULL || second->data == NULL || third->data == NULL) {
        free_list(head);
        return 1;
    }

    char *concatenated = concatenate_list(head);
    if (concatenated != NULL) {
        printf("%s\n", concatenated);
        free(concatenated);
    }

    free_list(head);

    return 0;
}