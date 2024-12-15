#ifndef EMSGRID
#define EMSGRID

#include "EmsComponent.cpp"
#include <iostream>

using namespace std;

struct EmsGridProfile
{
    double MaxIntoPower, MaxOutOfPower;
};

class EmsGridData : public EmsCompData
{
public:
    double IntoPower;
    double OutOfPower;

public:

    EmsGridData (double intoPower, double outOfPower) : EmsCompData(0)
    {
        IntoPower = intoPower;
        OutOfPower = outOfPower;
    }

    virtual ~EmsGridData(){};
};

class EmsGrid : public EmsComponent
{

protected:

    double PowerInto, PowerOutOf;
    EmsGridProfile Profile;

public:

    double getPowerInto()
    {
      return PowerInto;
    }
    double getPowerOutOf()
    {
      return PowerOutOf;
    }

    void setProfile(double MaxIntoPower, double MaxOutOfPower)
    {
        Profile.MaxIntoPower = MaxIntoPower;
        Profile.MaxOutOfPower = MaxOutOfPower;
    }

    EmsGridProfile getProfile()
    {
        return Profile;
    }

    virtual void forwardTo (double Time_to, EmsCompData* Data) override
    {

        EmsGridData* myData;

        if (currentTime > Time_to)
        {
            cout<<"EmsGrid.TimeForward called with time going backwards: " <<currentTime<<" "<<Time_to<<"\n";
            return;
        }

        if (currentTime == Time_to)
        {
            PowerInto=0;
            PowerOutOf=0;
            return;
        }

        myData = dynamic_cast<EmsGridData*>(Data);
        if (myData == nullptr) {
            cout<<"EmsGrid.TimeForward called with Data member not inherited from EmsGridData."<<endl;
            return;
        }

        if(myData->IntoPower > Profile.MaxIntoPower)
        {
            cout<<"More Power "<<myData->IntoPower/EmsPower_1kW<<"kW put into grid "<<name<<" than possible: "<<Profile.MaxIntoPower/EmsPower_1kW<<"kW."<<endl;
            PowerInto=Profile.MaxIntoPower;
        }
        else{
            PowerInto=myData->IntoPower;
        }

        if(myData->OutOfPower>Profile.MaxOutOfPower)
        {
            cout<<"More Power "<<myData->OutOfPower/EmsPower_1kW<<"kW requested out of grid "<<name<<" than possible: "<<Profile.MaxOutOfPower/EmsPower_1kW<<"kW."<<endl;
            PowerOutOf=Profile.MaxOutOfPower;
        }
        else{
            PowerOutOf=myData->OutOfPower;
        }

        currentTime = Time_to;
    };

    EmsGrid (string GridName, double maxIntoPower, double maxOutOfPower) : EmsComponent(GridName)
    {
        setProfile(maxIntoPower, maxOutOfPower);
        PowerInto = 0;
        PowerOutOf = 0;
        timestep = EmsTime_1s;
    }
};

#endif // EMSGRID
