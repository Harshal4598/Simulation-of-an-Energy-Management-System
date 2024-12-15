#ifndef EMSSIMPLEBATTERY
#define EMSSIMPLEBATTERY

#include <iostream>
#include "EmsBattery.cpp"

using namespace std;

class EmsSimpleBattery : public EmsBattery
{
public:

    EmsSimpleBattery (string BatteryName, double EnergyCapacity, double MaxLoadingPower,
               double MaxUnloadingPower, double Efficiency): EmsBattery (BatteryName,EnergyCapacity, MaxLoadingPower, MaxUnloadingPower, Efficiency){}

    virtual void forwardTo (double Time_to, EmsCompData* Data) override
    {
        EmsBatteryData* myData;

        if (currentTime > Time_to)
        {
            cout<<"EmsSimpleBattery.TimeForward called with time going backwards: " <<currentTime<<" "<<Time_to<<"\n";
            return;
        }

        if (currentTime == Time_to)
        {
            CurrentPowerDemand = 0;
            return;
        }

        myData = dynamic_cast<EmsBatteryData*>(Data);
        if (myData == nullptr) {
            cout<<"EmsSimpleBattery.TimeForward called with Data member not inherited from EmsBatteryData."<<endl;
            return;
        }

        if(myData->PowerDemand > 0)
        {
            CurrentPowerDemand = myData->PowerDemand;
            if(myData->PowerDemand > Profile.maxUnloadingPower)
                CurrentPowerDemand = Profile.maxUnloadingPower;
            double energy = CurrentPowerDemand * (Time_to-currentTime);
            if (energy > EnergyStored)
                CurrentPowerDemand = EnergyStored / (Time_to-currentTime);
            EnergyStored-=CurrentPowerDemand*(Time_to-currentTime);
        }

        if(myData->PowerDemand < 0)
        {
            CurrentPowerDemand = myData->PowerDemand;
            if(myData->PowerDemand < -Profile.maxLoadingPower)
                CurrentPowerDemand = -Profile.maxLoadingPower;
            double energy = CurrentPowerDemand * (Time_to-currentTime);
            if (EnergyStored - energy > Profile.energyCapacity)
                CurrentPowerDemand = (EnergyStored - Profile.energyCapacity) / (Time_to-currentTime);
            EnergyStored-=CurrentPowerDemand*(Time_to-currentTime);
        }
        currentTime = Time_to;
    }
};

#endif // EMSSIMPLEBATTERY

