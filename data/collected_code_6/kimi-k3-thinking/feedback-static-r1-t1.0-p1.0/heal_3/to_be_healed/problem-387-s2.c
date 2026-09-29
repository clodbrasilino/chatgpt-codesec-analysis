/* Possible weaknesses found:
 *  'buffer' undeclared here (not in a function)
 *  call to undeclared library function 'memchr' with type 'void *(const void *, int, unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
 *  use of undeclared identifier 'buffer'
 *  implicit declaration of function 'memchr' [-Wimplicit-function-declaration]
 *  'size_t' is defined in header '<stddef.h>'; this is probably fixable by adding '#include <stddef.h>'
 *  include '<string.h>' or provide a declaration of 'memchr'
 *  include the header <string.h> or explicitly provide a declaration for 'memchr'
 */
const char *nul = memchr(buffer, '\0', sizeof(buffer));
/* Possible weaknesses found:
 *  expected identifier or '(' before 'if'
 *  expected identifier or '('
 *  syntax error: keyword 'if' is not allowed in global scope [syntaxError]
 */
if (nul == NULL)
{
    fprintf(stderr, "Failed to read input.\n");
    return EXIT_FAILURE;
}
/* Possible weaknesses found:
 *  type defaults to 'int' in declaration of 'length' [-Wimplicit-int]
 *  type specifier missing, defaults to 'int'; ISO C99 and later do not support implicit int [-Wimplicit-int]
 *  use of undeclared identifier 'buffer'
 *  use of undeclared identifier 'size_t'; did you mean 'sizeof'?
 *  'size_t' undeclared here (not in a function)
 */
length = (size_t)(nul - buffer);