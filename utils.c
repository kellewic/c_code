#include <ctype.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 255

/**
 * Like ROT13 but uses extended ASCII instead
 */
static void
rot(unsigned char *s, uint32_t len, uint16_t r) {
    uint_fast32_t c, x;

    for (x = 0, c = s[x]; x < len; c = s[++x]) {
        if ((c + r) > MAX_CHAR) {
            s[x] = (c + r) - (MAX_CHAR+1);
        }
        else {
            s[x] = (c + r);
        }
    }
}

/**
 * Reverse of rot()
 */
static void
unrot(unsigned char *s, uint32_t len, uint16_t r) {
    uint_fast32_t c, x;

    for (x = 0, c = s[x]; x < len; c = s[++x]) {
        if ((c - r) < 0) {
            s[x] = (c - r) + (MAX_CHAR+1);
        }
        else {
            s[x] = (c - r);
        }
    }
}

/**
 * Convert a two-char hex string into the int it represents
 */
static const int
hex2int(char c) {
    char c1 = tolower(c);

    return (c1 >= 'a')
        ? ((int)c1 - (int)'a') + 10
        : ((int)c1 - (int)'0');
}

/**
 * Convert a two-char hex string into the char it represents
 */
static const char
hex2char(char *what)
{
  register char digit;
  digit = (what[0] >= 'A' ? ((what[0] & 0xdf) - 'A')+10 : (what[0] - '0'));
  digit *= 16;
  digit += (what[1] >= 'A' ? ((what[1] & 0xdf) - 'A')+10 : (what[1] - '0'));
  return(digit);
}

/**
 *
 */
int main(void) {
    unsigned char *s = calloc(128, sizeof(unsigned char));
    int rotate = 13;
    int i, j, k;
    strcpy(s, "Testing this!");

    rot(s, strlen(s), rotate);
    printf("%s\n", s);

    unrot(s, strlen(s), rotate);
    printf("%s\n", s);

    char *t = calloc(128, sizeof(char));
    strcpy(t, "AF");

    for (i = 0, j = 0, k = 0; j < (strlen(t) / 2); i+= 2, j++) {
        k += (hex2int(t[i]) << 4) + (hex2int(t[i+1]));
    }
    printf("%d\n", k);

	printf("%c\n", hex2char("53"));

    return 0;
}

