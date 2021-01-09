#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define MAX_STR2BCD	255
#define MAX_BCD_LEN	128

// Originally written in 2005 to apply packed BCD to credit card numbers

static unsigned char bcd_map[100] = {
	0  , 1  , 2  , 3  , 4  , 5  , 6  , 7  , 8  , 9  ,
	16 , 17 , 18 , 19 , 20 , 21 , 22 , 23 , 24 , 25 ,
	32 , 33 , 34 , 35 , 36 , 37 , 38 , 39 , 40 , 41 ,
	48 , 49 , 50 , 51 , 52 , 53 , 54 , 55 , 56 , 57 , 
	64 , 65 , 66 , 67 , 68 , 69 , 70 , 71 , 72 , 73 ,
	80 , 81 , 82 , 83 , 84 , 85 , 86 , 87 , 88 , 89 ,
	96 , 97 , 98 , 99 , 100, 101, 102, 103, 104, 105,
	112, 113, 114, 115, 116, 117, 118, 119, 120, 121,
	128, 129, 130, 131, 132, 133, 134, 135, 136, 137,
	144, 145, 146, 147, 148, 149, 150, 151, 152, 153
};


uint_fast8_t
tobcd(const char *str, size_t str_len, unsigned char **i_ret)
{
	int_fast8_t tmp[MAX_STR2BCD+2]={0};
	register int_fast16_t x;
	register uint_fast8_t t_pos;

	if (!str_len || str_len > MAX_STR2BCD) return 0;

	// Strip all non-number characters
	for (x=0, t_pos=0; x<str_len; x++){
		if (str[x] >= 48 && str[x] <= 57){
			tmp[t_pos++] = str[x];
		}
	}

	// If we have an odd number of characters,
	// we need to left pad with a '0'
	if (t_pos & 0x1){
		// Shuffle right to make room
		for (x=t_pos-1; x>=0; x--){
			tmp[x+1] = tmp[x];
		}

		// Pad with '0' and increment length
		tmp[0] = '0';
		t_pos++;
	}

	// Now that we have good data to work with, let's figure out
	// how much room we need for the packed BCD
	str_len = t_pos;
	*i_ret = malloc(1+(((int)(str_len/2))+(str_len%2)));

	// Convert number inputs (in groups of two) to packed
	// BCD values that we can return to the caller
	//
	// Since we know we have nothing but numbers, we roll our own
	// atoi() calculation. This is significantly faster than libc's
	// atoi() which uses ctype.h functions that in turn use locale
	// functions we don't care about
	for (x=0, t_pos=0; x<str_len; x+=2){
		(*i_ret)[t_pos++] = bcd_map[((tmp[x]-'0')*10) + (tmp[x+1]-'0')];
	}

	return t_pos;
}


int main(){
	register int y, x;
	uint_fast8_t r_len;
	unsigned char *ret;
	size_t d_len;
	char *d = calloc(1, 256);

	strncpy(d, "3782-8224631-0005", 255);
	d_len = strlen(d);

	for (y=0; y<=1000000; y++){
		r_len = tobcd(d, d_len, &ret);

        if (y == 0){
            for (x=0; x<r_len; x++){
            	printf("%d\n", ret[x]);
            }
            printf("%s\n", ret);
        }

		if (r_len && ret)	free(ret);
	}

	printf("\n");
	return 0;
}

