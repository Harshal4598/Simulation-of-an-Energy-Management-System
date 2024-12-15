#ifndef EMSCOMPONENT
#define EMSCOMPONENT
#include "EmsTypes.cpp"
#include <string>
using namespace std;

class EmsCompData
{
public:
    EmsCompData(int dummy){};

    virtual ~EmsCompData(){};
};

class EmsComponent
{
    protected:
        string name;
        double currentTime, timestep;

    public:

        virtual void forwardTo (double Time_to, EmsCompData* Data)=0;
        EmsComponent(string Name)
        {
            name = Name;
            currentTime = 0;
            timestep = -1;
        }
        string getName()
        {
            return name;
        }
};

#endif // EMSCOMPONENT


