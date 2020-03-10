#include <stdio.h>
#include <string.h>
#include "vault.h"

#define row 8
#define column 8
#define black 1
#define white 2
#define Size 80

int const Weight[Size] = {
    0, 99, -8, 8, 6, 6, 8, -8, 99, 0,

    0, -8, -24, -4, -3, -3, -4, -24, -8, 0,

    0, 8, -4, 7, 4, 4, 7, -4, 8, 0,

    0, 6, -3, 4, 0, 0, 4, -3, 6, 0,

    0, 6, -3, 4, 0, 0, 4, -3, 6, 0,

    0, 8, -4, 7, 4, 4, 7, -4, 8, 0,

    0, -8, -24, -4, -3, -3, -4, -24, -8, 0,

    0, 99, -8, 8, 6, 6, 8, -8, 99, 0};

void defineTable(int table[Size], char *argv[]);
void printTable(int table[Size]);
void copyTable(int table[Size], int table2[Size]);
int isPair(int square, int table[], int jump, int player);
int validSquares(int table[], int arrayOfValids[], int player);
void flip(int table[], int sqr, int jump, int player);
void doFlip(int table[], int sqr, int player);
int minimaxFirstlvl(int table[], int arrayOfValids[], int player, int depth);
int minimax(int table[], int depth, int player, int isMax, int isOver, int alpha, int beta);
int eval(const int table[Size], int player);

int da(int argc, char *argv[])
{

    int table[] = {
        //  0   1  2  3  4  5  6  7  8   9
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //0

        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //1

        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //2

        0, 0, 0, 0, 2, 1, 0, 0, 0, 0, //3

        0, 0, 0, 0, 1, 2, 0, 0, 0, 0, //4

        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //5

        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //6

        0, 0, 0, 0, 0, 0, 0, 0, 0, 0 //7
    };

    int arrayOfValids[row * column];

    // int const Player= argv[9][0]-48;
    // defineTable(table,argv);
    // int temp = validSquares(table,arrayOfValids,1);
    int minimax = minimaxFirstlvl(table, arrayOfValids, 1, 9);
    printf("%d %d", minimax % 10 - 1, minimax / 10);
    printTable(table);
    // for(int i=0;i<temp;i++){
    //     printf("%d\n",arrayOfValids[i]);
    //     int table2[Size];
    //     copyTable(table,table2);
    //     doFlip(table2,arrayOfValids[i],1);
    //     printTable(table2);
    // }
    // printTable(table);
    return 0;
}

///////////////////////////////// Table ///////////////////////////////////////

void defineTable(int table[Size], char *argv[])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 1; j < 9; j++)
        {
            table[i * 10 + j] = argv[i + 1][j - 1] - 48;
        }
    }
}

void printTable(int table[])
{
    puts("");
    printf("%s", "   ");
    for (int i = 0; i < column; i++)
        printf("%d ", i);
    puts("");
    for (int i = 0; i < row; i++)
    {
        printf("%d :", i);
        for (int j = 1; j < column + 1; j++)
        {
            printf("%d ", table[i * 10 + j]);
        }
        puts("");
    }
}

void copyTable(int table[Size], int table2[Size])
{
    for (int i = 0; i < Size; i++)
    {
        table2[i] = table[i];
    }
}

int isPair(int square, int table[], int jump, int player)
{
    if (table[square] != 0)
        return 0;
    int nextsqr = square + jump;
    do
    {
        square += jump;
    } while (table[square] == 3 - player);

    if (nextsqr != square && table[square] == player)
        return 1;
    else
        return 0;
}

int validSquares(int table[], int arrayOfValids[], int player)
{
    int counter = 0;
    for (int i = 0; i < Size; i++)
    {
        if (i % 10 == 0 || i % 10 == 9)
            continue;
        if (isPair(i, table, -11, player))
        {
            arrayOfValids[counter] = i;
            counter++;
        }
        else if (isPair(i, table, -10, player))
        {
            arrayOfValids[counter] = i;
            counter++;
        }
        else if (isPair(i, table, -9, player))
        {
            arrayOfValids[counter] = i;
            counter++;
        }
        else if (isPair(i, table, -1, player))
        {
            arrayOfValids[counter] = i;
            counter++;
        }
        else if (isPair(i, table, +1, player))
        {
            arrayOfValids[counter] = i;
            counter++;
        }
        else if (isPair(i, table, 9, player))
        {
            arrayOfValids[counter] = i;
            counter++;
        }
        else if (isPair(i, table, 10, player))
        {
            arrayOfValids[counter] = i;
            counter++;
        }
        else if (isPair(i, table, 11, player))
        {
            arrayOfValids[counter] = i;
            counter++;
        }
    }
    return counter;
}

void flip(int table[], int sqr, int jump, int player)
{
    if (isPair(sqr, table, jump, player))
    {
        sqr += jump;
        while (table[sqr] == 3 - player)
        {
            table[sqr] = player;
            sqr += jump;
        };
    }
}

void doFlip(int table[], int sqr, int player)
{
    flip(table, sqr, -11, player);
    flip(table, sqr, -10, player);
    flip(table, sqr, -9, player);
    flip(table, sqr, -1, player);
    flip(table, sqr, +1, player);
    flip(table, sqr, +9, player);
    flip(table, sqr, +10, player);
    flip(table, sqr, +11, player);
    table[sqr] = player;
}

