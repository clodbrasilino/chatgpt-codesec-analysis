#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strncpy'
  */

typedef struct {
    int id;
    char name[50];
} Tuple;

Tuple* create_tuple(int id, const char *name) {
    Tuple *t = (Tuple *)malloc(sizeof(Tuple));
    if (t == NULL) {
        exit(EXIT_FAILURE);
    }
    t->id = id;
    /* Possible weaknesses found:
     *  call to undeclared library function 'strncpy' with type 'char *(char *, const char *, unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <string.h> or explicitly provide a declaration for 'strncpy'
     *  implicit declaration of function 'strncpy' [-Wimplicit-function-declaration]
     */
    strncpy(t->name, name, 49);
    t->name[49] = '\0';
    return t;
}

void append_name(char *dest, const char *src) {
    /* Possible weaknesses found:
     *  include '<string.h>' or provide a declaration of 'strlen'
     *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <string.h> or explicitly provide a declaration for 'strlen'
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     */
    size_t dest_len = strlen(dest);
    if (dest_len + strlen(src) + 2 > 49) {
        dest[49] = '\0';
        return;
    }
    /* Possible weaknesses found:
     *  include '<string.h>' or provide a declaration of 'strcat'
     *  include the header <string.h> or explicitly provide a declaration for 'strcat'
     *  call to undeclared library function 'strcat' with type 'char *(char *, const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'strcat' [-Wimplicit-function-declaration]
     */
    strcat(dest, ", ");
    strcat(dest, src);
}

Tuple* join_tuples(Tuple *a, Tuple *b) {
    if (a->id != b->id) {
        return NULL;
    }
    append_name(a->name, b->name);
    free(b);
    return a;
}

int main() {
    Tuple *t1 = create_tuple(1, "Alice");
    Tuple *t2 = create_tuple(1, "Bob");
    Tuple *t3 = create_tuple(2, "Carol");

    Tuple *result = join_tuples(t1, t2);
    if (result != NULL) {
        printf("Joined: %d - %s\n", result->id, result->name);
        free(result);
    } else {
        printf("Did not join.\n");
    }

    if (t3 != NULL) {
        free(t3);
    }

    return 0;
}