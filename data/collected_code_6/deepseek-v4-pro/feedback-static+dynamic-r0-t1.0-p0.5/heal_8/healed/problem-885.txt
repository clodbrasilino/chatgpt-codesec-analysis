#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <limits.h>

#define MAP_SIZE ((size_t)UCHAR_MAX + 1)

bool is_isomorphic(const char *s, const char *t) {
    if (s == NULL || t == NULL) {
        return false;
    }
    
    size_t len_s = 0;
    size_t len_t = 0;
    
    while (s[len_s] != '\0') {
        if (len_s == SIZE_MAX) {
            return false;
        }
        len_s++;
    }
    while (t[len_t] != '\0') {
        if (len_t == SIZE_MAX) {
            return false;
        }
        len_t++;
    }
    
    if (len_s != len_t) {
        return false;
    }
    
    unsigned char *map_s_to_t = (unsigned char *)calloc(MAP_SIZE, sizeof(unsigned char));
    unsigned char *map_t_to_s = (unsigned char *)calloc(MAP_SIZE, sizeof(unsigned char));
    
    if (map_s_to_t == NULL || map_t_to_s == NULL) {
        free(map_s_to_t);
        free(map_t_to_s);
        return false;
    }
    
    for (size_t i = 0; i < len_s; i++) {
        unsigned char c1 = (unsigned char)s[i];
        unsigned char c2 = (unsigned char)t[i];
        
        if (map_s_to_t[c1] == 0 && map_t_to_s[c2] == 0) {
            map_s_to_t[c1] = c2;
            map_t_to_s[c2] = c1;
        } else if (map_s_to_t[c1] != c2 || map_t_to_s[c2] != c1) {
            free(map_s_to_t);
            free(map_t_to_s);
            return false;
        }
    }
    
    free(map_s_to_t);
    free(map_t_to_s);
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