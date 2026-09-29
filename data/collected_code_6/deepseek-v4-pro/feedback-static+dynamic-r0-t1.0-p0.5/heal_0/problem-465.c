#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dict_entry {
    char *key;
    char *value;
    struct dict_entry *next;
} dict_entry;

typedef struct {
    dict_entry *head;
    size_t size;
} dictionary;

dictionary *dict_create(void) {
    dictionary *d = malloc(sizeof(*d));
    if (!d) return NULL;
    d->head = NULL;
    d->size = 0;
    return d;
}

int dict_add(dictionary *d, const char *key, const char *value) {
    if (!d || !key || !value) return -1;
    dict_entry *e = malloc(sizeof(*e));
    if (!e) return -1;
    e->key = malloc(strlen(key) + 1);
    e->value = malloc(strlen(value) + 1);
    if (!e->key || !e->value) {
        free(e->key);
        free(e->value);
        free(e);
        return -1;
    }
    strcpy(e->key, key);
    strcpy(e->value, value);
    e->next = d->head;
    d->head = e;
    d->size++;
    return 0;
}

void dict_drop_empty(dictionary *d) {
    if (!d) return;
    dict_entry **pp = &d->head;
    while (*pp) {
        dict_entry *e = *pp;
        if (e->value == NULL || e->value[0] == '\0') {
            *pp = e->next;
            free(e->key);
            free(e->value);
            free(e);
            d->size--;
        } else {
            pp = &e->next;
        }
    }
}

void dict_print(const dictionary *d) {
    if (!d) return;
    for (dict_entry *e = d->head; e; e = e->next) {
        printf("%s: %s\n", e->key, e->value);
    }
}

void dict_free(dictionary *d) {
    if (!d) return;
    dict_entry *e = d->head;
    while (e) {
        dict_entry *next = e->next;
        free(e->key);
        free(e->value);
        free(e);
        e = next;
    }
    free(d);
}

int main(void) {
    dictionary *d = dict_create();
    if (!d) return 1;

    dict_add(d, "name", "Alice");
    dict_add(d, "email", "");
    dict_add(d, "phone", "12345");
    dict_add(d, "address", "");
    dict_add(d, "city", "Berlin");

    printf("Before dropping empty:\n");
    dict_print(d);

    dict_drop_empty(d);

    printf("\nAfter dropping empty:\n");
    dict_print(d);

    dict_free(d);
    return 0;
}