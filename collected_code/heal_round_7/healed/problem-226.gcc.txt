collected_code/heal_round_7/healed/problem-226.c: In function 'removeOddIndexChars':
collected_code/heal_round_7/healed/problem-226.c:19:16: warning: dereference of possibly-NULL 'tmp' [CWE-690] [-Wanalyzer-possible-null-dereference]
   19 |         tmp[i] = str[j];
      |         ~~~~~~~^~~~~~~~
  'removeOddIndexChars': events 1-8
    |
    |    9 |     if (str == NULL) return;
    |      |        ^
    |      |        |
    |      |        (1) following 'false' branch (when 'str' is non-NULL)...
    |   10 | 
    |   11 |     size_t length = strnlen(str, MAX_LENGTH);
    |      |                     ~~~~~~~~~~~~~~~~~~~~~~~~
    |      |                     |
    |      |                     (2) ...to here
    |   12 | 
    |   13 |     if (length >= MAX_LENGTH) return;
    |      |        ~
    |      |        |
    |      |        (3) following 'false' branch (when 'length <= 1023')...
    |   14 | 
    |   15 |     char* tmp = (char*) calloc(MAX_LENGTH + 1, sizeof(char));
    |      |                         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    |      |                         |
    |      |                         (4) ...to here
    |      |                         (5) this call could return NULL
    |......
    |   18 |     for(i = 0, j = 1; j < length && str[j] != '\0'; i++, j += 2) {
    |      |                       ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    |      |                                  |
    |      |                                  (6) following 'true' branch...
    |   19 |         tmp[i] = str[j];
    |      |         ~~~~~~~~~~~~~~~
    |      |                |    |
    |      |                |    (7) ...to here
    |      |                (8) 'tmp + i' could be NULL: unchecked value from (5)
    |
collected_code/heal_round_7/healed/problem-226.c:21:12: warning: dereference of possibly-NULL 'tmp' [CWE-690] [-Wanalyzer-possible-null-dereference]
   21 |     tmp[i] = '\0';
      |     ~~~~~~~^~~~~~
  'removeOddIndexChars': events 1-6
    |
    |    9 |     if (str == NULL) return;
    |      |        ^
    |      |        |
    |      |        (1) following 'false' branch (when 'str' is non-NULL)...
    |   10 | 
    |   11 |     size_t length = strnlen(str, MAX_LENGTH);
    |      |                     ~~~~~~~~~~~~~~~~~~~~~~~~
    |      |                     |
    |      |                     (2) ...to here
    |   12 | 
    |   13 |     if (length >= MAX_LENGTH) return;
    |      |        ~
    |      |        |
    |      |        (3) following 'false' branch (when 'length <= 1023')...
    |   14 | 
    |   15 |     char* tmp = (char*) calloc(MAX_LENGTH + 1, sizeof(char));
    |      |                         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    |      |                         |
    |      |                         (4) ...to here
    |      |                         (5) this call could return NULL
    |......
    |   21 |     tmp[i] = '\0';
    |      |     ~~~~~~~~~~~~~
    |      |            |
    |      |            (6) 'tmp + i' could be NULL: unchecked value from (5)
    |
-macosx_version_min has been renamed to -macos_version_min
