#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<ctype.h>' or provide a declaration of 'isalpha'
  */

void abbreviate_road(char *str) {
    char *pos = strstr(str, "road");
    while (pos != NULL) {
        /* Possible weaknesses found:
         *  implicit declaration of function 'isalpha' [-Wimplicit-function-declaration]
         *  include the header <ctype.h> or explicitly provide a declaration for 'isalpha'
         *  call to undeclared library function 'isalpha' with type 'int (int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        if ((pos == str || !isalpha(*(pos - 1))) && 
            (pos[4] == '\0' || !isalpha(pos[4]))) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            memmove(pos + 2, pos + 4, strlen(pos + 4) + 1);
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
             */
            strncpy(pos, "rd.", 3);
        }
        pos = strstr(pos + 1, "road");
    }
}

int main() {
    char str[] = "Please use the road to get to the other road.";
    abbreviate_road(str);
    printf("%s\n", str);
    return 0;
}