#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct kv {
    char key[50];
    char value[50];
    struct kv *next;
} kv_t;

kv_t* drop_empty(kv_t *dict) {
    if (!dict) return NULL;

    kv_t *head = NULL, *prev = NULL;

    for (kv_t *curr = dict; curr != NULL; curr = curr->next) {
        if (strcmp(curr->value, "") != 0) {
            kv_t *node = (kv_t *)malloc(sizeof(kv_t));
            if (!node) {
                printf("Memory allocation failed.\n");
                exit(EXIT_FAILURE);
            }
            strcpy(node->key, curr->key);
            strcpy(node->value, curr->value);
            node->next = NULL;

            if (prev != NULL) {
                prev->next = node;
            } else {
                head = node;
            }

            prev = node;
        }
    }
    return head;
}

int main(void) {
    kv_t *dict = (kv_t *)malloc(4 * sizeof(kv_t));
    strcpy(dict[0].key, "k1"); strcpy(dict[0].value, "v1"); dict[0].next = &dict[1];
    strcpy(dict[1].key, "k2"); strcpy(dict[1].value, ""); dict[1].next = &dict[2];
    strcpy(dict[2].key, "k3"); strcpy(dict[2].value, "v3"); dict[2].next = &dict[3];
    strcpy(dict[3].key, "end"); strcpy(dict[3].value, "end"); dict[3].next = NULL;

    kv_t *cleaned = drop_empty(dict);

    for (kv_t *curr = cleaned; curr != NULL; curr = curr->next) {
        printf("%s: %s\n", curr->key, curr->value);
    }

    kv_t *next;
    for (kv_t *curr = cleaned; curr != NULL; curr = next) {
        next = curr->next;
        free(curr);
    }

    free(dict);

    return 0;
}