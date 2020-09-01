// Tower of Hanoi
#include <iostream>
#include <stdlib.h>
#include <windows.h>     // "Used to function gotoRowColumn

using namespace std;

typedef int stack_element;

// Stack construction
#include "stack.h"

// Prototypes of function used in the main

// Prototypes of stack function
void initStack               (Stack &);
void push                    (Stack &, stack_element);
stack_element pop            (Stack &);
stack_element top            (Stack);
int isEmpty                  (Stack);
int amountOfDisksIntower     (Stack &);
void error                   (int);

// Prototypes of function used in the game
void insertDisksInTower(Stack &, int *);
void printHeader();
void printTowersAndDisks(Stack &, Stack &, Stack &, int, int);
void analyzeTransfertower_1_And_tower_2(Stack &, Stack &, int *);
void analyzeTransfertower_1_And_tower_3(Stack &, Stack &, int *);
void analyzeTransfertower_2_And_tower_3(Stack &, Stack &, int *);
void gotoRowColumn (int, int);

int main()
{
    Stack tower_1, tower_2, tower_3;
    int amountOfDisks = 0, amountOfMovements = 0, movements = 0;

    initStack(tower_1);
    initStack(tower_2);
    initStack(tower_3);

    printHeader();
    insertDisksInTower(tower_1, &amountOfDisks);
    printTowersAndDisks(tower_1, tower_2, tower_3, amountOfMovements, amountOfDisks);

    /* There is difference in next movements, depending on amount of disks (ODD and EVER), for always the algorithm be 2^n-1. */
    /* Need to put all the disks, minus the biggest in tower 3 */
    if(amountOfDisks % 2 != 0 && amountOfDisks < 10)
    {
        /* If is Odd, starting with tower 2 less than 10 */
        while(amountOfDisksIntower(tower_2) < amountOfDisks)
        {
            movements = amountOfMovements;
            analyzeTransfertower_1_And_tower_2(tower_1, tower_2, &amountOfMovements);

            if(movements != amountOfMovements)
                printTowersAndDisks(tower_1, tower_2, tower_3, amountOfMovements, amountOfDisks);

            if(amountOfDisksIntower(tower_2) == amountOfDisks) // Verifica se atingiu o objtivo do jogo
                break; // Sair do while

            movements = amountOfMovements;
            analyzeTransfertower_1_And_tower_3(tower_1, tower_3, &amountOfMovements);

            if(movements != amountOfMovements)
                printTowersAndDisks(tower_1, tower_2, tower_3, amountOfMovements, amountOfDisks);

            if(amountOfDisksIntower(tower_2) == amountOfDisks)
                break; // Sair do while

            movements = amountOfMovements;
            analyzeTransfertower_2_And_tower_3(tower_2, tower_3, &amountOfMovements);

            if(movements != amountOfMovements)
                printTowersAndDisks(tower_1, tower_2, tower_3, amountOfMovements, amountOfDisks);
        }
    }
    else
    {
        if(amountOfDisks % 2 != 0)
        {
            /* If is Odd, starting with tower 2 and big than 10 */
            while(amountOfDisksIntower(tower_2) < amountOfDisks)
            {
                analyzeTransfertower_1_And_tower_2(tower_1, tower_2, &amountOfMovements);
                if(amountOfDisksIntower(tower_2) == amountOfDisks) // Verifica se atingiu o objtivo do jogo
                    break; // Sair do while

                analyzeTransfertower_1_And_tower_3(tower_1, tower_3, &amountOfMovements);
                if(amountOfDisksIntower(tower_2) == amountOfDisks)
                    break; // Sair do while

                analyzeTransfertower_2_And_tower_3(tower_2, tower_3, &amountOfMovements);
            }
        }
        else
        {
            if(amountOfDisks < 10)
            {
                /* If is Even, starting with tower 3 less than 10 */
                while(amountOfDisksIntower(tower_2) < amountOfDisks)
                {
                    movements = amountOfMovements;
                    analyzeTransfertower_1_And_tower_3(tower_1, tower_3, &amountOfMovements);

                    if(movements != amountOfMovements)
                        printTowersAndDisks(tower_1, tower_2, tower_3, amountOfMovements, amountOfDisks);

                    if(amountOfDisksIntower(tower_2) == amountOfDisks)
                        break;

                    movements = amountOfMovements;
                    analyzeTransfertower_1_And_tower_2(tower_1, tower_2, &amountOfMovements);

                    if(movements != amountOfMovements)
                        printTowersAndDisks(tower_1, tower_2, tower_3, amountOfMovements, amountOfDisks);

                    if(amountOfDisksIntower(tower_2) == amountOfDisks)
                        break;

                    movements = amountOfMovements;
                    analyzeTransfertower_2_And_tower_3(tower_2, tower_3, &amountOfMovements);

                    if(movements != amountOfMovements)
                        printTowersAndDisks(tower_1, tower_2, tower_3, amountOfMovements, amountOfDisks);
                }
            }
            else
            {
                /* If is EVER, starting with tower 2 and big than 10 */
                while(amountOfDisksIntower(tower_2) < amountOfDisks)
                {
                    analyzeTransfertower_1_And_tower_3(tower_1, tower_3, &amountOfMovements);
                    if(amountOfDisksIntower(tower_2) == amountOfDisks)
                        break;

                    analyzeTransfertower_1_And_tower_2(tower_1, tower_2, &amountOfMovements);
                    if(amountOfDisksIntower(tower_2) == amountOfDisks)
                        break;

                    analyzeTransfertower_2_And_tower_3(tower_2, tower_3, &amountOfMovements);
                }
            }
        }
    }

        cout << "The minimum number of moves with " << amountOfDisks << " disks is: " << amountOfMovements << endl << endl << endl;

        return 0;
    }

    /* Put the amount of disk in tower */
    void insertDisksInTower(Stack &tower, int *amountOfDisks)
    {
        int counter;

        printf("      \332\304\304");

        for(counter=0; counter<5; counter++)
            printf("\304\304\304\304\304\304");

        printf("\304\277 \n      \263 ENTER THE AMOUNT OF DISKS:      \263 \n      \300\304");

        for(counter=0; counter<5; counter++)
            printf("\304\304\304\304\304\304");

        printf("\304\304\331 \n");

        gotoRowColumn(4, 35);

        scanf("%d", amountOfDisks);

        for(counter = *amountOfDisks; counter > 0; counter--)
            push(tower, counter);

        gotoRowColumn(7, 0);
    }

