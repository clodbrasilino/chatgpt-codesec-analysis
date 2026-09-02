/* Possible weaknesses found:
 *  'size_t' is defined in header '<stddef.h>'; this is probably fixable by adding '#include <stddef.h>'
 */
typedef struct {
    /* Possible weaknesses found:
     *  struct member 'List::elements' is never used. [unusedStructMember]
     */
    char **elements;
    /* Possible weaknesses found:
     *  struct member 'List::size' is never used. [unusedStructMember]
     *  unknown type name 'size_t'
     */
    size_t size;
    /* Possible weaknesses found:
     *  struct member 'List::capacity' is never used. [unusedStructMember]
     *  unknown type name 'size_t'
     *  'size_t' is defined in header '<stddef.h>'; this is probably fixable by adding '#include <stddef.h>'
     */
    size_t capacity;
} List;