int minimaxFirstlvl(int table[], int arrayOfValids[], int player, int depth)
{
    int numOfValidSqrs = validSquares(table, arrayOfValids, player);
    int bestEval = -2000, bestSqr;
    int alpha = -10000, beta = 10000;
    if (numOfValidSqrs == 0)
        return 0;
    for (int i = 0; i < numOfValidSqrs; i++)
    {
        int table2[Size];
        copyTable(table, table2);
        doFlip(table2, arrayOfValids[i], player);
        int temp = minimax(table2, depth - 1, player, 0, 0, alpha, beta);
        printf("%d\n", temp);
        if (temp > bestEval)
        {
            bestSqr = i;
            bestEval = temp;
        }
    }
    return arrayOfValids[bestSqr];
}

int minimax(int table[], int depth, int player, int isMax, int isOver, int alpha, int beta)
{
    if (depth == 0)
        return eval(table, player);
    if (isMax)
    {
        int *arrayOfValids = (int *)malloc(sizeof(int) * 64);
        int numOfValidSqrs = validSquares(table, arrayOfValids, player);
        if (numOfValidSqrs == 0 && isOver == 0)
            return minimax(table, depth, player, 0, 1, alpha, beta);
        if (numOfValidSqrs == 0 && isOver == 1)
            return eval(table, player);
        int bestEval = -2000;
        for (int i = 0; i < numOfValidSqrs; i++)
        {
            int table2[Size];
            copyTable(table, table2);
            doFlip(table2, arrayOfValids[i], player);
            int temp = minimax(table2, depth - 1, player, 0, 0, alpha, beta);
            bestEval = bestEval < temp ? temp : bestEval;
            // alpha = alpha>bestEval ? alpha : bestEval;
            // if(beta <= alpha)   break;
        }
        return bestEval;
        free(arrayOfValids);
    }
    else
    {
        int *arrayOfValids = (int *)malloc(sizeof(int) * 64);
        int numOfValidSqrs = validSquares(table, arrayOfValids, 3 - player);
        if (numOfValidSqrs == 0 && isOver == 0)
            return minimax(table, depth, player, 1, 1, alpha, beta);
        if (numOfValidSqrs == 0 && isOver == 1)
            return eval(table, player);
        int bestEval = 2000;
        for (int i = 0; i < numOfValidSqrs; i++)
        {
            int table2[Size];
            copyTable(table, table2);
            doFlip(table2, arrayOfValids[i], 3 - player);
            int temp = minimax(table2, depth - 1, player, 1, 0, alpha, beta);
            bestEval = bestEval > temp ? temp : bestEval;
            // beta = beta<bestEval ? beta : bestEval;
            // if(beta <= alpha)   break;
        }
        free(arrayOfValids);
        return bestEval;
    }
}

int eval(const int table[Size], int player)
{
    int count = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 1; j < column + 1; j++)
        {
            if (table[i * 10 + j] == player)
                count += Weight[i * 10 + j];
            else if (table[i * 10 + j] == 3 - player)
                count -= Weight[i * 10 + j];
        }
    }
    return count;
}

void open1(char *pass);
void open2(char *pass);
void open3(char *pass);
void open4(char *pass);

void check(char *pass)
{
    open1(pass);
}

void open1(char *pass)
{
    open2(pass);
}

void open2(char *pass)
{
    open3(pass);
}

void open3(char *pass)
{
    open4(pass);
}

void open4(char *pass)
{
    int code_arr[22] = {'C', 'T', 'F', '{', 'b', 'r', 'u', 't', 'e', '_', 'f', 'r', 'u', 'i', 't', 'f', '0', 'r', 'c', '3', '}', '\0'};
    int error_arr[12] = {'W', 'R', '0', 'N', 'G', '-', '_', '-', 'U', '$', '3', 'R'};
    int pass_arr[33] = {'0', 'c', 'f', 'c', '8', '9', 'c', 'a', 'f', 'b', 'c', '3', 'b', 'b', '5', 'd', 'f', '0', 'd', '1', 'e', '0', 'c', 'e', '8', '6', 'b', 'c', '5', '9', 'a', 'f', '\0'};
    char valid_pass[33];
    char code[21];
    char *fake_arr[] = {"e4d909c290d0fb1ca068ffaddf22cbd0",
                        "dd0c31d9fb083d6d3c6dd56fe793c76f",
                        "07f8e3784e3fdcbf1f97df48b2def65d",
                        "c4fed1bbac4cf5648ebb09958e15041e",
                        "97e63d460ad92c5f157819c36269a0bc",
                        "dd0c31d9fb083d6d3c6dd56fe793c76f",
                        "shwrhwswfb083d6d3c6dd56fe793c556",
                        "dabcddvsdgdgqwdwqehdd56fe793c76f",
                        "erfc31d9fb083d6d3c6dfbfdpgsac77k",
                        "dd0c31d9fb083d6d3c6dd56fe793c76j",
                        "bbnjk1d9fb083uhg8j6ddsdsfbs09u0n",
                        "d8e819daeb14874b74e12c87c26309ae"};

    for (size_t i = 0; i < 32; i++)
    {
        valid_pass[i] = pass_arr[i];
    }
    valid_pass[32] = '\0';
    if (strcmp(pass, valid_pass) == 0)
    {
        for (size_t i = 0; i < 21; i++)
        {
            code[i] = code_arr[i];
        }
        printf("%s", code);
        char *fake_arr[] = {
            "4d90e9casgasga1ca068ffaddf22sbvv",
            "d1eqwfw9fb083d6d3c6dd56qeggwgd34",
            "02422fgv4e3fdcbf1f97df48b2drbwsb",
        };
    }
    else
    {
        for (size_t i = 0; i < 12; i++)
        {
            code[i] = error_arr[i];
        }
        printf("%s", code);
        char *fake_arr[] = {
            "ejassfc290d0gw4gsdg8ffaddf2245he",
            "akesm1d9fb083d6d3c6ejanbe793c76f",
            "50eik3adgqemdcbf1f7df48beakgme32",
        };
    }
}