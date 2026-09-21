#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include <limits.h>
#include <stdint.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'calloc'
  */

bool is_isomorphic(const char *s, const char *t) {
    if (s == NULL || t == NULL) {
        return false;
    }

    size_t len_s = 0;
    size_t len_t = 0;
    
    while (s[len_s] != '\0') {
        if (len_s >= SIZE_MAX) {
            return false;
        }
        len_s++;
    }
    
    while (t[len_t] != '\0') {
        if (len_t >= SIZE_MAX) {
            return false;
        }
        len_t++;
    }

    if (len_s != len_t) {
        return false;
    }

    if (len_s == 0) {
        return true;
    }

    /* Possible weaknesses found:
     *  implicit declaration of function 'calloc' [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'calloc'
     *  call to undeclared library function 'calloc' with type 'void *(unsigned long, unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    unsigned char *map_s_t = (unsigned char *)calloc(UCHAR_MAX + 1, sizeof(unsigned char));
    unsigned char *map_t_s = (unsigned char *)calloc(UCHAR_MAX + 1, sizeof(unsigned char));
    
    if (map_s_t == NULL || map_t_s == NULL) {
        /* Possible weaknesses found:
         *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
         *  include '<stdlib.h>' or provide a declaration of 'free'
         *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
         */
        free(map_s_t);
        free(map_t_s);
        return false;
    }

    for (size_t i = 0; i < len_s; i++) {
        unsigned char c1 = (unsigned char)s[i];
        unsigned char c2 = (unsigned char)t[i];

        if (map_s_t[c1] == 0 && map_t_s[c2] == 0) {
            map_s_t[c1] = c2;
            map_t_s[c2] = c1;
        } else if (map_s_t[c1] != c2 || map_t_s[c2] != c1) {
            free(map_s_t);
            free(map_t_s);
            return false;
        }
    }

    free(map_s_t);
    free(map_t_s);
    return true;
}

int main(void) {
    const char *s1 = "egg";
    const char *t1 = "add";
    const char *s2 = "foo";
    const char *t2 = "bar";
    const char *s3 = "paper";
    const char *t3 = "title";
    const char *s4 = "ab";
    const char *t4 = "aa";

    printf("%s and %s: %s\n", s1, t1, is_isomorphic(s1, t1) ? "true" : "false");
    printf("%s and %s: %s\n", s2, t2, is_isomorphic(s2, t2) ? "true" : "false");
    printf("%s and %s: %s\n", s3, t3, is_isomorphic(s3, t3) ? "true" : "false");
    printf("%s and %s: %s\n", s4, t4, is_isomorphic(s4, t4) ? "true" : "false");

    return 0;
}