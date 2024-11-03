#include <iostream>
#include <cmath> 
#include "heatExchanger/heatExchanger.h"
#include "calculator/calculator.h"


#define INNER_PIPE_WIDTH 0.002
#define ROUNDING_APPROX 0.00001

#define ROUND(value) (round((value) / ROUNDING_APPROX) * ROUNDING_APPROX)


using namespace std;





int main() {
    cout << "PROGRAM WILL APPROXIMATE PRINTED VALUES TO THE NEAREST " << ROUNDING_APPROX << endl << endl;
    cout << "Fluid is defined as the product to be cooled inside the pipes" << endl;
    cout << "Coolant is the product that cools the fluid inside the shell and around the pipes" <<endl;

    HeatExchanger heatExchanger={};
    Calculator calculator={};

    bool demo_version = false;
    cout<<"do you want the demo version ? (0 no, 1 yes) ";
    cin >> demo_version;

    bool verbose = false;
    cout<<"do you want verbose ? (0 no, 1 yes) ";
    cin >> verbose;

    if(demo_version)
    {
        calculator.demo(heatExchanger, verbose);
        return 0;
    }

    calculator.initialisation(heatExchanger, verbose);

    bool giveUp = false;
    while (abs(heatExchanger.Uerror())>0.30)
    {
        cout << "Large error, need to recompute !"<<endl;

        cout<<"Give Up ? (0 no, 1 yes)"<<endl;
        cin >> giveUp;
        if(giveUp) break;

        cout <<"standard your options are:"<< endl;
        if(heatExchanger._Uerror>0)
        {
            cout<<"- reducing the tube length"<<endl;
            cout<<"- reducing the tube passes"<<endl;
            cout<<"- reducing the number of baffles (not implemented?)"<<endl;
        }else
        {
            cout<<"- augmenting the tube length"<<endl;
            cout<<"- augmenting the tube passes"<<endl;
            cout<<"- augmenting the number of baffles (not implemented?)"<<endl;
        }

        calculator.updateValues(heatExchanger);
        cout<<"Values updated, calcul are being recomputed..."<<endl<<endl;
        calculator.reRun(heatExchanger, verbose);
    }
    
    calculator.finalize(heatExchanger, verbose);

    cout<<endl<<"Code Finished, you can close the window"<<endl<<endl;
    while (true)
    {
        /* code */
    }
    

    return 0;
}