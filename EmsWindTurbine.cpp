#ifndef EMSWINDTURBINE
#define EMSWINDTURBINE

#include <iostream>
#include <vector>
#include "EmsProducer.cpp"
#include "EmsSyntheticPower.cpp"
using namespace std;

class EmsWindTurbine : public EmsProducer
{
protected:

    vector<double>powerCurve_V;
    vector<double>powerCurve_P;
    vector<double>windSpeed;
    double windSpeedTimeStep;

public:

    vector<double> currentSpeed;
    EmsWindTurbine(string Name, vector<double>PC_V, vector<double>PC_P, vector<double>vWind, double WSTimeStep) : EmsProducer(Name,0,0)
    {
        powerCurve_V=PC_V;
        powerCurve_P=PC_P;
        windSpeed=vWind;
        windSpeedTimeStep=WSTimeStep;

        if(powerCurve_P.size()!=powerCurve_V.size())
        {
            cout<<"Error in Power Curve";
            exit(100);
        }


        double currentMax=0;
        for(int i=0; i<powerCurve_V.size(); i++)
        {
            if(powerCurve_P[i]>currentMax)
            {
                currentMax = powerCurve_P[i];
            }
        }
        setProfile(0,currentMax);
    }
    virtual void forwardTo (double Time_to, EmsCompData* Data) override
    {
        if (currentTime > Time_to)
        {
            cout<<"EmsWindTurbine.TimeForward called with time going backwards: " <<currentTime<<" "<<Time_to<<"\n";
            return;
        }

        if (currentTime == Time_to)
        {
            PowerProduced=0;
            return;
        }

        int currentInterval = currentTime/windSpeedTimeStep;
        int Time_toInterval = Time_to/windSpeedTimeStep;

        vector<double> currentWindSpeed;
        for(int i=currentInterval; i<=Time_toInterval; i++)
        {
            currentWindSpeed.push_back(windSpeed[i]);
        }currentSpeed = currentWindSpeed;
        vector<double> currentWindPower = getSyntheticPower(currentWindSpeed, powerCurve_V, powerCurve_P);

        if(currentInterval==Time_toInterval)
        {
            PowerProduced = currentWindPower[0];
            currentTime = Time_to;
            return;
        }

        double EnergyProduced =currentWindPower[0] * ((currentInterval+1) * windSpeedTimeStep - currentTime);
        for(int i=currentInterval+1; i<Time_toInterval; i++)
        {
            EnergyProduced+=currentWindPower[i-currentInterval]*windSpeedTimeStep;
        }
        EnergyProduced += currentWindPower[Time_toInterval-currentInterval]*(Time_to-Time_toInterval*windSpeedTimeStep);
        PowerProduced = EnergyProduced/(Time_to - currentTime);
        currentTime = Time_to;
    }

};


#endif // EMSWINDTURBINE
