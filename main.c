#include <stdio.h>
#include <math.h>
#include <inttypes.h>
#include "utilsme.h"




int main(void)
{

    uint_fast32_t x;


    FILE *fptr;

    fptr = fopen("/home/ali/Downloads/lua","rb");
    char flag =0;
    int tt = 0, counter = 0;
    while(1)
    {
        if (fread(&x,1, 4, fptr) == 0)
            break;





        tt+=4;




        if (getnbits(x,32,6) == 0 && getnbits(x,6,6) == 0b100001){

            if (x == 0x0399e021)
                flag = 1;



            if (flag){

            printf("\n--- %x ---\n",tt-4);

            printf("%s\t%x\n",getstrbits(x,32,32),x);

            printf("%s\t%x\n",getstrbits(x,6,6),getnbits(x,6,6));
            printf("%s\t%x\n",getstrbits(x,11,5),getnbits(x,11,5));
            printf("%s\t%x\n",getstrbits(x,16,5),getnbits(x,16,5));
            printf("%s\t%x\n",getstrbits(x,21,5),getnbits(x,21,5));
            printf("%s\t%x\n",getstrbits(x,26,5),getnbits(x,26,5));
            printf("%s\t%x\n",getstrbits(x,32,6),getnbits(x,32,6));
            getchar();
            counter++;
            }
        }





        /*
        printf("%s\t%02x\n",getstrbits(x,8,8),x);
        printf("%s\t%02x\n",getstrbits(x,3,3),x);

        printf("%s\t%d\n",getstrbits(getnbits(x, 3, 3),32,32),getnbits(x, 3, 3));

        //printf("%s\n",getstrbits(SWAP_INT32(x),32,32));

        getchar();*/

    }
    fclose(fptr);
    printf("\n--- %d ---\n",counter);
    return 0;
}


