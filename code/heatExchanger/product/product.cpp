
#include "product.h"

Product::Product(){}

Product::~Product(){}

double Product::calculate_flowRate_kilogramPerSecond(double Qbis, bool _verbose)
{
    if(_verbose)
    {
        cout<<"--- START calculate_flowRate_kilogramPerSecond ---"<<endl;
        cout<<"flowRate_kilogramPerSecond = Qbis/(Cp*(endTemperature_kelvin-startTemperature_kelvin)); "<< Qbis/(Cp*(endTemperature_kelvin-startTemperature_kelvin))<<endl;
        cout<<"---  END  calculate_flowRate_kilogramPerSecond ---"<<endl;
    }
    flowRate_kilogramPerSecond = Qbis/(Cp*(endTemperature_kelvin-startTemperature_kelvin));
    return flowRate_kilogramPerSecond;
}

double Product::averageTemperature_kelvin(bool _verbose)
{
    if(_verbose)
    {
        cout<<"--- START averageTemperature_kelvin ---"<<endl;
        cout<<"return (startTemperature_kelvin+endTemperature_kelvin)/2; "<<(startTemperature_kelvin+endTemperature_kelvin)/2<<endl;
        cout<<"---  END  averageTemperature_kelvin ---"<<endl;
    }
    return (startTemperature_kelvin+endTemperature_kelvin)/2;
}



double Product::Pr(bool _verbose)
{
    if(_verbose)
    {
        cout<<"--- START Pr ---"<<endl;
        cout<<"return (Cp*mu/k); "<<(Cp*mu/k)<<endl;
        cout<<"---  END  Pr ---"<<endl;
    }
    return (Cp*mu/k);
}

double Product::ut(double numberPass, double numberTubes, double d_one, bool _verbose)
{
    if(_verbose)
    {
        cout<<"--- START ut ---"<<endl;
        cout<<"_ut = (4*flowRate_kilogramPerSecond * numberPass)/(rho * MAISON_PI * d_one * d_one * numberTubes); "<< (4*flowRate_kilogramPerSecond * numberPass)/(rho * MAISON_PI * d_one * d_one * numberTubes)<<endl;
        cout<<"---  END  ut ---"<<endl;
    }
    _ut = (4*flowRate_kilogramPerSecond * numberPass)/(rho * MAISON_PI * d_one * d_one * numberTubes);
    return _ut;
}

double Product::ut(double Sflow, bool _verbose)
{
    if(_verbose)
    {
        cout<<"--- START ut ---"<<endl;
        cout<<"_ut = flowRate_kilogramPerSecond / (Sflow * rho); "<< flowRate_kilogramPerSecond / (Sflow * rho)<<endl;
        cout<<"---  END  ut ---"<<endl;
    }
    _ut = flowRate_kilogramPerSecond / (Sflow * rho);
    return _ut;
}


double Product::reynold(double d, bool _verbose)
{
    if(_verbose)
    {
        cout<<"--- START reynold ---"<<endl;
        cout<<"_reynold = (rho * _ut * d) / mu; "<< (rho * _ut * d) / mu<<endl;
        cout<<"---  END  reynold ---"<<endl;
    }
    _reynold = (rho * _ut * d) / mu;
    return _reynold; 
}

double Product::nusselt(double d_one, double lengthPipe, bool _verbose)
{
    if(_verbose)
    {
        cout<<"--- START nusselt ---"<<endl;
        cout<<"_nusselt = 0.036* pow(_reynold, 0.8) * pow(Pr(), 0.33) * pow((d_one / lengthPipe),0.055); "<< 0.036* pow(_reynold, 0.8) * pow(Pr(), 0.33) * pow((d_one / lengthPipe),0.055)<<endl;
        cout<<"---  END  nusselt ---"<<endl;
    }
    _nusselt = 0.036* pow(_reynold, 0.8) * pow(Pr(), 0.33) * pow((d_one / lengthPipe),0.055);
    return _nusselt; 
}

double Product::nusselt2(double C, double n, bool _verbose)
{
    if(_verbose)
    {
        cout<<"--- START nusselt2 ---"<<endl;
        cout<<"_nusselt = 1.13* C * pow(_reynold, n) * pow(Pr(), 0.33); "<< 1.13* C * pow(_reynold, n) * pow(Pr(), 0.33)<<endl;
        cout<<"---  END  nusselt2 ---"<<endl;
    }
    _nusselt = 1.13* C * pow(_reynold, n) * pow(Pr(), 0.33);
    return _nusselt; 
}

double Product::h(double d, bool _verbose)
{
    if(_verbose)
    {
        cout<<"--- START h ---"<<endl;
        cout<<"return (_nusselt * k) / d; "<<(_nusselt * k) / d<<endl;
        cout<<"---  END  h ---"<<endl;
    }
    _h = (_nusselt * k) / d;
    return _h;
}