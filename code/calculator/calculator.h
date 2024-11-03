#include "../heatExchanger/heatExchanger.h"

class Calculator
{
private:
public:
    Calculator();
    ~Calculator();
    
    bool possibleInput(double& output);
    void updateValues(HeatExchanger &heatExchanger);
    
    void initialisation(HeatExchanger &heatExchanger, bool _verbose = false);
    void reRun(HeatExchanger &heatExchanger, bool _verbose = false);
    void finalize(HeatExchanger &heatExchanger, bool _verbose = false);
    
    void demo(HeatExchanger &heatExchanger, bool _verbose = false);
};
