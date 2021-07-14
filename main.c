#include <stdio.h>
#include <math.h>
#include <inttypes.h>
#include "utilsme.h"

unsigned int address = 0x400000;
#define PRINT_ADDRESS(heh) printf("%x:"heh,address-4)


void detect_register(char _r1[], char *r1)
{
            if (*r1 == 0)
            {
                _r1[0] = '$';
                _r1[1] = '0';
            }else

            if(*r1 == 1)
            {
                _r1[0] = 'a';
                _r1[1] = 't';
            }else

            if (*r1 == 3 || *r1 == 2){ //v0 v1
                _r1[0] = 'v';
                _r1[1] = ((*r1)-2) + '0';
            }else


            if (*r1 <= 7 && *r1 >= 4){ // a0-a3
                _r1[0] = 'a';
                _r1[1] = (*r1-4) + '0';

            }else

            if (*r1 <= 15 && *r1 >= 8){ //t0-t7

                _r1[0] = 't';
                _r1[1] = (*r1-8) + '0';

            }else

            if (*r1 <= 23 && *r1 >= 16){ //s0-s7

                _r1[0] = 's';
                _r1[1] = (*r1-16) + '0';

            }else

            if (*r1 == 24 || *r1 == 25){ //t8 t9
                _r1[0] = 't';
                _r1[1] = (*r1-16) + '0';

            }else

            if (*r1 == 26 || *r1 == 27){ //k0 k1
                _r1[0] = 'k';
                _r1[1] = (*r1-26) + '0';

            }else


            if (*r1 == 28)
                strcpy(_r1, "gp");
            else

            if (*r1 == 29)
                strcpy(_r1, "sp");
            else

            if (*r1 == 30)
                strcpy(_r1, "fp");
            else

            if (*r1 == 31)
                strcpy(_r1, "ra");

            else
                *r1 = -1;

}


char detect_instruction(unsigned char bits)
{
    if (bits == 0)
        return 0;

    else
    if (bits == 0b11 || bits ==0b10)
        return 2;


    return 1;
}


