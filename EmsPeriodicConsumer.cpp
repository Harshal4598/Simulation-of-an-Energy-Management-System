#ifndef EMSPERIODICCONSUMER
#define EMSPERIODICCONSUMER

#include "EmsConsumer.cpp"
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include "EmsRandom.cpp"

using namespace std;

class EmsPeriodicConsumer : public EmsConsumer
{
    double P_mean, P_amp;
    double T_period, T_offset;

public:

    EmsPeriodicConsumer(string ConsName, double meanConsPower, double ampConsPower, double period, double offset) : EmsConsumer(ConsName, 0.95*(meanConsPower-ampConsPower), 1.05*(meanConsPower+ampConsPower)){

        timestep = EmsTime_1s;
        P_mean = meanConsPower;
        P_amp = ampConsPower;
        T_period = period;
        T_offset = offset;

        PowerConsumed = 0;

        }

    virtual void forwardTo (double Time_to, EmsCompData* Data) override
    {
        double omega;

        if (currentTime > Time_to)
        {
            cout<<"EmsPeriodicConsumer.TimeForward called with time going backwards: " <<currentTime<<" "<<Time_to<<"\n";
            return;
        }

        if (currentTime == Time_to)
        {
            PowerConsumed=0;
            return;
        }

        omega=2*M_PI/T_period;

        PowerConsumed = P_mean - P_amp/omega/(Time_to - currentTime) * (cos(omega*(Time_to - T_offset)) - cos(omega*(currentTime - T_offset)));
        PowerConsumed *= EmsRandomInterval(1,0.05,0.95,1.05);

        currentTime = Time_to;
    };
};
#endif // EMSCONSUMERPERIODIC