// Print header of game
    void printHeader ()
    {
        int counter=0;

        printf("\t    \332");

        for(counter=0; counter<5; counter++)
            printf("\304\304\304\304");

        printf("\304\277 \n \t    \263 PLAY TOWER OF HANOI \263 \n \t    \300\304");

        for(counter=0; counter<5; counter++)
            printf("\304\304\304\304");

        printf("\331 \n");
    }

// print struct towers and disks
    void printTowersAndDisks(Stack & tower_1, Stack & tower_2, Stack & tower_3, int movements, int amountOfDisks)
    {
        int counter=0, matPrint[amountOfDisks][3] = {0}, row;
        Stack towerAuxiliary_1, towerAuxiliary_2, towerAuxiliary_3;
        stack_element disk;

        initStack(towerAuxiliary_1);
        initStack(towerAuxiliary_2);
        initStack(towerAuxiliary_3);

        while(!isEmpty(tower_1))
        {
            disk=pop(tower_1);
            push(towerAuxiliary_1, disk);
        }
        while(!isEmpty(tower_2))
        {
            disk=pop(tower_2);
            push(towerAuxiliary_2, disk);
        }
        while(!isEmpty(tower_3))
        {
            disk=pop(tower_3);
            push(towerAuxiliary_3, disk);
        }

        printf("\n");

        for(counter=0; counter<amountOfDisks; counter++)
            printf("\t\t \263   \263   \263   \263 \n");

        printf("\t\t \300\304\304\304\301\304\304\304\301\304\304\304\331");

        if(movements == 0)
            row=7;
        else
            row = movements*(amountOfDisks+4)+7;

        for(counter=0; counter<amountOfDisks; counter++)
        {
            if(!isEmpty(towerAuxiliary_1))
            {
                gotoRowColumn(amountOfDisks+row-counter, 19);
                disk = pop(towerAuxiliary_1);
                push(tower_1, disk);
                printf("%d\n", disk);
            }
            if(!isEmpty(towerAuxiliary_2))
            {
                gotoRowColumn(amountOfDisks+row-counter, 23);
                disk = pop(towerAuxiliary_2);
                push(tower_2, disk);
                printf("%d\n", disk);
            }
            if(!isEmpty(towerAuxiliary_3))
            {
                gotoRowColumn(amountOfDisks+row-counter, 27);
                disk = pop(towerAuxiliary_3);
                push(tower_3, disk);
                printf("%d\n", disk);
            }
        }

        gotoRowColumn(row+amountOfDisks+3, 0);
    }

    /* Analyze transfer between tower 1 and tower 2 or tower 2 and tower 1 */
    void analyzeTransfertower_1_And_tower_2(Stack &tower_1, Stack &tower_2, int *amountOfMovements)
    {
        stack_element disk;
        int movements=0;

        if(isEmpty(tower_1) && !isEmpty(tower_2))
        {
            disk = pop(tower_2);
            push(tower_1, disk);
            cout << *amountOfMovements+1 << " - Moving the disk " << disk << " from tower B, to tower A" << endl;
            movements++;
        }
        else
        {
            if(isEmpty(tower_2)&& !isEmpty(tower_1))
            {
                disk = pop(tower_1);
                push(tower_2, disk);
                cout << *amountOfMovements+1 << " - Moving the disk " << disk << " from tower A, to tower B" << endl;
                movements++;
            }
            else
            {
                if(top(tower_1) < top(tower_2) && !isEmpty(tower_1))
                {
                    disk = pop(tower_1);
                    push(tower_2, disk);
                    cout << *amountOfMovements+1 << " - Moving the disk " << disk << " from tower A, to tower B" << endl;
                    movements++;
                }
                else
                {
                    if(top(tower_2) < top(tower_1) && !isEmpty(tower_2))
                    {
                        disk = pop(tower_2);
                        push(tower_1, disk);
                        cout << *amountOfMovements+1 << " - Moving the disk " << disk << " from tower B, to tower A" << endl;
                        movements++;
                    }
                }
            }
        }
        *amountOfMovements += movements;
    }

    /* Analyze transfer between tower 1 and tower 3 or tower 3 and tower 1 */
    void analyzeTransfertower_1_And_tower_3(Stack &tower_1, Stack &tower_3, int *amountOfMovements)
    {
        stack_element disk;
        int movements = 0;

        if(isEmpty(tower_1) && !isEmpty(tower_3))
        {
            disk = pop(tower_3);
            push(tower_1, disk);
            cout << *amountOfMovements+1 << " - Moving the disk " << disk << " from tower C, to tower A" << endl;
            movements++;
        }
        else
        {
            if(isEmpty(tower_3) && !isEmpty(tower_1))
            {
                disk = pop(tower_1);
                push(tower_3, disk);
                cout << *amountOfMovements+1 << " - Moving the disk " << disk << " from tower A, to tower C" << endl;
                movements++;
            }
            else
            {
                if(top(tower_1) < top(tower_3) && !isEmpty(tower_1))
                {
                    disk = pop(tower_1);
                    push(tower_3, disk);
                    cout << *amountOfMovements+1 << " - Moving the disk " << disk << " from tower A, to tower C" << endl;
                    movements++;
                }
                else
                {
                    if(top(tower_3) < top(tower_1) && !isEmpty(tower_3))
                    {
                        disk = pop(tower_3);
                        push(tower_1, disk);
                        cout << *amountOfMovements+1 << " - Moving the disk " << disk << " from tower C, to tower A" << endl;
                        movements++;
                    }
                }
            }
        }
        *amountOfMovements += movements;
    }

    /* Analyze transfer between tower 2 and tower 3 or tower 3 and tower 2 */
    void analyzeTransfertower_2_And_tower_3(Stack &tower_2, Stack &tower_3, int *amountOfMovements)
    {
        stack_element disk;
        int movements = 0;

        if(isEmpty(tower_3) && !isEmpty(tower_2))
        {
            disk = pop(tower_2);
            push(tower_3, disk);
            cout << *amountOfMovements+1 << " - Moving the disk " << disk << " from tower B, to tower C" << endl;
            movements++;
        }
        else
        {
            if(isEmpty(tower_2) && !isEmpty(tower_3))
            {
                disk = pop(tower_3);
                push(tower_2, disk);
                cout << *amountOfMovements+1 << " - Moving the disk " << disk << " from tower C, to tower B" << endl;
                movements++;
            }
            else
            {
                if(top(tower_3) < top(tower_2) && !isEmpty(tower_3))
                {
                    disk = pop(tower_3);
                    push(tower_2, disk);
                    cout << *amountOfMovements+1 << " - Moving the disk " << disk << " from tower C, to tower B" << endl;
                    movements++;
                }
                else
                {
                    if(top(tower_2) < top(tower_3)&& !isEmpty(tower_2))
                    {
                        disk = pop(tower_2);
                        push(tower_3, disk);
                        cout << *amountOfMovements+1 << " - Moving the disk " << disk << " from tower B, to tower C" << endl;
                        movements++;
                    }
                }
            }
        }
        *amountOfMovements += movements;
    }

// Used to print and position rows and Columns
    void gotoRowColumn(int Row, int Column)
    {
        HANDLE saida;

        COORD posicao;

        saida = GetStdHandle(STD_OUTPUT_HANDLE);

        posicao.X = Column;
        posicao.Y = Row;

        SetConsoleCursorPosition(saida, posicao);
    }
