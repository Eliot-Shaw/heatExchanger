#include <iostream>
#include <cmath>
# define MAISON_PI           3.14159265358979323846  /* pi */
# define MAISON_EXP           2.7182811828  /* exp */

using namespace std;
class Product
{
private:
public:
    Product();
    ~Product();

    double flowRate_kilogramPerSecond;
    double calculate_flowRate_kilogramPerSecond(double Qbis, bool _verbose = false);
    
    double startTemperature_kelvin;
    double endTemperature_kelvin;
    double averageTemperature_kelvin(bool _verbose = false);

    double k;
    double Cp;
    double mu;
    double rho;
    double Pr(bool _verbose = false);

    double Rf;

    double _ut;
    double ut(double numberPass, double numberTubes, double d_one, bool _verbose = false);
    double ut(double Sflow, bool _verbose = false);
    
    double _reynold;
    double reynold(double d, bool _verbose = false);

    double _nusselt;
    double Cnusselt;
    double Nnusselt;
    double nusselt(double d_one, double lengthPipe, bool _verbose = false);
    double nusselt2(double Cnusselt, double Nnusselt, bool _verbose = false);

    double _h;
    double h(double d, bool _verbose = false);

};