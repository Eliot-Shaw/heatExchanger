#include "heatExchanger.h"



#define HEAT_TRANSFER_EFFICIENCY 0.9
#define INNER_PIPE_WIDTH 0.002


HeatExchanger::HeatExchanger(){}

HeatExchanger::~HeatExchanger(){}


double HeatExchanger::Q_theoriticalDuty_watts(bool _verbose)
{
    if(_verbose)
    {
        cout<<"--- START Q_theoriticalDuty_watts ---"<<endl;
        cout<<"return (fluid.flowRate_kilogramPerSecond*fluid.Cp*(fluid.startTemperature_kelvin-fluid.endTemperature_kelvin)); "<<(fluid.flowRate_kilogramPerSecond*fluid.Cp*(fluid.startTemperature_kelvin-fluid.endTemperature_kelvin))<<endl;
        cout<<"---  END  Q_theoriticalDuty_watts ---"<<endl;
    }
    return (fluid.flowRate_kilogramPerSecond*fluid.Cp*(fluid.startTemperature_kelvin-fluid.endTemperature_kelvin));
}

double HeatExchanger::Qbis_realDuty_watts(bool _verbose)
{
    if(_verbose)
    {
        cout<<"--- START Qbis_realDuty_watts ---"<<endl;
        cout<<"return HEAT_TRANSFER_EFFICIENCY*(fluid.flowRate_kilogramPerSecond*fluid.Cp*(fluid.startTemperature_kelvin-fluid.endTemperature_kelvin)); "<<HEAT_TRANSFER_EFFICIENCY*(fluid.flowRate_kilogramPerSecond*fluid.Cp*(fluid.startTemperature_kelvin-fluid.endTemperature_kelvin))<<endl;
        cout<<"---  END  Qbis_realDuty_watts ---"<<endl;
    }
    return HEAT_TRANSFER_EFFICIENCY*(fluid.flowRate_kilogramPerSecond*fluid.Cp*(fluid.startTemperature_kelvin-fluid.endTemperature_kelvin));
}


double HeatExchanger::deltaTLM(bool _verbose)
{
    if(_verbose)
    {
        cout<<"--- START deltaTLM ---"<<endl;
        cout<<"if((fluid.startTemperature_kelvin-coolant.endTemperature_kelvin) == (fluid.endTemperature_kelvin-coolant.startTemperature_kelvin)) "<<endl;
        cout<<"then(return (fluid.startTemperature_kelvin-coolant.endTemperature_kelvin);) "<<(fluid.startTemperature_kelvin-coolant.endTemperature_kelvin)<<endl;
        cout<<"else(return ((fluid.startTemperature_kelvin-coolant.startTemperature_kelvin) + (fluid.endTemperature_kelvin-coolant.endTemperature_kelvin)) / log((fluid.startTemperature_kelvin-coolant.startTemperature_kelvin))-log((fluid.endTemperature_kelvin-coolant.endTemperature_kelvin));) "<<((fluid.startTemperature_kelvin-coolant.startTemperature_kelvin) + (fluid.endTemperature_kelvin-coolant.endTemperature_kelvin)) / (log((fluid.startTemperature_kelvin-coolant.startTemperature_kelvin))/log(MAISON_EXP))-(log((fluid.endTemperature_kelvin-coolant.endTemperature_kelvin))/log(MAISON_EXP))<<endl;
        cout<<"---  END  deltaTLM ---"<<endl;
    }
    if((fluid.startTemperature_kelvin-coolant.endTemperature_kelvin) == (fluid.endTemperature_kelvin-coolant.startTemperature_kelvin))
    {
        return (fluid.startTemperature_kelvin-coolant.endTemperature_kelvin);
    }else
    {   
        return ((fluid.startTemperature_kelvin-coolant.endTemperature_kelvin) - (fluid.endTemperature_kelvin-coolant.startTemperature_kelvin)) / ((log((fluid.startTemperature_kelvin-coolant.endTemperature_kelvin))/log(MAISON_EXP))-(log((fluid.endTemperature_kelvin-coolant.startTemperature_kelvin))/log(MAISON_EXP)));
    }
}

double HeatExchanger::R(bool _verbose)
{
    if(_verbose)
    {
        cout<<"--- START R ---"<<endl;
        cout<<"return (coolant.startTemperature_kelvin-coolant.endTemperature_kelvin)/(fluid.endTemperature_kelvin-fluid.startTemperature_kelvin); "<<(coolant.startTemperature_kelvin-coolant.endTemperature_kelvin)/(fluid.endTemperature_kelvin-fluid.startTemperature_kelvin)<<endl;
        cout<<"---  END  R ---"<<endl;
    }
    return (coolant.startTemperature_kelvin-coolant.endTemperature_kelvin)/(fluid.endTemperature_kelvin-fluid.startTemperature_kelvin);
}

