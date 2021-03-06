/*******************
File: New Sleep
Author: Supplied by Curtin University
Access Date: 16/10/2020
Unit: Unix and C Programming
*******************/
#define _DEFAULT_SOURCE
#include "newSleep.h"

void newSleep(float sec)
{
    struct timespec ts;
    ts.tv_sec = (int) sec;
    ts.tv_nsec = (sec - ((int) sec)) * 1000000000;
    nanosleep(&ts,NULL);
}
