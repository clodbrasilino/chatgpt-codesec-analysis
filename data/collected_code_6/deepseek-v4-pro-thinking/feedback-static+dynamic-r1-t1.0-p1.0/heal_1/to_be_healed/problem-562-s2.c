#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    int key;
    size_t value;
    int occupied;
} HashEntry;

/* Possible weaknesses found:
 *  Unmatched '('. Configuration: ''. [syntaxError]
 *  expected ')'
 *  expected function body after function declarator
 *  to match this '('
 */
static size_t hash_int(int key, size_t capacity