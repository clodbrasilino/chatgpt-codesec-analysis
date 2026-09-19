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
    /* Possible weaknesses found:
     *  Assignment 'user=NULL', assigned value is 0
     */
    struct my_struct *user = NULL, *s;

    s = (struct my_struct *)malloc(sizeof(struct my_struct));
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (s == NULL) return 1;
    s->id = 1;
    strcpy(s->name, "John");
    s->hh_next = user;
    /* Possible weaknesses found:
     *  Condition 'user!=NULL' is always false [knownConditionTrueFalse]
     *  Condition 'user!=NULL' is always false
     */
    if (user != NULL) user->hh_prev = &s->hh_next;
    user = s;

    s = (struct my_struct *)malloc(sizeof(struct my_struct));
    if (s == NULL) return 1;
    s->id = 2;
    strcpy(s->name, "Jane");
    s->hh_next = user;
    /* Possible weaknesses found:
     *  Condition 'user!=NULL' is always true [knownConditionTrueFalse]
     */
    if (user != NULL) user->hh_prev = &s->hh_next;
    user = s;

    for (s = user; s != NULL; s = s->hh_next) {
        printf("Name: %s, ID: %d\n", s->name, s->id);
    }

    /* Possible weaknesses found:
     *  The scope of the variable 'current_user' can be reduced. [variableScope]
     *  Unused variable: tmp [unusedVariable]
     */
    struct my_struct *current_user, *tmp;
    while (user != NULL) {
        current_user = user;
        user = user->hh_next;
        free(current_user);
    }

    return 0;
}