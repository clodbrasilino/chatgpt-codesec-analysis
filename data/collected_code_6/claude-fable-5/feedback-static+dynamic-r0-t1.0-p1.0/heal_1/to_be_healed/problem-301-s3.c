#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Dict Dict;

struct Dict {
    char *key;
    char *value;
    Dict **children;
    size_t child_count;
};

static Dict *dict_create(const char *key, const char *value)
{
    Dict *d = malloc(sizeof(Dict));
    if (d == NULL) {
        return NULL;
    }
    d->key = NULL;
    d->value = NULL;
    d->children = NULL;
    d->child_count = 0;

    if (key != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(key) + 1;
        d->key = malloc(len);
        if (d->key == NULL) {
            free(d);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(d->key, key, len);
    }

    if (value != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(value) + 1;
        d->value = malloc(len);
        if (d->value == NULL) {
            free(d->key);
            free(d);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(d->value, value, len);
    }

    return d;
}

static int dict_add_child(Dict *parent, Dict *child)
{
    Dict **tmp;

    if (parent == NULL || child == NULL) {
        return -1;
    }

    tmp = realloc(parent->children, (parent->child_count + 1) * sizeof(Dict *));
    if (tmp == NULL) {
        return -1;
    }

    parent->children = tmp;
    parent->children[parent->child_count] = child;
    parent->child_count++;
    return 0;
}

static void dict_free(Dict *d)
{
    size_t i;

    if (d == NULL) {
        return;
    }

    for (i = 0; i < d->child_count; i++) {
        dict_free(d->children[i]);
    }

    free(d->children);
    free(d->key);
    free(d->value);
    free(d);
}

static size_t dict_depth(const Dict *d)
{
    size_t max_child_depth = 0;
    size_t i;

    if (d == NULL) {
        return 0;
    }

    for (i = 0; i < d->child_count; i++) {
        size_t child_depth = dict_depth(d->children[i]);
        if (child_depth > max_child_depth) {
            max_child_depth = child_depth;
        }
    }

    return 1 + max_child_depth;
}

int main(void)
{
    Dict *root;
    Dict *level1;
    Dict *level2;
    Dict *level3;
    Dict *sibling;
    size_t depth;

    root = dict_create("root", NULL);
    if (root == NULL) {
        fprintf(stderr, "allocation failure\n");
        return EXIT_FAILURE;
    }

    level1 = dict_create("a", NULL);
    if (level1 == NULL || dict_add_child(root, level1) != 0) {
        dict_free(level1);
        dict_free(root);
        fprintf(stderr, "allocation failure\n");
        return EXIT_FAILURE;
    }

    level2 = dict_create("b", NULL);
    if (level2 == NULL || dict_add_child(level1, level2) != 0) {
        dict_free(level2);
        dict_free(root);
        fprintf(stderr, "allocation failure\n");
        return EXIT_FAILURE;
    }

    level3 = dict_create("c", "value");
    if (level3 == NULL || dict_add_child(level2, level3) != 0) {
        dict_free(level3);
        dict_free(root);
        fprintf(stderr, "allocation failure\n");
        return EXIT_FAILURE;
    }

    sibling = dict_create("d", "value");
    if (sibling == NULL || dict_add_child(root, sibling) != 0) {
        dict_free(sibling);
        dict_free(root);
        fprintf(stderr, "allocation failure\n");
        return EXIT_FAILURE;
    }

    depth = dict_depth(root);
    printf("Depth of dictionary: %zu\n", depth);

    dict_free(root);
    return EXIT_SUCCESS;
}