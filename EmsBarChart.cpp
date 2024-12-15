#ifndef EMSBARCHART
#define EMSBARCHART

#include <iostream>
#include <cmath>

using namespace std;

class EmsBarChart
{
private:

    double barValue;
    char a = 219;
    double Min, Max;
    string Name;
    int Space;

public:

    int percentage;
    string getName()
    {
        return Name;
    }
    string getBarString(double barValue)
    {
        if(barValue<Min || barValue>Max)
        {
            cout<<"-----Invalid Value!-----";
            return "";
        }
        double val = (barValue-Min)/(Max-Min) * Space;
        percentage = round((barValue-Min)/(Max-Min) * 100);
        int length = round(val);
        string result = "";

        for(int i=0; i<length;i++)
        {
            result+=a;
        }
        for(int i=length; i<Space;i++)
        {
            result+="_";
        }
        return result;
    }

    EmsBarChart (string Bar,int space, double min, double max)
    {
        Min=0;
        Max=-1;
        Space = 0;
        if(min>max)
        {
            cout<<"EmsBarChart "<<Bar<<"Invalid input: min = "<<min<<" and max = "<<max;
            return;
        }
        if(space<=0)
        {
            cout<<"EmsBarChart "<<Bar<<"space should be at least 1.";
            return;
        }
        Min=min;
        Max=max;
        Name = Bar;
        Space = space;
    }
};
#endif // EMSBARCHART

