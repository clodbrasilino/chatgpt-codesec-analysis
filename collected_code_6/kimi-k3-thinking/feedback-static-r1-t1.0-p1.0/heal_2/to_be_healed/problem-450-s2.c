/* Possible weaknesses found:
 *  'size_t' is defined in header '<stddef.h>'; this is probably fixable by adding '#include <stddef.h>'
 *  unknown type name 'size_t'
 */
static size_t bounded_strnlen(const char *s, size_t max_len)
{
    /* Possible weaknesses found:
     *  use of undeclared identifier 'size_t'; did you mean 'sizeof'?
     *  use of undeclared identifier 'len'
     */
    size_t len = 0;
    /* Possible weaknesses found:
     *  use of undeclared identifier 'len'
     */
    while (len < max_len && s[len] != '\0') {
        /* Possible weaknesses found:
         *  use of undeclared identifier 'len'
         */
        len++;
    }
    /* Possible weaknesses found:
     *  use of undeclared identifier 'len'
     */
    return len;
}