void parse_i(uint_fast32_t x)
{

    char r1, r2;
    int16_t  imm;

    unsigned char opcode;

    char _r1[6] = {0}, _r2[6] = {0};


    imm = getnbits(x,16,16); //immediate
    r2 = getnbits(x,21,5);  //rt
    r1 = getnbits(x,26,5);  //rs
    opcode = getnbits(x,32,6);

    detect_register(_r1,&r1);
    detect_register(_r2,&r2);



    if (opcode == 1 && r2 == 0)
    {
        if (r1 == -1)
            return 0;

        PRINT_ADDRESS("\t");
        printf("bltz\t%s, %x\n",_r1,imm);
    }else

    if (opcode == 1 && r2 == 1)
    {
        if (r1 == -1)
            return 0;

        PRINT_ADDRESS("\t");
        printf("bgez\t%s, %x\n",_r1,imm);
    }else

    if (opcode == 0x4)
    {
        if (r1 == -1 || r2 == -1)
            return 0;

        PRINT_ADDRESS("\t");
        printf("beq\t%s, %s, %x\n", _r1, _r2, ((address) << 32 ) + (imm<<2)   );
    }else

    if (opcode == 0x5)
    {
        if (r1 == -1 || r2 == -1)
            return 0;

        PRINT_ADDRESS("\t");
        printf("bne\t%s, %s, %x\n", _r1, _r2, ((address) << 32 ) + (imm<<2)   );
    }else

    if (opcode == 0x6 && r2 == 0)
    {
        if (r1 == -1)
            return 0;

        PRINT_ADDRESS("\t");
        printf("blez\t%s, %x\n", _r1, ((address) << 32 ) + (imm<<2));
    }else

    if (opcode == 0x7 && r2 == 0)
    {
        if (r1 == -1)
            return 0;

        PRINT_ADDRESS("\t");
        printf("bgtz\t%s, %x\n", _r1, ((address) << 32 ) + (imm<<2));
    }else

    if (opcode == 0x8)
    {
        if (r1 == -1 || r2 == -1)
            return 0;

        PRINT_ADDRESS("\t");
        printf("addi\t%s, %s, %x\n", _r2, _r1, imm);
    }else

    if (opcode == 0x9)
    {
        if (r1 == -1 || r2 == -1)
            return 0;

        PRINT_ADDRESS("\t");
        printf("addiu\t%s, %s, %x\n", _r2, _r1, imm);
    }

    if (opcode == 0xa)
    {
        if (r1 == -1 || r2 == -1)
            return 0;

        PRINT_ADDRESS("\t");
        printf("slti\t%s, %s, %x\n", _r2, _r1, imm);
    }else

    if (opcode == 0xb)
    {
        if (r1 == -1 || r2 == -1)
            return 0;

        PRINT_ADDRESS("\t");
        printf("sltiu\t%s, %s, %x\n", _r2, _r1, imm);
    }else

    if (opcode == 0xc)
    {
        if (r1 == -1 || r2 == -1)
            return 0;

        PRINT_ADDRESS("\t");
        printf("andi\t%s, %s, %x\n", _r2, _r1, imm);
    }else

    if (opcode == 0xd)
    {
        if (r1 == -1 || r2 == -1)
            return 0;

        PRINT_ADDRESS("\t");
        printf("ori\t%s, %s, %x\n", _r2, _r1, imm);
    }else

    if (opcode == 0xe)
    {
        if (r1 == -1 || r2 == -1)
            return 0;

        PRINT_ADDRESS("\t");
        printf("xori\t%s, %s, %x\n", _r2, _r1, imm);
    }else

    if (opcode == 0xf)
    {
        if (r2 == -1)
            return 0;

        PRINT_ADDRESS("\t");
        printf("lui\t%s, %x\n", _r2, imm);
    }else

    if (opcode == 0x20)
    {
        if (r1 == -1 || r2 == -1)
            return 0;

        PRINT_ADDRESS("\t");
        printf("lb\t%s, %x(%s)\n", _r2, imm, _r1);
    }else

    if (opcode == 0x21)
    {
        if (r1 == -1 || r2 == -1)
            return 0;

        PRINT_ADDRESS("\t");
        printf("lh\t%s, %x(%s)\n", _r2, imm, _r1);
    }else

    if (opcode == 0x23)
    {
        if (r1 == -1 || r2 == -1)
            return 0;

        PRINT_ADDRESS("\t");
        printf("lw\t%s, %x(%s)\n", _r2, imm, _r1);
        printf("%s\n",getstrbits(x,16,16));
    }else

    if (opcode == 0x24)
    {
        if (r1 == -1 || r2 == -1)
            return 0;

        PRINT_ADDRESS("\t");
        printf("lbu\t%s, %x(%s)\n", _r2, imm, _r1);
    }else

    if (opcode == 0x25)
    {
        if (r1 == -1 || r2 == -1)
            return 0;

        PRINT_ADDRESS("\t");
        printf("lhu\t%s, %x(%s)\n", _r2, imm, _r1);
    }else

    if (opcode == 0x28)
    {
        if (r1 == -1 || r2 == -1)
            return 0;

        PRINT_ADDRESS("\t");
        printf("sb\t%s, %x(%s)\n", _r2, imm, _r1);
    }else

    if (opcode == 0x29)
    {
        if (r1 == -1 || r2 == -1)
            return 0;

        PRINT_ADDRESS("\t");
        printf("sh\t%s, %x(%s)\n", _r2, imm, _r1);
    }else

    if (opcode == 0x2b)
    {
        if (r1 == -1 || r2 == -1)
            return 0;

        PRINT_ADDRESS("\t");
        printf("sw\t%s, %x(%s)\n", _r2, imm, _r1);
    }else

    if (opcode == 0x31)
    {
        if (r1 == -1 || r2 == -1)
            return 0;

        PRINT_ADDRESS("\t");
        printf("lwc1\t%s, %x(%s)\n", _r2, imm, _r1);
    }else

    if (opcode == 0x39)
    {
        if (r1 == -1 || r2 == -1)
            return 0;

        PRINT_ADDRESS("\t");
        printf("swcl\t%s, %x(%s)\n", _r2, imm, _r1);
    }


}


