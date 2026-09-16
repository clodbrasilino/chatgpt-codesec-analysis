#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

typedef struct {
    const char *key;
    int value;
} Pair;

typedef struct ValueNode {
    int value;
    struct ValueNode *next;
} ValueNode;

typedef struct Group {
    char *key;
    ValueNode *head;
    ValueNode *tail;
    struct Group *next;
} Group;

typedef struct {
    Group *head;
    Group *tail;
} Map;

static char *duplicate_string(const char *s) {
    size_t len;
    char *copy;

    if (s == NULL) {
        return NULL;
    }

    len = strlen(s);
    copy = malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, s, len + 1);
    return copy;
}

static Map *create_map(void) {
    Map *map = malloc(sizeof(*map));
    if (map == NULL) {
        return NULL;
    }

    map->head = NULL;
    map->tail = NULL;
    return map;
}

static Group *find_group(const Map *map, const char *key) {
    Group *group;

    if (map == NULL || key == NULL) {
        return NULL;
    }

    for (group = map->head; group != NULL; group = group->next) {
        if (strcmp(group->key, key) == 0) {
            return group;
        }
    }

    return NULL;
}

static int append_value(Group *group, int value) {
    ValueNode *node;

    if (group == NULL) {
        return 0;
    }

    node = malloc(sizeof(*node));
    if (node == NULL) {
        return 0;
    }

    node->value = value;
    node->next = NULL;

    if (group->tail != NULL) {
        group->tail->next = node;
    } else {
        group->head = node;
    }
    group->tail = node;

    return 1;
}

static void free_value_nodes(ValueNode *head) {
    while (head != NULL) {
        ValueNode *next = head->next;
        free(head);
        head = next;
    }
}

void free_map(Map *map) {
    Group *group;
    Group *next;

    if (map == NULL) {
        return;
    }

    group = map->head;
    while (group != NULL) {
        next = group->next;
        free(group->key);
        free_value_nodes(group->head);
        free(group);
        group = next;
    }

    free(map);
}

Map *group_pairs(const Pair *pairs, size_t count) {
    Map *map;
    size_t i;

    if (pairs == NULL && count > 0) {
        return NULL;
    }

    map = create_map();
    if (map == NULL) {
        return NULL;
    }

    for (i = 0; i < count; ++i) {
        Group *group;

        if (pairs[i].key == NULL) {
            free_map(map);
            return NULL;
        }

        group = find_group(map, pairs[i].key);
        if (group == NULL) {
            group = malloc(sizeof(*group));
            if (group == NULL) {
                free_map(map);
                return NULL;
            }

            group->key = duplicate_string(pairs[i].key);
            if (group->key == NULL) {
                free(group);
                free_map(map);
                return NULL;
            }

            group->head = NULL;
            group->tail = NULL;
            group->next = NULL;

            if (map->tail != NULL) {
                map->tail->next = group;
            } else {
                map->head = group;
            }
            map->tail = group;
        }

        if (!append_value(group, pairs[i].value)) {
            free_map(map);
            return NULL;
        }
    }

    return map;
}

static void print_map(const Map *map) {
    Group *group;
    ValueNode *node;

    if (map == NULL) {
        return;
    }

    for (group = map->head; group != NULL; group = group->next) {
        printf("%s:", group->key);
        for (node = group->head; node != NULL; node = node->next) {
            printf(" %d", node->value);
        }
        printf("\n");
    }
}

int main(void) {
    Pair pairs[] = {
        {"apple", 1},
        {"banana", 2},
        {"apple", 3},
        {"cherry", 4},
        {"banana", 5},
        {"apple", 6}
    };
    Map *map = group_pairs(pairs, sizeof(pairs) / sizeof(pairs[0]));

    if (map == NULL) {
        fprintf(stderr, "Failed to group pairs\n");
        return 1;
    }

    print_map(map);
    free_map(map);
    return 0;
}