#ifndef EMSTYPES_H
#define EMSTYPES_H

using namespace std;

    double EmsTime;
    double EmsPower;

    const double EmsTime_1s   = 1;
    const double EmsTime_1min = 60;
    const double EmsTime_1h   = 60*60;

    const double EmsPower_1W = 1;
    const double EmsPower_1kW = 1000;

    const double EmsEnergy_1kWh = EmsTime_1h*EmsPower_1kW;

#endif // EMSTYPES_H

