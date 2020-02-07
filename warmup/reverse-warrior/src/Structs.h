#ifndef A_H
#define A_H

enum Face
{
    EAST,
    WEST
};

typedef void (*Function)();

typedef struct Object
{
    int health;
    int maxHealth;
    char name[20];
    char character;
    int reward;
    int enemy;
    int bound;
    int locX;
    int locY;
    void (*run)(struct Object *);
    enum Face face;
} Object;

Object __warrior, wall, space, stairs;

typedef struct Level
{
    int timeBonus;
    int aceScore;
    int width;
    int height;
    int stairX;
    int stairY;
    int startX;
    int startY;
    int objsLength;
    Object *thisLevelsObjs[];
} Level;

struct Storage
{
    int health;
} notebook;

#endif