double HeatExchanger::S(bool _verbose)
{
    if(_verbose)
    {
        cout<<"--- START S ---"<<endl;
        cout<<"return (fluid.endTemperature_kelvin-fluid.startTemperature_kelvin)/(coolant.startTemperature_kelvin-fluid.startTemperature_kelvin); "<<(fluid.endTemperature_kelvin-fluid.startTemperature_kelvin)/(coolant.startTemperature_kelvin-fluid.startTemperature_kelvin)<<endl;
        cout<<"---  END  S ---"<<endl;
    }
    return (fluid.endTemperature_kelvin-fluid.startTemperature_kelvin)/(coolant.startTemperature_kelvin-fluid.startTemperature_kelvin);
}


double HeatExchanger::A(bool _verbose)
{
    if(_verbose)
    {
        cout<<"--- START A ---"<<endl;
        cout<<"return std::abs((Qbis_realDuty_watts())/(Usuggested * F * deltaTLM())); "<<std::abs((Qbis_realDuty_watts())/(Usuggested * F * deltaTLM()))<<endl;
        cout<<"---  END  A ---"<<endl;
    }
    return std::abs((Qbis_realDuty_watts())/(Usuggested * F * deltaTLM()));
}


double HeatExchanger::d_one(bool _verbose)
{
    if(_verbose)
    {
        cout<<"--- START d_one ---"<<endl;
        cout<<"return (d_zero - 2*innerPipeWidth); "<<(d_zero - 2*innerPipeWidth)<<endl;
        cout<<"---  END  d_one ---"<<endl;
    }
    return (d_zero - 2*innerPipeWidth);
}


double HeatExchanger::areaOneTube(bool _verbose)
{
    if(_verbose)
    {
        cout<<"--- START areaOneTube ---"<<endl;
        cout<<"return MAISON_PI * lengthPipe * d_zero; "<<MAISON_PI * lengthPipe * d_zero<<endl;
        cout<<"---  END  areaOneTube ---"<<endl;
    }
    return MAISON_PI * lengthPipe * d_zero;
}

double HeatExchanger::theoriticalTubesNeeded(bool _verbose)
{
    if(_verbose)
    {
        cout<<"--- START theoriticalTubesNeeded ---"<<endl;
        cout<<"return A() / areaOneTube(); "<<A() / areaOneTube()<<endl;
        cout<<"---  END  theoriticalTubesNeeded ---"<<endl;
    }
    return A() / areaOneTube();
}

double HeatExchanger::roundTubesNeeded(bool _verbose)
{
    if(_verbose)
    {
        cout<<"--- START roundTubesNeeded ---"<<endl;
        cout<<"return ceil(theoriticalTubesNeeded()); "<<ceil(theoriticalTubesNeeded())<<endl;
        cout<<"---  END  roundTubesNeeded ---"<<endl;
    }
    return ceil(theoriticalTubesNeeded());
}

double HeatExchanger::Uestimate(bool _verbose)
{
    if(_verbose)
    {
        cout<<"--- START Uestimate ---"<<endl;
        cout<<"return Qbis_realDuty_watts()/(_numberTubes * areaOneTube() * F * deltaTLM()); "<<Qbis_realDuty_watts()<<"/"<<_numberTubes<<" * "<<areaOneTube()<<" * "<<F<<" * "<<deltaTLM()<<endl;
        cout<<"return Qbis_realDuty_watts()/(_numberTubes * areaOneTube() * F * deltaTLM()); "<<Qbis_realDuty_watts()/(_numberTubes * areaOneTube() * F * deltaTLM())<<endl;
        cout<<"---  END  Uestimate ---"<<endl;
    }
    _Uestimate = Qbis_realDuty_watts()/(_numberTubes * areaOneTube() * F * deltaTLM());
    return _Uestimate;
}


double HeatExchanger::pt(bool _verbose)
{
    if(_verbose)
    {
        cout<<"--- START pt ---"<<endl;
        cout<<"return d_zero*1.25; "<<d_zero*1.25<<endl;
        cout<<"---  END  pt ---"<<endl;
    }
    return d_zero*1.25;
}


double HeatExchanger::db_bundle_diameter(bool _verbose)
{
    if(_verbose)
    {
        cout<<"--- START db_bundle_diameter ---"<<endl;
        cout<<"return d_zero * pow((_numberTubes/k_one), (1/n_one)); "<<d_zero * pow((_numberTubes/k_one), (1/n_one))<<endl;
        cout<<"---  END  db_bundle_diameter ---"<<endl;
    }
    return d_zero * pow((_numberTubes/k_one), (1/n_one));
}


