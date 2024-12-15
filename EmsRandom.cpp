#ifndef EMSRANDOM
#define EMSRANDOM
#include <iostream>
#include <ctime>

using namespace std;

double EmsRandomInterval (double average, double spread, double MIN, double MAX)
{
    double num;

    do{num = average-spread + (((double)rand()/RAND_MAX)*2*spread);}
    while(num<MIN || num>MAX);

    return num;
}
#endif // EMSRANDOM
