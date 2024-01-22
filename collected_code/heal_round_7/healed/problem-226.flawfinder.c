Flawfinder version 2.0.19, (C) 2001-2019 David A. Wheeler.
Number of rules (primarily dangerous function names) in C/C++ ruleset: 222
Examining collected_code/heal_round_7/healed/problem-226.c

FINAL RESULTS:

collected_code/heal_round_7/healed/problem-226.c:30:  [1] (buffer) strncpy:
  Easily used incorrectly; doesn't always \0-terminate or check for invalid
  pointers [MS-banned] (CWE-120). Risk is low because the source is a
  constant string.

ANALYSIS SUMMARY:

Hits = 1
Lines analyzed = 38 in approximately 0.00 seconds (11431 lines/second)
Physical Source Lines of Code (SLOC) = 26
Hits@level = [0]   1 [1]   1 [2]   0 [3]   0 [4]   0 [5]   0
Hits@level+ = [0+]   2 [1+]   1 [2+]   0 [3+]   0 [4+]   0 [5+]   0
Hits/KSLOC@level+ = [0+] 76.9231 [1+] 38.4615 [2+]   0 [3+]   0 [4+]   0 [5+]   0
Minimum risk level = 1

Not every hit is necessarily a security vulnerability.
You can inhibit a report by adding a comment in this form:
// flawfinder: ignore
Make *sure* it's a false positive!
You can use the option --neverignore to show these.

There may be other security vulnerabilities; review your code!
See 'Secure Programming HOWTO'
(https://dwheeler.com/secure-programs) for more information.