void parse_r(uint_fast32_t x)
{
    unsigned char func = getnbits(x,6,6);

    char r1, r2, r3, sa;

    char _r1[4] = {0}, _r2[4] = {0}, _r3[4] = {0};


    sa = getnbits(x,11,5); //shift amount
    r3 = getnbits(x,16,5); //rd
    r2 = getnbits(x,21,5); //rt
    r1 = getnbits(x,26,5); //rs

    detect_register(_r1,&r1);
    detect_register(_r2,&r2);
    detect_register(_r3,&r3);



   if (func == 0) //sll
   {
       if ( r2 == -1 || r3 == -1) //check if invalid register
            return;
       PRINT_ADDRESS("\t");
       printf("sll\t%s, %s, 0x%x\n", _r3, _r2, sa);
   }

   if (func == 0x2) //sll
   {
       if ( r2 == -1 || r3 == -1) //check if invalid register
            return;
        PRINT_ADDRESS("\t");
       printf("srl\t%s, %s, 0x%x\n", _r3, _r2, sa);
   }

   if (func == 0x3) //sll
   {
       if ( r2 == -1 || r3 == -1) //check if invalid register
            return;

       PRINT_ADDRESS("\t");
       printf("sra\t%s, %s, 0x%x\n", _r3, _r2, sa);
   }

   if (func == 0x4) //sll
   {
       if ( r2 == -1 || r3 == -1 || r1 == -1) //check if invalid register
            return;

       PRINT_ADDRESS("\t");
       printf("sllv\t%s, %s, %s\n", _r3, _r2, _r1);
   }

   if (func == 0x6) //sll
   {
       if ( r2 == -1 || r3 == -1 || r1 == -1) //check if invalid register
            return;

       PRINT_ADDRESS("\t");
       printf("slrv\t%s, %s, %s\n", _r3, _r2, _r1);
   }

   if (func == 0x7) //sll
   {
       if ( r2 == -1 || r3 == -1 || r1 == -1) //check if invalid register
            return;

       PRINT_ADDRESS("\t");
       printf("srav\t%s, %s, %s\n", _r3, _r2, _r1);
   }

   if (func == 0x8) //sll
   {
       if (r1 == -1) //check if invalid register
            return;

       PRINT_ADDRESS("\t");
       printf("jr\t%s\n", _r1);
   }

   if (func == 0x9) //sll
   {
       if (r1 == -1 || _r3 == -1) //check if invalid register
            return;

       PRINT_ADDRESS("\t");
       printf("jalr\t%s, %s\n", _r3, _r1);
   }

   if (func == 0xc) //sll
   {
       PRINT_ADDRESS("\t");
       printf("syscall\n");
   }

   if (func == 0xd) //sll
   {
       PRINT_ADDRESS("\t");
       printf("break\n");
   }

   if (func == 0x10) //sll
   {
       if (r3 == -1) //check if invalid register
            return;

       PRINT_ADDRESS("\t");
       printf("mfhi\t%s\n", _r3);
   }

   if (func == 0x11) //sll
   {
       if (r1 == -1) //check if invalid register
            return;

       PRINT_ADDRESS("\t");
       printf("mthi\t%s\n", _r1);
   }

   if (func == 0x12) //sll
   {
       if (r3 == -1) //check if invalid register
            return;

       PRINT_ADDRESS("\t");
       printf("mflo\t%s\n", _r3);
   }

   if (func == 0x13) //sll
   {
       if (r1 == -1) //check if invalid register
            return;

       PRINT_ADDRESS("\t");
       printf("mtlo\t%s\n", _r1);
   }

   if (func == 0x18) //sll
   {
       if (r1 == -1 || r2 == -1) //check if invalid register
            return;

       PRINT_ADDRESS("\t");
       printf("mult\t%s, %s\n", _r1, _r2);
   }

   if (func == 0x19) //sll
   {
       if (r1 == -1 || r2 == -1) //check if invalid register
            return;

       PRINT_ADDRESS("\t");
       printf("multu\t%s, %s\n", _r1, _r2);
   }

   if (func == 0x1a) //sll
   {
       if (r1 == -1 || r2 == -1) //check if invalid register
            return;

       PRINT_ADDRESS("\t");
       printf("div\t%s, %s\n", _r1, _r2);
   }

   if (func == 0x1b) //sll
   {
       if (r1 == -1 || r2 == -1) //check if invalid register
            return;

       PRINT_ADDRESS("\t");
       printf("divu\t%s, %s\n", _r1, _r2);
   }

   if (func == 0x20) //sll
   {
       if (r1 == -1 || r2 == -1 || r3 == -1) //check if invalid register
            return;

       PRINT_ADDRESS("\t");
       printf("add\t%s, %s, %s\n", _r3 , _r1, _r2);
   }

   if (func == 0x21) //sll
   {
       if (r1 == -1 || r2 == -1 || r3 == -1) //check if invalid register
            return;

       PRINT_ADDRESS("\t");
       printf("addu\t%s, %s, %s\n", _r3 , _r1, _r2);
   }

   if (func == 0x22) //sll
   {
       if (r1 == -1 || r2 == -1 || r3 == -1) //check if invalid register
            return;

       PRINT_ADDRESS("\t");
       printf("sub\t%s, %s, %s\n", _r3 , _r1, _r2);
   }

   if (func == 0x23) //sll
   {
       if (r1 == -1 || r2 == -1 || r3 == -1) //check if invalid register
            return;

       PRINT_ADDRESS("\t");
       printf("subu\t%s, %s, %s\n", _r3 , _r1, _r2);
   }

   if (func == 0x24) //sll
   {
       if (r1 == -1 || r2 == -1 || r3 == -1) //check if invalid register
            return;

       PRINT_ADDRESS("\t");
       printf("and\t%s, %s, %s\n", _r3 , _r1, _r2);
   }

   if (func == 0x25) //sll
   {
       if (r1 == -1 || r2 == -1 || r3 == -1) //check if invalid register
            return;

       PRINT_ADDRESS("\t");
       printf("or\t%s, %s, %s\n", _r3 , _r1, _r2);
   }

   if (func == 0x26) //sll
   {
       if (r1 == -1 || r2 == -1 || r3 == -1) //check if invalid register
            return;

       PRINT_ADDRESS("\t");
       printf("xor\t%s, %s, %s\n", _r3 , _r1, _r2);

   }

   if (func == 0x27) //sll
   {
       if (r1 == -1 || r2 == -1 || r3 == -1) //check if invalid register
            return;

       PRINT_ADDRESS("\t");
       printf("nor\t%s, %s, %s\n", _r3 , _r1, _r2);
   }

   if (func == 0x2a) //sll
   {
       if (r1 == -1 || r2 == -1 || r3 == -1) //check if invalid register
            return;

       PRINT_ADDRESS("\t");
       printf("slt\t%s, %s, %s\n", _r3 , _r1, _r2);
   }

   if (func == 0x2b) //sll
   {
       if (r1 == -1 || r2 == -1 || r3 == -1) //check if invalid register
            return;

       PRINT_ADDRESS("\t");
       printf("sltu\t%s, %s, %s\n", _r3 , _r1, _r2);
   }



}


