#ifndef EMSSYNTHETICWIND
#define EMSSYNTHETICWIND

#include <iostream>
#include <cmath>
#include <vector>
#include "EmsRandom.cpp"

using namespace std;

vector<double> getSyntheticWind(double T, int N, double V_mean, double kbar, double spec_a, double spec_b)
{
    double dt = T/N;
    double vWave[N];
    vector<double> vWind;

    for(int n=1; n<=N; n++)
    {
        vWave[n-1] = V_mean;
        double tn = dt*(n-1);

        for(int k=1; k<=N/2; k++)
        {
            double Chi_k = spec_a/(1+spec_b*(k-kbar)*(k-kbar));
            double Phi_k = EmsRandomInterval(M_PI, M_PI, 0, 2*M_PI);

            vWave[n-1]+= Chi_k * cos(2*M_PI*k/T*tn + Phi_k);
        }
        if(vWave[n-1]<=0)
        {
            vWave[n-1]=0;
        }
        vWind.push_back(vWave[n-1]);
    }
    return vWind;
}
//Code is used to generate synthetic wind speed data
/*int main()
{
    ofstream Result("WindData/Wind_7.5.csv");

    vector<double> vWind = getSyntheticWind(8760*EmsTime_1h, 8760*EmsTime_1h/(10*EmsTime_1min), 7.5, 50, 0.4, 0.00002);
    //getSyntheticPower(N,vWind,vPower);

    for(int i=0; i<8760*EmsTime_1h/(10*EmsTime_1min); i++)
    {
        Result<<i<<","<<vWind[i]<<endl;
    }
    Result.close();
}*/
#endif // EMSSYNTHETICWIND
