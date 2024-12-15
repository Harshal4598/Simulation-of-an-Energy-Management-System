#ifndef EMSPRODUCER
#define EMSPRODUCER

#include "EmsComponent.cpp"
#include <iostream>

using namespace std;

struct EmsProducerProfile
{
    double MinProdPower, MaxProdPower;
};

class EmsProducer : public EmsComponent
{
protected:

    double PowerProduced;
    EmsProducerProfile Profile;

public:

    double getPower()
    {
      return PowerProduced;
    }

    void setProfile(double MinProdPower, double MaxProdPower)
    {

        Profile.MinProdPower = MinProdPower;
        Profile.MaxProdPower = MaxProdPower;
    }

    EmsProducerProfile getProfile()
    {
        return Profile;
    }

    virtual void forwardTo (double Time_to, EmsCompData* Data) override =0;

    EmsProducer (string ProdName, double minProdPower, double maxProdPower): EmsComponent (ProdName)
    {
        setProfile (minProdPower, maxProdPower);
        PowerProduced = minProdPower;
    }
};
#endif // EMSPRODUCER
