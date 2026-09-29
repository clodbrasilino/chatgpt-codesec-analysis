#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    int key;
    size_t value;
    int occupied;
} HashEntry;

/* Possible weaknesses found:
 *  to match this '('
 *  expected function body after function declarator
 *  expected ')'
 *  Unmatched '('. Configuration: ''. [syntaxError]
 */
static size_t hash_int(int key, size_t capacity