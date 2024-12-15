#include <iostream>
#include "windows.h"
#include <fstream>
#include <iomanip>
#include <vector>

#include "EmsTypes.cpp"
#include "EmsComponent.cpp"
#include "EmsProducer.cpp"
#include "EmsConsumer.cpp"
#include "EmsGrid.cpp"
#include "EmsSimpleBattery.cpp"

#include "EmsSyntheticWind.cpp"
#include "EmsSyntheticPower.cpp"
#include "EmsWindTurbine.cpp"
#include "EmsReadWind.cpp"
#include "EmsReadPowerCurve.cpp"
#include "EmsPeriodicConsumer.cpp"
#include "EmsBarChart.cpp"

using namespace std;

int main()
{
    ofstream Result;
    Result.open("Result/Simulation_8.5.csv"); // Give path and name of the file to be created
    Result<<"Time"<<","<<"Wind Turbine"<<","<<"Periodic Consumer"<<","<<"Power To Grid"<<","
          <<"Battery Storage"<<","<<"Power from Battery"<<endl;
    Result<<"h"<<","<<"kW"<<","<<"kW"<<","<<"kW"<<","<<"kWh"<<","<<"kW"<<endl;

    int randomseed = time(NULL); randomseed = 1648052951;
    srand(randomseed);
    rand();rand();

    vector<double> vWind = readWindData("WindData/Wind_8.5.csv"); // Give path and name of the wind speed data file
    PowerCurve Data1("PowerCurve/PC.csv");  // giving path and name of the Power Curve data file
    PowerCurveData PC = Data1.getPC_data();

    //User data input, assign names and components profile values as function suggests
    EmsGrid testGrid ("TrialGrid", 30*EmsPower_1kW, 30*EmsPower_1kW);
    EmsWindTurbine testTurbine("TestTurbine", PC.Wind, PC.Power,vWind,10*EmsTime_1min);
    EmsPeriodicConsumer testCons("TestConsumer", 15*EmsPower_1kW, 5*EmsPower_1kW,
                                                 24*EmsTime_1h, 15*EmsTime_1h);
    EmsSimpleBattery testbattery("TestBattery",100*EmsEnergy_1kWh,10*EmsPower_1kW,
                                                10*EmsPower_1kW, 1);

    //set Display bar length
    EmsBarChart plotProd("TrialBarProd",50, testTurbine.getProfile().MinProdPower,
                                            testTurbine.getProfile().MaxProdPower);
    EmsBarChart plotCons("TrialBarCons",50, testCons.getProfile().MinConsPower,
                                            testCons.getProfile().MaxConsPower);
    EmsBarChart plotGrid("TrialBarGrid",50,-testGrid.getProfile().MaxIntoPower,
                                            testGrid.getProfile().MaxOutOfPower);
    EmsBarChart plotBatteryStorage("TrialStorage",50,0,testbattery.getProfile().energyCapacity);
    EmsBarChart plotBatteryPower("TrialBatteryPower",50,-testbattery.getProfile().maxUnloadingPower,
                                                        testbattery.getProfile().maxLoadingPower);

    //Assign simulation time credentials
    for(int t=1;t<=8760*EmsTime_1h;t+=10*EmsTime_1min)
    {
        testTurbine.forwardTo(t, nullptr);
        testCons.forwardTo(t, nullptr);

        double powerIn = testTurbine.getPower();
        double powerOut = testCons.getPower();

        EmsBatteryData batterydata(powerOut-powerIn);
        testbattery.forwardTo(t, &batterydata);

        double batteryPowerProvided;
        batteryPowerProvided = testbattery.getCurrentPowerProvided();

        double powerGridIn, powerGridOut;

            powerGridIn = powerIn;
            powerGridOut = powerOut;

        if(batteryPowerProvided > 0)
        {
            powerGridIn = powerIn + batteryPowerProvided;
            powerGridOut = powerOut;
        }
        if(batteryPowerProvided < 0)
        {
            powerGridIn = powerIn;
            powerGridOut = powerOut - batteryPowerProvided;
        }

        EmsGridData gridData(powerGridIn , powerGridOut);
        testGrid.forwardTo(t, &gridData);
        double gridPowerIn = testGrid.getPowerInto();
        double gridPowerOut = testGrid.getPowerOutOf();

/*
        cout<<fixed<<setprecision(2)<<"\n\tSimulation Time: "<<t/EmsTime_1h<<" hr"<<endl;
        cout<<fixed<<setprecision(4);
        if(testTurbine.currentSpeed.size()>=1)
        {
            cout<<"\tWind Speed: ";
            for(int j=0; j<testTurbine.currentSpeed.size();j++)
            {
                cout<<testTurbine.currentSpeed[j]<<" m/s\t";
            }
        }
        cout<<endl<<endl;
        cout<<"\t"<<plotProd.getBarString(powerIn)<<plotProd.percentage
            <<"%\t"<<"Wind Turbine"<<"\t\t"<<powerIn/EmsPower_1kW<<" kW "<<endl<<endl;
        cout<<"\t"<<plotCons.getBarString(powerOut)<<plotCons.percentage
            <<"%\t"<<"Periodic Consumer"<<"\t"<<powerOut/EmsPower_1kW<<" kW "<<endl<<endl;
        cout<<"\t"<<plotGrid.getBarString(gridPowerOut-gridPowerIn)<<plotGrid.percentage
            <<"%\t"<<"External Grid"<<"\t\t"<<(gridPowerIn-gridPowerOut)/EmsPower_1kW
            <<" kW "<<endl<<endl;
        cout<<"\t"<<plotBatteryStorage.getBarString(testbattery.getEnergy())
            <<plotBatteryStorage.percentage<<"%\t"<<"Battery storage\t\t"
            <<testbattery.getEnergy()/EmsEnergy_1kWh<<" kWh "<<endl<<endl;
        cout<<"\t"<<plotBatteryPower.getBarString(testbattery.getCurrentPowerProvided())
            <<plotBatteryPower.percentage<<"%\t"<<"Battery power\t\t"
            <<testbattery.getCurrentPowerProvided()/EmsPower_1kW<<" kW "<<endl<<endl;
*/
        Result<<fixed<<setprecision(2)<<t/EmsTime_1h<<","<<setprecision(4)<<powerIn/EmsPower_1kW
              <<","<<powerOut/EmsPower_1kW<<","<<(gridPowerIn-gridPowerOut)/EmsPower_1kW
              <<","<<testbattery.getEnergy()/EmsEnergy_1kWh<<","
              <<testbattery.getCurrentPowerProvided()/EmsPower_1kW<<endl;
        //Sleep(1000);
        //cin.get();
        //system("cls");
    }
    Result<<"Seed: "<<","<<randomseed<<endl;
    cout << "Seed: "<<randomseed;

    Result.close();
    return 0;

}
