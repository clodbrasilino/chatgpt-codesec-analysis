#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct my_struct {
    int id;
    char name[10];
    /* Possible weaknesses found:
     *  unknown type name 'UT_hash_handle'
     */
    UT_hash_handle hh;
};

int main() {
    struct my_struct *user = NULL, *s;

    s = (struct my_struct *)malloc(sizeof(struct my_struct));
    if (s == NULL) return 1;
    s->id = 1;
    strcpy(s->name, "John");
    /* Possible weaknesses found:
     *  implicit declaration of function 'HASH_ADD_INT' [-Wimplicit-function-declaration]
     *  call to undeclared function 'HASH_ADD_INT'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  use of undeclared identifier 'id'
     *  each undeclared identifier is reported only once for each function it appears in
     *  'id' undeclared (first use in this function)
     */
    HASH_ADD_INT(user, id, s);

    s = (struct my_struct *)malloc(sizeof(struct my_struct));
    if (s == NULL) return 1;
    s->id = 2;
    strcpy(s->name, "Jane");
    /* Possible weaknesses found:
     *  use of undeclared identifier 'id'
     */
    HASH_ADD_INT(user, id, s);

    /* Possible weaknesses found:
     *  request for member 'next' in something not a structure or union
     */
    for (s = user; s != NULL; s = (struct my_struct *)s->hh.next) {
        printf("Name: %s, ID: %d\n", s->name, s->id);
    }

    struct my_struct *current_user, *tmp;
    /* Possible weaknesses found:
     *  'hh' undeclared (first use in this function)
     *  call to undeclared function 'HASH_ITER'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  use of undeclared identifier 'hh'
     *  implicit declaration of function 'HASH_ITER' [-Wimplicit-function-declaration]
     *  expected ';' after expression
     *  expected ';' before '{' token
     */
    HASH_ITER(hh, user, current_user, tmp) {
        /* Possible weaknesses found:
         *  call to undeclared function 'HASH_DEL'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        HASH_DEL(user, current_user);
        free(current_user);
    }

    return 0;
}