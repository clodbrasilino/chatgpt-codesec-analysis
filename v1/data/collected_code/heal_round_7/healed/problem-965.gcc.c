collected_code/heal_round_7/healed/problem-965.c: In function 'main':
collected_code/heal_round_7/healed/problem-965.c:46:9: warning: use of possibly-NULL 'str' where non-null expected [CWE-690] [-Wanalyzer-possible-null-argument]
   46 |     str[strcspn(str, "\n")] = '\0';
      |         ^~~~~~~~~~~~~~~~~~
  'main': events 1-4
    |
    |   37 |     char* str = malloc((MAX_INPUT_LENGTH+1)*sizeof(char));
    |      |                 ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    |      |                 |
    |      |                 (1) this call could return NULL
    |......
    |   40 |     if(fgets(str, MAX_INPUT_LENGTH+1, stdin) == NULL) {
    |      |       ~          
    |      |       |
    |      |       (2) following 'false' branch...
    |......
    |   46 |     str[strcspn(str, "\n")] = '\0';
    |      |         ~~~~~~~~~~~~~~~~~~
    |      |         |
    |      |         (3) ...to here
    |      |         (4) argument 1 ('str') from (1) could be NULL where non-null expected
    |
In file included from collected_code/heal_round_7/healed/problem-965.c:4:
/Library/Developer/CommandLineTools/SDKs/MacOSX13.sdk/usr/include/string.h:80:10: note: argument 1 of 'strcspn' must be non-null
   80 | size_t   strcspn(const char *__s, const char *__charset);
      |          ^~~~~~~
-macosx_version_min has been renamed to -macos_version_min
