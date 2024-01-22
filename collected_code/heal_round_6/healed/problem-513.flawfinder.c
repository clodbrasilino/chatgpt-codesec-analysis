Flawfinder version 2.0.19, (C) 2001-2019 David A. Wheeler.
Number of rules (primarily dangerous function names) in C/C++ ruleset: 222
Examining collected_code/heal_round_6/healed/problem-513.c

FINAL RESULTS:

collected_code/heal_round_6/healed/problem-513.c:27:  [2] (buffer) char:
  Statically-sized arrays can be improperly restricted, leading to potential
  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use
  functions that limit length, or ensure that the size is larger than the
  maximum possible length.
collected_code/heal_round_6/healed/problem-513.c:12:  [1] (buffer) strlen:
  Does not handle strings that are not \0-terminated; if given one it may
  perform an over-read (it could cause a crash if unprotected) (CWE-126).
collected_code/heal_round_6/healed/problem-513.c:13:  [1] (buffer) strlen:
  Does not handle strings that are not \0-terminated; if given one it may
  perform an over-read (it could cause a crash if unprotected) (CWE-126).
collected_code/heal_round_6/healed/problem-513.c:16:  [1] (buffer) strncpy:
  Easily used incorrectly; doesn't always \0-terminate or check for invalid
  pointers [MS-banned] (CWE-120).
collected_code/heal_round_6/healed/problem-513.c:18:  [1] (buffer) strncat:
  Easily used incorrectly (e.g., incorrectly computing the correct maximum
  size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf,
  or automatically resizing strings.

ANALYSIS SUMMARY:

Hits = 5
Lines analyzed = 33 in approximately 0.00 seconds (8587 lines/second)
Physical Source Lines of Code (SLOC) = 26
Hits@level = [0]   2 [1]   4 [2]   1 [3]   0 [4]   0 [5]   0
Hits@level+ = [0+]   7 [1+]   5 [2+]   1 [3+]   0 [4+]   0 [5+]   0
Hits/KSLOC@level+ = [0+] 269.231 [1+] 192.308 [2+] 38.4615 [3+]   0 [4+]   0 [5+]   0
Minimum risk level = 1

Not every hit is necessarily a security vulnerability.
You can inhibit a report by adding a comment in this form:
// flawfinder: ignore
Make *sure* it's a false positive!
You can use the option --neverignore to show these.

There may be other security vulnerabilities; review your code!
See 'Secure Programming HOWTO'
(https://dwheeler.com/secure-programs) for more information.
