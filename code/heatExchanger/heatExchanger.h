#ifndef HEATEXCHANGER_H
#define HEATEXCHANGER_H

#include <cmath> 
#include <iostream>

#include "./product/product.h"

using namespace std;

class HeatExchanger
{

private:
// rien soy boy
public:
    HeatExchanger(); // default constructeur tiede
    ~HeatExchanger(); // default constructeur tiede
    

    Product fluid={};
    Product coolant={};

    double Q_theoriticalDuty_watts(bool _verbose = false);
    double Qbis_realDuty_watts(bool _verbose = false);

    double deltaTLM(bool _verbose = false);
    double R(bool _verbose = false);
    double S(bool _verbose = false);

    double F;

    double Usuggested;
    
    double A(bool _verbose = false);

    double lengthPipe;
    double d_zero;
    double innerPipeWidth = 0.002;

    double d_one(bool _verbose = false);

    double _numberTubes;

    double areaOneTube(bool _verbose = false);
    double theoriticalTubesNeeded(bool _verbose = false);
    double roundTubesNeeded(bool _verbose = false);
    double Uestimate(bool _verbose = false);

    double numberPass;
    bool satisfied;

    double pt(bool _verbose = false);

    double k_one;
    double n_one;

    double db_bundle_diameter(bool _verbose = false);

    double ds(bool _verbose = false);

    int numberBaffle;

    double theoriticalBaffleSpacing(bool _verbose = false); 
    double theoriticalBaffleNeeded(bool _verbose = false);
    double roundBaffleNeeded(bool _verbose = false);
    double actualBaffleSpacing(bool _verbose = false);

    double de(bool _verbose = false);

    double Sflow(bool _verbose = false);

    double material_K;

    double _Uestimate;
    double _Uactual;
    double _Uerror;


    double Uactual(bool _verbose = false);

    double Uerror(bool _verbose = false);
};

#endif // HEATEXCHANGER_H