void parse_cop(uint_fast32_t x)
{
    unsigned char opcode, func, format;

    char r1, r2, r3;

    char _r1[4] = {0}, _r2[4] = {0}, _r3[4] = {0};

    format = getnbits(x,26,5);
    opcode = getnbits(x,32,6);
    func = getnbits(x,6,6);

    r1 = getnbits(x,11,5); //fd
    r2 = getnbits(x,16,5); //fs
    r3 = getnbits(x,21,5); //ft



    detect_register(_r1,&r1);
    detect_register(_r2,&r2);
    detect_register(_r3,&r3);









    if (opcode == 0x11)
    {
        if (func == 0)
        {
            if (r1 == -1 || r2 == -1 || r3 == -1)
                return;

            printf("adds\t%s, %s, %s", _r1, _r2, _r3);
        }

        if (func == 0x20)
        {
            if (r1 == -1 || r2 == -1)
                return;

            printf("cvt.s.w\t%s, %s", _r1, _r2);
        }




    }



}




int main(void)
{

    uint_fast32_t x;

    int counter = 0;
    FILE *fptr;

    fptr = fopen("/home/ali/Downloads/lsof","rb");




    while(1)
    {
        if (fread(&x,1, 4, fptr) == 0)
            break;

        address+=4;




        if (getnbits(x,32,6) == 0)
        {
            parse_r(x);
        }else

        if (getnbits(x,32,6) == 2)
        {
            PRINT_ADDRESS("\t");
            printf("j\t%x\n",getnbits(x,26,26));
        }else

        if (getnbits(x,32,6) == 3)
        {
            PRINT_ADDRESS("\t");
            printf("jal \t%x\n",getnbits(x,26,26));
        }else
        if (getnbits(x,32,6) == 0b010001 || getnbits(x,32,6) == 0b010000 || getnbits(x,32,6) == 0b010010 || getnbits(x,32,6) == 0b010011)
        {
            parse_cop(x);
        }else
            parse_i(x);


        if (address % 500 == 0)
            getchar();






    }
    fclose(fptr);
    return 0;
}


