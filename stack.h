/*
 stack.h
 Elaboration of this library for the game Tower of Hanoi
 Created by Murilo Araujo on 23/08/2020.
 Copyright © 2020 Murilo Araujo. All rights reserved.
*/

#ifndef Stack

#include <iostream>
#include <stdlib.h>

using namespace std;

// Creation of stack
struct no {
    stack_element info;
    no * next;
};

struct Stack {
    no * top;
};

// Prototype of functions for stack
void initStack               (Stack&);
void push                    (Stack&, stack_element);
stack_element pop            (Stack&);
stack_element top            (Stack);
int isEmpty                  (Stack);
int amountOfDisksIntower (Stack &);
void error                   (int);

/* Initializes the stack (tower) "NULL" */
void initStack(Stack &p)
{
    p.top= NULL;
}

/* New no of stack*/
no* novo_no()
{
    no* novo;
    novo = new no;
    if (!novo)
        error(1);
    return novo;
}

/* Insert a disk in tower */
void push(Stack &p, stack_element a)
{
    no * novo = novo_no();
    novo->info = a;
    novo->next = p.top;
    p.top = novo;
}

/* Remove a disk of tower */
stack_element pop (Stack& stack){
    if(stack.top == NULL)
        error (2);
    stack_element auxiliary = stack.top ->info;
    no * elementoExcluir = stack.top;
    stack.top = (stack.top)->next;
    delete elementoExcluir;
    return auxiliary;
}

/* Return disk of top in tower */
stack_element top (Stack stack)
{
    if(stack.top == NULL)
        error(2);
    return (stack.top) ->info;
}

/* Se stack is empty, return 1 (true), because different of zero*/
int isEmpty(Stack stack)
{
    if (stack.top == NULL)
        return 1;
    else
        return 0;
}

/* Return amount of disk in tower */
int amountOfDisksIntower(Stack &tower)
{
    Stack towerAuxiliary;
    initStack(towerAuxiliary);
    stack_element disk;
    int disks=0;

    while(!isEmpty(tower))
    {
        disk = pop(tower);
        push(towerAuxiliary, disk);
        disks++;
    }

    while(!isEmpty(towerAuxiliary))
    {
        disk = pop(towerAuxiliary);
        push(tower, disk);
    }

    return disks;
}

/* Mensagem de erro */
void error(int i)
{
    switch(i)
    {
    case 1:
        cerr<< " OVERFLOW ";
        exit(1);
    case 2:
        cerr<< " UNDERFLOW ";
        exit(1);
    }
}

#endif /* stack.h */
