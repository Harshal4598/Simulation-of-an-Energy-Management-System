#ifndef EMSREADPOWERCURVE
#define EMSREADPOWERCURVE

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

struct PowerCurveData
{
    vector<double> Wind, Power;
};
class PowerCurve
{
protected:

    PowerCurveData read;

public:

    void setPC_data(string filename)
    {
        string line,word;
        ifstream file(filename,ios::in);
        if(file.is_open())
        {
            while(getline(file,line))
            {
                stringstream str(line);

                getline(str, word, ',');
                read.Wind.push_back(stod(word));
                getline(str, word, '\n');
                read.Power.push_back(stod(word));
            }
        }
        else
        {
            cout<<"Unable to open the file"<<endl;
        }
    }
    PowerCurveData getPC_data()
    {
        return read;
    }
    PowerCurve (string Filename)
    {
        setPC_data(Filename);
    }
};
#endif // EMSREADPOWERCURVE
