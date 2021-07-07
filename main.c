#include <stdio.h>
#include <math.h>
#include <inttypes.h>
#include "utilsme.h"


void detect_register(char _r1[], char r1)
{
            if (r1 == 3 || r1 == 2){
                _r1[0] = 'v';
                _r1[1] = (r1-2) + '0';
            }else


            if (r1 <= 7 && r1 >= 4){
                _r1[0] = 'a';
                _r1[1] = (r1-4) + '0';

            }else

            if (r1 <= 15 && r1 >= 8){

                _r1[0] = 't';
                _r1[1] = (r1-8) + '0';

            }else

            if (r1 <= 23 && r1 >= 16){

                _r1[0] = 's';
                _r1[1] = (r1-16) + '0';

            }else

            if (r1 == 24 || r1 == 25){
                _r1[0] = 't';
                _r1[1] = (r1-16) + '0';

            }else

            if (r1 == 26 || r1 == 27){
                _r1[0] = 'k';
                _r1[1] = (r1-26) + '0';

            }else


            if (r1 == 28)
                strcpy(_r1, "gp");
            else

            if (r1 == 29)
                strcpy(_r1, "sp");
            else

            if (r1 == 30)
                strcpy(_r1, "fp");
            else

            if (r1 == 31)
                strcpy(_r1, "ra");



}


int main(void)
{

    uint_fast32_t x;


    FILE *fptr;

    fptr = fopen("/home/ali/Downloads/lua","rb");
    char flag =0;
    int tt = 0x400000, counter = 0;

    char r1,r2,r3;


    char _r1[4] = {0}, _r2[4] = {0}, _r3[4] = {0};

    while(1)
    {
        if (fread(&x,1, 4, fptr) == 0)
            break;





        tt+=4;



        if (getnbits(x,32,6) == 0 && getnbits(x,6,6) == 0b100001){



            r3 = getnbits(x,16,5);
            r2 = getnbits(x,21,5);
            r1 = getnbits(x,26,5);


            detect_register(_r1,r1);
            detect_register(_r2,r2);
            detect_register(_r3,r3);





            printf("%x:\t",tt-4);

            printf("%s ", "addu");

            printf("%s,", _r3);
            printf("%s,", _r1);
            printf("%s\n", _r2);





            /*
            printf("\n--- %x ---\n",tt-4);

            printf("%s\t%x\n",getstrbits(x,32,32),x);

            printf("%s\t%x\n",getstrbits(x,6,6),getnbits(x,6,6));
            printf("%s\t%x\n",getstrbits(x,11,5),getnbits(x,11,5));
            printf("%s\t%x\n",getstrbits(x,16,5),getnbits(x,16,5));
            printf("%s\t%x\n",getstrbits(x,21,5),getnbits(x,21,5));
            printf("%s\t%x\n",getstrbits(x,26,5),getnbits(x,26,5));
            printf("%s\t%x\n",getstrbits(x,32,6),getnbits(x,32,6));*/
            counter++;

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