double HeatExchanger::ds(bool _verbose)
{
    if(_verbose)
    {
        cout<<"--- START ds ---"<<endl;
        cout<<"return db_bundle_diameter() * 1.01 + 0.00743;"<<db_bundle_diameter() * 1.01 + 0.00743<<endl;
        cout<<"---  END  ds ---"<<endl;
    }
    return db_bundle_diameter() * 1.01 + 0.00743;
}


double HeatExchanger::theoriticalBaffleSpacing(bool _verbose)
{
    if(_verbose)
    {
        cout<<"--- START theoriticalBaffleSpacing ---"<<endl;
        cout<<"return ds() / 5; "<<ds() / 5<<endl;
        cout<<"---  END  theoriticalBaffleSpacing ---"<<endl;
    }
    return ds() / 5;
}

double HeatExchanger::theoriticalBaffleNeeded(bool _verbose)
{
    if(_verbose)
    {
        cout<<"--- START theoriticalBaffleNeeded ---"<<endl;
        cout<<"return lengthPipe / theoriticalBaffleSpacing(); "<<lengthPipe / theoriticalBaffleSpacing()<<endl;
        cout<<"---  END  theoriticalBaffleNeeded ---"<<endl;
    }
    return lengthPipe / theoriticalBaffleSpacing();
}

double HeatExchanger::roundBaffleNeeded(bool _verbose)
{
    if(_verbose)
    {
        cout<<"--- START roundBaffleNeeded ---"<<endl;
        cout<<"return floor(theoriticalBaffleNeeded()); "<<floor(theoriticalBaffleNeeded())<<endl;
        cout<<"---  END  roundBaffleNeeded ---"<<endl;
    }
    return floor(theoriticalBaffleNeeded());
}

double HeatExchanger::actualBaffleSpacing(bool _verbose)
{
    if(_verbose)
    {
        cout<<"--- START actualBaffleSpacing ---"<<endl;
        cout<<"return lengthPipe / roundBaffleNeeded(); "<<lengthPipe / roundBaffleNeeded()<<endl;
        cout<<"---  END  actualBaffleSpacing ---"<<endl;
    }
    return lengthPipe / roundBaffleNeeded();
}


double HeatExchanger::de(bool _verbose)
{
    if(_verbose)
    {
        cout<<"--- START de ---"<<endl;
        cout<<"return ((4*pt()*pt()) / (MAISON_PI*d_zero)) - d_zero; "<<((4*pt()*pt()) / (MAISON_PI*d_zero)) - d_zero<<endl;
        cout<<"---  END  de ---"<<endl;
    }
    return ((4*pow(pt(),2)) / (MAISON_PI*d_zero)) - d_zero;
}



double HeatExchanger::Sflow(bool _verbose)
{    
    if(_verbose)
    {
        cout<<"--- START Sflow ---"<<endl;
        cout<<"return actualBaffleSpacing()*(ds()-(floor(db_bundle_diameter()/pt())*d_zero)); "<<actualBaffleSpacing()*(ds()-(floor(db_bundle_diameter()/pt())*d_zero))<<endl;
        cout<<"---  END  Sflow ---"<<endl;
    }
    return actualBaffleSpacing()*(ds()-(floor(db_bundle_diameter()/pt())*d_zero));
}


double HeatExchanger::Uactual(bool _verbose)
{
    if(_verbose)
    {
        cout<<"--- START Uactual ---"<<endl;
        cout<<"return 1/( ((1/fluid.h(d_one()))+fluid.Rf) + ((d_one()*(log(d_zero/d_one())))/(2*material_K)) + (d_one()/d_zero)*((1/coolant.h(de()))+coolant.Rf)); "<<1/( ((1/fluid.h(d_one()))+fluid.Rf) + ((d_one()*((log(d_zero/d_one())/log(MAISON_EXP))))/(2*material_K)) + (d_one()/d_zero)*((1/coolant.h(de()))+coolant.Rf))<<endl;
        cout<<"---  END  Uactual ---"<<endl;
    }
    _Uactual = 1/( ((1/fluid.h(d_one()))+fluid.Rf) + ((d_one()*((log(d_zero/d_one())/log(MAISON_EXP))))/(2*material_K)) + (d_one()/d_zero)*((1/coolant.h(de()))+coolant.Rf));
    return _Uactual;
}


double HeatExchanger::Uerror(bool _verbose)
{
    if(_verbose)
    {
        cout<<"--- START Uerror ---"<<endl;
        cout<<"return (100*(Uactual()-Uestimate())/Uestimate()); "<<(100*(Uactual()-Uestimate())/Uestimate())<<endl;
        cout<<"---  END  Uerror ---"<<endl;
    }
    _Uerror = ((Uactual()-Uestimate())/Uestimate());
    return _Uerror;
}