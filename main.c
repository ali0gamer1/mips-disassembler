#include <stdio.h>
#include <math.h>
#include <inttypes.h>
#include "utils.h"








int main(void)
{

    uint_fast32_t x;


    FILE *fptr;

    fptr = fopen("/home/ali/Downloads/mipsproject/curl","rb");
    fseek(fptr, 1, SEEK_CUR);

    while(1)
    {

        if (fread(&x,1, 4, fptr) == 0)
            break;



        getchar();

    }

    return 0;
}


