#ifndef EMSSYNTHETICPOWER
#define EMSSYNTHETICPOWER

#include <iostream>
#include <vector>
using namespace std;

vector<double> getSyntheticPower(vector<double> synWind, vector<double> v, vector<double> P)
{
    vector<double> synPower;
    int N = synWind.size();
    int len = v.size();
    for(int i=0; i<N; i++)
    {
        if(synWind[i]<v[0])
        {
            synPower.push_back(0);
        }
        if(synWind[i]>v[len-1])
        {
            synPower.push_back(0);
        }
        for(int j=0;j<len-1;j++)
        {
            if(synWind[i]>=v[j] && synWind[i]<=v[j+1])
            {
                synPower.push_back(P[j] + ((synWind[i]-v[j]) * ((P[j+1]-P[j])/(v[j+1]-v[j]))));
            }
        }
    }
    return synPower;
}
#endif // EMSSYNTHETICPOWER
