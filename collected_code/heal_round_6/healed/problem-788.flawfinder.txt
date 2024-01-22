Flawfinder version 2.0.19, (C) 2001-2019 David A. Wheeler.
Number of rules (primarily dangerous function names) in C/C++ ruleset: 222
Examining collected_code/heal_round_6/healed/problem-788.c

FINAL RESULTS:

collected_code/heal_round_6/healed/problem-788.c:27:  [4] (buffer) strcpy:
  Does not check for buffer overflows when copying to destination [MS-banned]
  (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy
  easily misused).
collected_code/heal_round_6/healed/problem-788.c:21:  [1] (buffer) strlen:
  Does not handle strings that are not \0-terminated; if given one it may
  perform an over-read (it could cause a crash if unprotected) (CWE-126).

ANALYSIS SUMMARY:

Hits = 2
Lines analyzed = 63 in approximately 0.00 seconds (16483 lines/second)
Physical Source Lines of Code (SLOC) = 50
Hits@level = [0]   4 [1]   1 [2]   0 [3]   0 [4]   1 [5]   0
Hits@level+ = [0+]   6 [1+]   2 [2+]   1 [3+]   1 [4+]   1 [5+]   0
Hits/KSLOC@level+ = [0+] 120 [1+]  40 [2+]  20 [3+]  20 [4+]  20 [5+]   0
Minimum risk level = 1

Not every hit is necessarily a security vulnerability.
You can inhibit a report by adding a comment in this form:
// flawfinder: ignore
Make *sure* it's a false positive!
You can use the option --neverignore to show these.

There may be other security vulnerabilities; review your code!
See 'Secure Programming HOWTO'
(https://dwheeler.com/secure-programs) for more information.
