#ifndef EMSCONSUMER
#define EMSCONSUMER

#include "EmsComponent.cpp"
#include <iostream>

using namespace std;

struct EmsConsumerProfile
{
    double MinConsPower, MaxConsPower;
};

class EmsConsumer : public EmsComponent
{
protected:

    double PowerConsumed;
    EmsConsumerProfile Profile;

public:

    double getPower()
    {
      return PowerConsumed;
    }

    void setProfile(double MinConsPower, double MaxConsPower)
    {
        Profile.MinConsPower = MinConsPower;
        Profile.MaxConsPower = MaxConsPower;
    }

    EmsConsumerProfile getProfile()
    {
        return Profile;
    }

    virtual void forwardTo (double Time_to, EmsCompData* Data) override =0;

    EmsConsumer (string ConsName, double minConsPower, double maxConsPower): EmsComponent (ConsName)
    {
        setProfile (minConsPower, maxConsPower);
        PowerConsumed = minConsPower;
    }
};
#endif // EMSCONSUMER

