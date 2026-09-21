#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct my_struct {
    int id;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[12];
    /* Possible weaknesses found:
     *  unknown type name 'UT_hash_handle'
     */
    UT_hash_handle hh;
};

int main() {
    struct my_struct *user = NULL, *s, *tmp;

    s = (struct my_struct *)malloc(sizeof(struct my_struct));
    if (s == NULL) return 1;
    s->id = 1;
    snprintf(s->name, sizeof(s->name), "%s", "John");
    /* Possible weaknesses found:
     *  implicit declaration of function 'HASH_ADD_INT' [-Wimplicit-function-declaration]
     *  call to undeclared function 'HASH_ADD_INT'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  'id' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     *  use of undeclared identifier 'id'
     */
    HASH_ADD_INT(user, id, s);

    s = (struct my_struct *)malloc(sizeof(struct my_struct));
    if (s == NULL) return 1;
    s->id = 2;
    snprintf(s->name, sizeof(s->name), "%s", "Jane");
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

    /* Possible weaknesses found:
     *  implicit declaration of function 'HASH_ITER' [-Wimplicit-function-declaration]
     *  expected ';' before '{' token
     *  call to undeclared function 'HASH_ITER'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  use of undeclared identifier 'hh'
     *  'hh' undeclared (first use in this function)
     *  expected ';' after expression
     */
    HASH_ITER(hh, user, s, tmp) {
        /* Possible weaknesses found:
         *  call to undeclared function 'HASH_DEL'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        HASH_DEL(user, s);
        free(s);
    }

    return 0;
}