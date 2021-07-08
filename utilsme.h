#define SWAP_INT32(x) (((x) >> 24) | (((x) & 0x00FF0000) >> 8) | (((x) & 0x0000FF00) << 8) | ((x) << 24))
#include<math.h>

uint_fast32_t getnbits(uint_fast32_t num, unsigned char p, unsigned char n)
{
    uint_fast32_t mask ;

    mask = ~(~0U << n) << (p  - n);





    return (mask & num) >>(p-n);
}


char *getstrbits(uint_fast32_t x, unsigned char bitcount, unsigned char max)
{
  char *the = (char *) malloc(bitcount + 1);

  uint_fast32_t n = sizeof(uint_fast32_t);

  int count = 0;
  int i;
  for (i = bitcount-1; i >= 0; --i)
  {
    if (count>=max)
	    break;

    the[bitcount - i - 1] = (x & (uint_fast32_t)pow(2, i)) ? ('1') : ('0');


    count++;
  }

  the[bitcount] = 0;
  return the;
}



