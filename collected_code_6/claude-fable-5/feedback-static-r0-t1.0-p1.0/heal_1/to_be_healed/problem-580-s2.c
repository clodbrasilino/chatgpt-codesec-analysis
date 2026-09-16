#include <stdio.h>
#include <stdlib.h>

typedef enum { ELEM_INT, ELEM_TUPLE } ElemType;

typedef struct Element Element;

struct Element {
    ElemType type;
    union {
        int value;
        struct {
            Element **items;
            size_t count;
        } tuple;
    } data;
};

static void free_element(Element *e);

static Element *make_int(int value)
/* Possible weaknesses found:
 *  Unmatched '{'. Configuration: ''. [syntaxError]
 *  to match this '{'
 */
{
    Element *e = malloc(sizeof *e);
    if (e == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     *  expected declaration or statement at end of input
     *  use of undeclared identifier 'ELEM'
     *  expected '}'
     *  each undeclared identifier is reported only once for each function it appears in
     *  expected ';' at end of input
     *  'ELEM' undeclared (first use in this function)
     */
    e->type = ELEM