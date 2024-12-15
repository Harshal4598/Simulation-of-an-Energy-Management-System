#ifndef EMSBATTERY
#define EMSBATTERY

#include <iostream>
#include "EmsComponent.cpp"

using namespace std;

struct EmsBatteryProfile
{
    double energyCapacity, maxLoadingPower, maxUnloadingPower, efficiency;
};

class EmsBatteryData : public EmsCompData
{
public:
    double PowerDemand;

public:

    EmsBatteryData (double powerDemand) : EmsCompData(0)
    {
        PowerDemand = powerDemand;
    }

    virtual ~EmsBatteryData(){};
};

class EmsBattery : public EmsComponent
{
protected:

    double EnergyStored, CurrentPowerDemand;
    EmsBatteryProfile Profile;

public:

    double getEnergy()
    {
      return EnergyStored;
    }

    double getCurrentPowerProvided()
    {
      return CurrentPowerDemand;
    }

    void setProfile(double EnergyCapacity, double MaxLoadingPower, double MaxUnloadingPower,
                    double Efficiency)
    {
        Profile.energyCapacity = EnergyCapacity;
        Profile.maxLoadingPower = MaxLoadingPower;
        Profile.maxUnloadingPower = MaxUnloadingPower;
        Profile.efficiency = Efficiency;
    }

    EmsBatteryProfile getProfile()
    {
        return Profile;
    }

    virtual void forwardTo (double Time_to, EmsCompData* Data) override =0;

    EmsBattery (string BatteryName, double EnergyCapacity, double MaxLoadingPower,
                double MaxUnloadingPower, double Efficiency): EmsComponent (BatteryName)
    {
        setProfile (EnergyCapacity, MaxLoadingPower, MaxUnloadingPower, Efficiency);
        EnergyStored = Profile.energyCapacity/2; //chnage the capacity here
        CurrentPowerDemand = 0;
    }
};

#endif // EMSBATTERY
