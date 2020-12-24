#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "operation.h"

int main()
{
    while(1)
    {
        int32_t exit = 0;
        exit = menu();
        if(exit)
        {
            break;
        }
        char input[25] = {0};
        int32_t count = 0;
        fun1(input);
        for(int32_t i = 0 ; i < 25 ; i++)
        {
            if(input[i] != 0)
            {
                count ++;
            }
        }
        if(!checkError(input))
        {
            tran number[25];
            int32_t numcnt = 0;
            numcnt = transnum(input,number,count);
            tran stack[20];
            tran pofix_num[25];
            int32_t pofixnum = 0;
            printf("The postfix expression:");
            pofixnum = pofix(number,numcnt,stack,pofix_num);
            printf("\n=");
            double stack_double[20];
            count_ans(pofix_num,pofixnum,stack_double);
            Sleep(10000);
        }
    }
    return 0;
}