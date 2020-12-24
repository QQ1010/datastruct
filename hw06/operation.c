#include "operation.h"


char map[16] = {'0','1','2','3','4','5','6','7','8','9','(',')','+','*','/','-'};

int32_t menu()
{
    setbuf(stdin, NULL);
    system("cls");
    printf("------------------- 開始 ----------------\n");
    printf("Menu\n1.   輸入數學運算式\n(按esc鍵來結束程式)\n");
    printf("------------- 輸入1來進入指令1 ---------\n");
    printf(">");
    char skill;
    skill = getch();
    if(skill == 0x1b)
    {
        return 1;
    }
    system("cls");
}
void fun1(char input[25])
{
    
    printf("指令1：輸入數學運算式\n");
    printf("Please enter an infix expression and press enter:");
    scanf("%s",input);
}
int32_t checkError(char input[25])
{
    int32_t error = 0;
    //operations over 20      
    int32_t count = 0;
    for(int32_t i = 0 ; i < 25 ; i++)
    {
        if(input[i] != 0)
        {
            count ++;
        }
    }
    if(count > 20)
    {
        error = 1;
        printf("Error -line  contains  more characters than allowed.\n");
        Sleep(5000);
        return 1;
    }
    //Illegal character
    int32_t errorflag[20] = {0};
    for(int32_t i = 0 ; i < count ; i++)
    {
        for(int32_t j = 0 ; j < 16 ; j++)
        {
            if(input[i] == map[j])
            {
                errorflag[i] = 1;
            }
        }
        if(errorflag[i] != 1)
        {
            error = 1;
            printf("Illegal character\n");
            Sleep(5000);
            break;
        }
    }
    //First character an operation
    for(int32_t i = 0 ; i < 4 ; i++)
    {
        if(input[0] == map[12+i])
        {
            error = 1;
            printf("First character an operation\n");
            Sleep(5000);
            break;
        }
    }
    //Last character an operation
    for(int32_t i = 0 ; i < 4 ; i++)
    {
        if(input[count-1] == map[12+i])
        {
            error = 1;
            printf("Last character an operation\n");
            Sleep(5000);
            break;
        }
    }
    int32_t leftpare = 0;
    int32_t rightpare = 0;
    for(int32_t i = 0 ; i < count ; i++)
    {
        //Right parenthesis followd by an identifier
        if(input[i]  == map[11])
        {
            for(int32_t j = 0 ; j < 10 ; j++)
            {
                if(input[i+1] == map[j])
                {
                    error = 1;
                    printf("Right parenthesis followd by an identifier\n");
                    Sleep(5000);
                    break;
                }
            }
        }
        //Operator followed by an operator
        for(int32_t j = 0 ; j < 4 ; j++)
        {
            if(input[i] == map[12+j])
            {
                for(int32_t k = 0 ; k < 4 ; k++)
                {
                    if(input[i+1] == map[12+k])
                    {
                        error = 1;
                        printf("Operator followed by an operator\n");
                        Sleep(5000);
                        break;
                    }
                }
            }
        }
        //Left parenthesis followed by an operator ((-2) is legal)
        if(input[i] == map[10])
        {
            for(int32_t j = 0 ; j < 3 ; j++)
            {
                if(input[i+1] == map[12+j])
                {
                    error = 1;
                    printf("Left parenthesis followed by an operator\n");
                    Sleep(5000);
                    break;                
                }
            }
        }
        //Identifier followed by a left parenthesis
        for(int32_t j = 0 ; j < 10 ; j++)
        {
            if(input[i] == map[j])
            {
                if(input[i+1] == map[10])
                {
                    error = 1;
                    printf("Identifier followed by a left parenthesis\n");
                    Sleep(5000);
                    break;
                }
            }
        }
        //Right parenthesis followed by a left parenthesis
        if(input[i] == map[11] && input[i+1] == map[10])
        {
            error = 1;
            printf("Right parenthesis followed by a left parenthesis\n");
            Sleep(5000);
            break;
        }
        //Operator followed by a right parenthesis
        for(int32_t j = 0 ; j < 4 ; j++)
        {
            if(input[i] == map[12+j] && input[i+1] == map[11])
            {
                error = 1;
                printf("Operator followed by a right parenthesis\n");
                Sleep(5000);
                break;
            }
        }
        //Left parenthesis followed by a right parenthesis
        if(input[i] == map[10] && input[i+1] == map[11])
        {
            error = 1;
            printf("Left parenthesis followed by a right parenthesis\n");
            Sleep(5000);
            break;
        }
        //count left & right parenthesis
        if(input[i] == map[10])
        {
            leftpare += 1;
        }
        else if (input[i] == map[11])
        {
            rightpare += 1;
        }
    }
    //Unmatched left parenthesis
    if(leftpare > rightpare)
    {
        error = 1;
        printf("Unmatched left parenthesis\n");
        Sleep(5000);
    }
    //Unmatched right parenthesis
    if(leftpare < rightpare)
    {
        error = 1;
        printf("Unmatched right parenthesis\n");
        Sleep(5000);
    }
    return error;
}
int32_t transnum(char input[25],tran number[25],int32_t count)
{
    int32_t cnt = count;
    int32_t index = 0;
    for(int32_t i = 0 ; i <= count ; i++)
    {
        if(input[i] == map[10] && input[i+1] == map[15])     //(-2)
        {
            int32_t j = i+2;
            int32_t tmp = 0;
            while( 0 <= (input[j]-'0') && (input[j]-'0') <= 9)
            {
                tmp = tmp*10 + (input[j]-'0');
                j++;
            }
            tmp *= -1;
            number[index].data = tmp;
            number[index].operation = 0;
            index ++;
            i = j+1;
            cnt -= 3;
        }
        if( 0 <= (input[i]-'0') && (input[i]-'0') <= 9)    //0-9
        {
            int32_t j = i+1;
            int32_t tmp = (input[i]-'0');
            int32_t checkwhile = 0;
            while( 0 <= (input[j]-'0') && (input[j]-'0') <= 9)
            {
                tmp = tmp*10 + (input[j]-'0');
                j++;
                cnt --;
            }
            number[index].data = tmp;
            number[index].operation = 0;
            index ++;
            i = j;
        }
        for(int32_t j = 0 ; j < 6 ; j++)
        {
            if(input[i] == map[10+j])        //+-*/()
            {
                number[index].data = (input[i]-'0');
                number[index].operation = 1;
                index ++;
            }
        }
    }
    return cnt;
}
void push(int32_t *top,tran item,tran stack[20])
{
    stack[++(*top)] = item;
}
void pop(int32_t *top,tran stack[20])
{
    stack[(*top)--];
}
int32_t pofix(tran number[25],int32_t numcnt,tran stack[20],tran pofix_num[25])
{
    int32_t top = -1;
    int32_t cnt = 0;
    for(int32_t i = 0 ; i < numcnt ; i++)
    {
        if(number[i].operation == 0)
        {
            if(number[i].data >= 0)
            {
                pofix_num[cnt].data = number[i].data;
                pofix_num[cnt].operation = number[i].operation;
                cnt ++;
                printf("%d",number[i].data);
            }
            else
            {
                pofix_num[cnt].data = number[i].data;
                pofix_num[cnt].operation = number[i].operation;
                cnt ++;
                number[i].data *= -1;
                printf("(-%d)",number[i].data);
            }
            
        }
        if(number[i].operation == 1)
        {
            if(number[i].data == (map[13]-'0') || number[i].data == (map[14]-'0'))          //operator = */
            {
                while(stack[top].data == (map[13]-'0') || stack[top].data == (map[14]-'0'))
                {
                    pofix_num[cnt].data = stack[top].data;
                    pofix_num[cnt].operation = stack[top].operation;
                    cnt ++;
                    printf("%c",('0'+stack[top].data));
                    pop(&top,stack);
                }
                push(&top,number[i],stack);
            }
            else if(number[i].data == (map[12]-'0') || number[i].data == (map[15]-'0'))     //operator = +-
            {
                while(stack[top].data == (map[13]-'0') || stack[top].data == (map[14]-'0') || stack[top].data == (map[12]-'0') || stack[top].data == (map[15]-'0'))
                {
                    pofix_num[cnt].data = stack[top].data;
                    pofix_num[cnt].operation = stack[top].operation;
                    cnt ++;
                    printf("%c",('0'+stack[top].data));
                    pop(&top,stack);
                }
                push(&top,number[i],stack);
            }
            else if(number[i].data == (map[10]-'0'))
            {
                push(&top,number[i],stack);
            }
            else if(number[i].data == (map[11]-'0'))      //operator = )
            {
                while(stack[top].data != (map[10]-'0'))
                {
                    pofix_num[cnt].data = stack[top].data;
                    pofix_num[cnt].operation = stack[top].operation;
                    cnt ++;
                    printf("%c",('0'+stack[top].data));
                    pop(&top,stack);
                }
                pop(&top,stack);
            }
            
        }
        if(i == numcnt - 1)
        {
            while(top != -1)
            {
                pofix_num[cnt].data = stack[top].data;
                pofix_num[cnt].operation = stack[top].operation;
                cnt ++;
                printf("%c",('0' + stack[top].data));
                pop(&top,stack);
            }
        }
    }
    return cnt;
}
void push_double(int32_t *top,double input,double stack[20])
{
    stack[++(*top)] = input;
}
void pop_double(int32_t *top,double stack[20])
{
    stack[(*top)--];
}
void count_ans(tran number[25],int32_t numcnt,double stack[20])
{
    int32_t top = -1;
    for(int32_t i = 0 ; i <numcnt ; i++)
    {
       if(number[i].operation == 0)
        {
            push_double(&top,number[i].data,stack);
        }
        if(number[i].operation == 1)
        {
            double temp = 0;
            double result = 0;
            temp = stack[top];
            pop_double(&top,stack);
            if(number[i].data == (map[12]-'0'))
            {
                result = add_fun(stack[top],temp);
            }
            else if(number[i].data == (map[13]-'0'))
            {
                result = mult_fun(stack[top],temp);
            }
            else if(number[i].data == (map[14]-'0'))
            {
                result = div_fun(stack[top],temp);
            }
            else if(number[i].data == (map[15]-'0'))
            {
                result = sub_fun(stack[top],temp);
            }
            pop_double(&top,stack);
            push_double(&top,result,stack);
        }
    }
    printf("%.4lf",stack[top]);
}
double add_fun(double a,double b)
{
    double result = 0;
    result = a+b;
    return result;
}
double sub_fun(double a,double b)
{
    double result = 0;
    result = a-b;
    return result;
}
double mult_fun(double a,double b)
{
    double result = 0;
    result = a*b;
    return result;
}
double div_fun(double a,double b)
{
    double result = 0;
    result = a/b;
    return result;
}