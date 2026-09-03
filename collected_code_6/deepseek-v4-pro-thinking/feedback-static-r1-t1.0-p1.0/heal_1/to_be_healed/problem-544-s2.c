#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct {
    int first;
    int second;
} Tuple;

/* Possible weaknesses found:
 *  to match this '{'
 */
static bool append_text(char **result, size_t *length, size_t *capacity, const char *text, size_t text_len) {
    size_t needed = *length + text_len + 1;
    if (needed < *length) {
        free(*result);
        *result = NULL;
        return false;
    }

    /* Possible weaknesses found:
     *  to match this '{'
     */
    if (needed > *capacity) {
        size_t new_capacity = *capacity;
        /* Possible weaknesses found:
         *  to match this '{'
         *  Unmatched '{'. Configuration: ''. [syntaxError]
         */
        while (new_capacity < needed) {
            if (new_capacity > (size_t)-1 / 2) {
                free(*result);
                *result = NULL;
                return false;
            }
            /* Possible weaknesses found:
             *  expected ';' at end of input
             *  'new' undeclared (first use in this function)
             *  each undeclared identifier is reported only once for each function it appears in
             *  expected declaration or statement at end of input
             *  expected '}'
             *  use of undeclared identifier 'new'
             */
            new