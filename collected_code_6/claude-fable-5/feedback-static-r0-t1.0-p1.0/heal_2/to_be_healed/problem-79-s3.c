/* Possible weaknesses found:
 *  type specifier missing, defaults to 'int'; ISO C99 and later do not support implicit int [-Wimplicit-int]
 *  'buffer' undeclared here (not in a function)
 *  type defaults to 'int' in declaration of 'buffer' [-Wimplicit-int]
 *  use of undeclared identifier 'buffer'
 */
buffer[sizeof(buffer) - 1U] = '\0';