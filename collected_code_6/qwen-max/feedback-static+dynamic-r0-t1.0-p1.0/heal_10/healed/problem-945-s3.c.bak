#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct my_struct {
    int id;
    char name[10];
    struct my_struct *hh_next;
    struct my_struct **hh_prev;
};

int main() {
    struct my_struct *user = NULL, *s;

    s = (struct my_struct *)malloc(sizeof(struct my_struct));
    if (s == NULL) return 1;
    s->id = 1;
    strcpy(s->name, "John");
    s->hh_next = user;
    user = s;

    s = (struct my_struct *)malloc(sizeof(struct my_struct));
    if (s == NULL) return 1;
    s->id = 2;
    strcpy(s->name, "Jane");
    s->hh_next = user;
    user->hh_prev = &s->hh_next;
    user = s;

    for (s = user; s != NULL; s = s->hh_next) {
        printf("Name: %s, ID: %d\n", s->name, s->id);
    }

    while (user != NULL) {
        s = user;
        user = user->hh_next;
        free(s);
    }

    return 0;
}