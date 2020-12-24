#pragma once

#include <math.h>
#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdint.h>
#include <string.h>

typedef struct _tran{
    int32_t data;
    int32_t operation;
}tran;

int32_t menu();
void fun1(char input[25]);
int32_t checkError(char input[25]);
int32_t transnum(char input[25],tran number[25],int32_t count);
void push(int32_t *top,tran item,tran stack[20]);
void pop(int32_t *top,tran stack[20]);
int32_t pofix(tran number[25],int32_t numcnt,tran stack[20],tran pofix_num[25]);
void push_double(int32_t *top,double input,double stack[20]);
void pop_double(int32_t *top,double stack[20]);
void count_ans(tran number[25],int32_t numcnt,double stack[20]);
double add_fun(double a,double b);
double sub_fun(double a,double b);
double mult_fun(double a,double b);
double div_fun(double a,double b);