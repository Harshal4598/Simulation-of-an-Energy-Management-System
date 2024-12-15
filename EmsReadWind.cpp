#ifndef EMSREADWIND
#define EMSREADWIND

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;
vector<double> readWindData(string filename)
{
    string line,word;
    vector<double> vWind,P;
    ifstream file(filename,ios::in);
    if(file.is_open())
    {
        while(getline(file,line))
        {
            stringstream str(line);

            getline(str, word, ',');
            P.push_back(stod(word));
            getline(str, word, '\n');
            vWind.push_back(stod(word));
        }
    }
    else
    {
        cout<<"Unable to open the file"<<endl;
    }
    return vWind;
}
#endif // EMSREADWIND
