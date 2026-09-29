#include <stdio.h>
/* Possible weaknesses found:
 *  No pair for character (<). Can't process file. File is either invalid or unicode, which is currently not supported. [syntaxError]
 *  to match this '<'
 *  empty filename in #include
 *  missing terminating '>' character
 *  expected '>'
 */
#include <