#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

static size_t safe_string_length(const char *str, size_t max_len) {
    size_t len = 0;
    if (str == NULL) {
        return 0;
    }
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

bool is_isomorphic(const char *s, const char *t) {
    if (s == NULL || t == NULL) {
        return false;
    }
    
    const size_t MAX_LEN = 512;
    
    size_t len_s = safe_string_length(s, MAX_LEN);
    if (len_s >= MAX_LEN || s[len_s] != '\0') {
        return false;
    }
    
    size_t len_t = safe_string_length(t, MAX_LEN);
    if (len_t >= MAX_LEN || t[len_t] != '\0') {
        return false;
    }
    
    if (len_s != len_t) {
        return false;
    }
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char map_s_to_t[256];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char map_t_to_s[256];
    
    memset(map_s_to_t, 0, sizeof(map_s_to_t));
    memset(map_t_to_s, 0, sizeof(map_t_to_s));
    
    for (size_t i = 0; i < len_s; i++) {
        unsigned char c1 = (unsigned char)s[i];
        unsigned char c2 = (unsigned char)t[i];
        
        if (c1 > 255 || c2 > 255) {
            return false;
        }
        
        if (map_s_to_t[c1] == 0 && map_t_to_s[c2] == 0) {
            map_s_to_t[c1] = c2;
            map_t_to_s[c2] = c1;
        } else if (map_s_to_t[c1] != c2 || map_t_to_s[c2] != c1) {
            return false;
        }
    }
    
    return true;
}

int main(void) {
    char str1[] = "egg";
    char str2[] = "add";
    char str3[] = "foo";
    char str4[] = "bar";
    char str5[] = "paper";
    char str6[] = "title";
    
    printf("%s and %s: %s\n", str1, str2, is_isomorphic(str1, str2) ? "true" : "false");
    printf("%s and %s: %s\n", str3, str4, is_isomorphic(str3, str4) ? "true" : "false");
    printf("%s and %s: %s\n", str5, str6, is_isomorphic(str5, str6) ? "true" : "false");
    
    return 0;
}