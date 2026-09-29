#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct my_struct {
    int id;
    char name[12];
    UT_hash_handle hh;
};

int main() {
    struct my_struct *user = NULL, *s, *tmp;

    s = (struct my_struct *)malloc(sizeof(struct my_struct));
    if (s == NULL) return 1;
    s->id = 1;
    snprintf(s->name, sizeof(s->name), "%s", "John");
    HASH_ADD_INT(user, id, s);

    s = (struct my_struct *)malloc(sizeof(struct my_struct));
    if (s == NULL) return 1;
    s->id = 2;
    snprintf(s->name, sizeof(s->name), "%s", "Jane");
    HASH_ADD_INT(user, id, s);

    for (s = user; s != NULL; s = (struct my_struct *)s->hh.next) {
        printf("Name: %s, ID: %d\n", s->name, s->id);
    }

    HASH_ITER(hh, user, s, tmp) {
        HASH_DEL(user, s);
        free(s);
    }

    return 0;
}