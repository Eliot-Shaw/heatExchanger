#include "calculator.h"
#define HEAT_TRANSFER_EFFICIENCY 0.9



Calculator::Calculator(){}

Calculator::~Calculator(){}


void Calculator::initialisation(HeatExchanger &heatExchanger, bool _verbose)
{
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"Initialize the values, put a . for decimal, all values are mandatory"<<endl;
    cout<<endl;

    cout<<" -------------- Fluid"<<endl;
    cout<<"fluid's   flowRate_kilogramPerSecond = "; cin >>(heatExchanger.fluid.flowRate_kilogramPerSecond);
    cout<<"fluid's   startTemperature_kelvin = "; cin >>(heatExchanger.fluid.startTemperature_kelvin);
    cout<<"fluid's   endTemperature_kelvin = "; cin >>(heatExchanger.fluid.endTemperature_kelvin);
    cout<<"fluid's   k = "; cin >>(heatExchanger.fluid.k);
    cout<<"fluid's   Cp = "; cin >>(heatExchanger.fluid.Cp);
    cout<<"fluid's   mu = "; cin >>(heatExchanger.fluid.mu);
    cout<<"fluid's   rho = "; cin >>(heatExchanger.fluid.rho);
    cout<<"fluid's   Rf (fouling resistance) = "; cin >>(heatExchanger.fluid.Rf);
    cout<<endl;
    cout<<endl;
    
    cout<<" -------------- Coolant"<<endl;
    cout<<"coolant's   startTemperature_kelvin = "; cin >>(heatExchanger.coolant.startTemperature_kelvin);
    cout<<"coolant's   endTemperature_kelvin = "; cin >>(heatExchanger.coolant.endTemperature_kelvin);
    cout<<"coolant's   k = "; cin >>(heatExchanger.coolant.k);
    cout<<"coolant's   Cp = "; cin >>(heatExchanger.coolant.Cp);
    cout<<"coolant's   mu = "; cin >>(heatExchanger.coolant.mu);
    cout<<"coolant's   rho = "; cin >>(heatExchanger.coolant.rho);
    cout<<"coolant's   Cnusselt (for pt/de = 1.25)= "; cin >>(heatExchanger.coolant.Cnusselt);
    cout<<"coolant's   Nnusselt (for pt/de = 1.25)= "; cin >>(heatExchanger.coolant.Nnusselt);
    cout<<"coolant's   Rf (fouling resistance) = "; cin >>(heatExchanger.coolant.Rf);
    cout<<endl;
    cout<<endl;

    cout<<" -------------- System"<<endl;
    cout<<"lengthPipe = "; cin >>(heatExchanger.lengthPipe);
    cout<<"d_zero = "; cin >>(heatExchanger.d_zero);
    cout<<"innerPipeWidth = "; cin >>(heatExchanger.innerPipeWidth);
    cout<<"material_K = "; cin >>(heatExchanger.material_K);
    cout<<"Usuggested = "; cin >> (heatExchanger.Usuggested);
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"RUNNING THE APP FIRST TIME"<<endl;
    cout<<endl;
    cout<<endl;    
    
    cout << "... S: " << heatExchanger.S(_verbose) << endl;
    cout << "enter new F (correction factor) ";
    cin >> (heatExchanger.F);

    heatExchanger._numberTubes = heatExchanger.roundTubesNeeded(_verbose);
    cout << "Do you want to keep minimum tubes amount (old = "<<heatExchanger._numberTubes<<", <a character> to keep it)";
    possibleInput(heatExchanger._numberTubes);

    heatExchanger.satisfied = false;
    do
    {
        cout << "enter new number of pass (preferably pair) ";
        cin >> (heatExchanger.numberPass);
        cout << "enter new K1: ";
        cin >> heatExchanger.k_one;
        cout << "enter new n1: ";
        cin >> heatExchanger.n_one;

        cout << "Current velocity: " << heatExchanger.fluid.ut(heatExchanger.numberPass, heatExchanger._numberTubes, heatExchanger.d_one(_verbose), _verbose) << endl;

        cout << " ------------ Are you satisfied ? (yes 1, no 0) ------------ ";
        cin >> heatExchanger.satisfied;
    } while (heatExchanger.satisfied == false);

    heatExchanger.coolant.calculate_flowRate_kilogramPerSecond(heatExchanger.Qbis_realDuty_watts(_verbose), _verbose);
    heatExchanger.coolant.ut(heatExchanger.Sflow(_verbose), _verbose);

    heatExchanger.fluid.reynold(heatExchanger.d_one(), _verbose);
    heatExchanger.coolant.reynold(heatExchanger.de(), _verbose);
    
    heatExchanger.fluid.nusselt(heatExchanger.d_one(), heatExchanger.lengthPipe, _verbose);
    heatExchanger.coolant.nusselt2(heatExchanger.coolant.Cnusselt, heatExchanger.coolant.Nnusselt, _verbose);
    
    cout << "Suggested U value: " << heatExchanger.Usuggested << endl;
    cout << "Estimated U value: " << heatExchanger.Uestimate(_verbose) << endl;
    cout << "Actual U value: " << heatExchanger.Uactual(_verbose) << endl;
    cout << "U error: " << heatExchanger.Uerror(_verbose)*100 <<"%" << endl;
}

/**
 * update = return true
 */
bool Calculator::possibleInput(double& output) {
    double temp;
    
    // Save the current state of std::cin
    std::istream::iostate prevState = std::cin.rdstate();
    
    // Read input into temp, checking for a valid double
    std::cin >> temp;
    
    // Check if the input was a double
    if (std::cin.fail()) {
        // Clear the error flags and ignore invalid input
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        // Restore previous state
        std::cin.setstate(prevState);
        
        return false;  // Input was not valid, output remains unchanged
    } else {
        // Input was valid, update output
        output = temp;
        return true;
    }
}


void Calculator::updateValues(HeatExchanger &heatExchanger)
{
    cout<<"Update the values, press <a character> to keep the previous value"<<endl;
    cout<<"Update the values, press <a character> to keep the previous value"<<endl;
    cout<<"Update the values, press <a character> to keep the previous value"<<endl;
    cout<<endl;

    cout<<" -------------- Fluid"<<endl;
    cout<<"no modifications"<<endl;
    cout<<endl;
    cout<<endl;
    
    cout<<" -------------- Coolant"<<endl;
    cout<<"no modifications"<<endl;
    cout<<endl;
    cout<<endl;

    cout<<" -------------- System"<<endl;
    cout<<"lengthPipe ("<<heatExchanger.lengthPipe<<") = "; possibleInput(heatExchanger.lengthPipe);
    cout<<"pipe eternal Diameter (d_zero) ("<<heatExchanger.d_zero<<") = "; possibleInput(heatExchanger.d_zero);
    cout<<"innerPipeWidth ("<<heatExchanger.innerPipeWidth<<") = "; possibleInput(heatExchanger.innerPipeWidth);
    cout<<"material_K ("<<heatExchanger.material_K<<") = "; possibleInput(heatExchanger.material_K);
    cout<<"Usuggested ("<<heatExchanger.Usuggested<<") = "; possibleInput(heatExchanger.Usuggested);
    cout<<endl;
    cout<<endl;
}


void Calculator::reRun(HeatExchanger &heatExchanger, bool _verbose)
{
    cout<<endl;
    cout<<endl;
    cout<<"RUNNING THE APP AGAIN..."<<endl;
    cout<<endl;
    cout<<endl;
    
    cout << "enter new number of pass (preferably pair?) (old = "<<heatExchanger._numberTubes<<", <a character> to keep it)";
    possibleInput(heatExchanger._numberTubes);

    heatExchanger.satisfied = false;
    do
    {
        cout << "enter new number of pass (preferably pair?) (old = "<<heatExchanger.numberPass<<", <a character> to keep it)";
        if(!possibleInput(heatExchanger.numberPass)) 
        {
            heatExchanger.satisfied = true;
        }else
        {
            cout << "enter new K1: ";
            cin >> heatExchanger.k_one;
            cout << "enter new n1: ";
            cin >> heatExchanger.n_one;
        }

        cout << "Current velocity: " << heatExchanger.fluid.ut(heatExchanger.numberPass, heatExchanger._numberTubes, heatExchanger.d_one(_verbose), _verbose) << endl;

        cout << " ------------ Are you satisfied ? (yes 1, no 0) ------------ ";
        cin >> heatExchanger.satisfied;
    } while (heatExchanger.satisfied == false);

    heatExchanger.coolant.calculate_flowRate_kilogramPerSecond(heatExchanger.Qbis_realDuty_watts(_verbose), _verbose);
    heatExchanger.coolant.ut(heatExchanger.Sflow(_verbose), _verbose);

    heatExchanger.fluid.reynold(heatExchanger.d_one(), _verbose);
    heatExchanger.coolant.reynold(heatExchanger.de(), _verbose);
    
    heatExchanger.fluid.nusselt(heatExchanger.d_one(), heatExchanger.lengthPipe, _verbose);
    heatExchanger.coolant.nusselt2(heatExchanger.coolant.Cnusselt, heatExchanger.coolant.Nnusselt, _verbose);

    
    cout << "Suggested U value: " << heatExchanger.Usuggested << endl;
    cout << "Estimated U value: " << heatExchanger.Uestimate(_verbose) << endl;
    cout << "Actual U value: " << heatExchanger.Uactual(_verbose) << endl;
    cout << "U error: " << heatExchanger.Uerror(_verbose)*100 <<"%" << endl;
}

void Calculator::finalize(HeatExchanger &heatExchanger, bool _verbose)
{
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    
    cout<<" ------------------------- REPORT ------------------------- "<<endl;
    cout<<" ------------------------- REPORT ------------------------- "<<endl;
    cout<<" -------------------------        ------------------------- "<<endl;
    cout<<" -------------------------        ------------------------- "<<endl;
    cout<<" -------------------------        ------------------------- "<<endl;
    cout<<" -------------------------        ------------------------- "<<endl;
    cout<<" -------------------------        ------------------------- "<<endl;
    cout<<" ------------------------- REPORT ------------------------- "<<endl;
    cout<<" ------------------------- REPORT ------------------------- "<<endl;

    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<" -------------- Fluid"<<endl;
    cout<<"fluid's   flowRate_kilogramPerSecond = "<<heatExchanger.fluid.flowRate_kilogramPerSecond<<endl;
    cout<<"fluid's   startTemperature_kelvin = "<<heatExchanger.fluid.startTemperature_kelvin<<endl;
    cout<<"fluid's   endTemperature_kelvin = "<<heatExchanger.fluid.endTemperature_kelvin<<endl;
    cout<<"fluid's   averageTemperature_kelvin = "<<heatExchanger.fluid.averageTemperature_kelvin(_verbose)<<endl;
    cout<<"fluid's   k = "<<heatExchanger.fluid.k<<endl;
    cout<<"fluid's   Cp = "<<heatExchanger.fluid.Cp<<endl;
    cout<<"fluid's   mu = "<<heatExchanger.fluid.mu<<endl;
    cout<<"fluid's   rho = "<<heatExchanger.fluid.rho<<endl;
    cout<<"fluid's   Pr = "<<heatExchanger.fluid.Pr(_verbose)<<endl;
    cout<<"fluid's   Rf = "<<heatExchanger.fluid.Rf<<endl;
    cout<<"fluid's   _ut = "<<heatExchanger.fluid._ut<<endl;
    cout<<"fluid's   _reynold = "<<heatExchanger.fluid._reynold<<endl;
    cout<<"fluid's   _nusselt = "<<heatExchanger.fluid._nusselt<<endl;
    cout<<"fluid's   Cnusselt = "<<heatExchanger.fluid.Cnusselt<<endl;
    cout<<"fluid's   Nnusselt = "<<heatExchanger.fluid.Nnusselt<<endl;
    cout<<"fluid's   _h = "<<heatExchanger.fluid._h<<endl;
    cout<<endl;
    cout<<endl;

    cout<<" -------------- Coolant"<<endl;
    cout<<"coolant's flowRate_kilogramPerSecond = "<<heatExchanger.coolant.flowRate_kilogramPerSecond<<endl;
    cout<<"coolant's startTemperature_kelvin = "<<heatExchanger.coolant.startTemperature_kelvin<<endl;
    cout<<"coolant's endTemperature_kelvin = "<<heatExchanger.coolant.endTemperature_kelvin<<endl;
    cout<<"coolant's averageTemperature_kelvin = "<<heatExchanger.coolant.averageTemperature_kelvin(_verbose)<<endl;
    cout<<"coolant's k = "<<heatExchanger.coolant.k<<endl;
    cout<<"coolant's Cp = "<<heatExchanger.coolant.Cp<<endl;
    cout<<"coolant's mu = "<<heatExchanger.coolant.mu<<endl;
    cout<<"coolant's rho = "<<heatExchanger.coolant.rho<<endl;
    cout<<"coolant's Pr = "<<heatExchanger.coolant.Pr(_verbose)<<endl;
    cout<<"coolant's Rf = "<<heatExchanger.coolant.Rf<<endl;
    cout<<"coolant's _ut = "<<heatExchanger.coolant._ut<<endl;
    cout<<"coolant's _reynold = "<<heatExchanger.coolant._reynold<<endl;
    cout<<"coolant's _nusselt = "<<heatExchanger.coolant._nusselt<<endl;
    cout<<"coolant's Cnusselt = "<<heatExchanger.coolant.Cnusselt<<endl;
    cout<<"coolant's Nnusselt = "<<heatExchanger.coolant.Nnusselt<<endl;
    cout<<"coolant's _h = "<<heatExchanger.coolant._h<<endl;
    cout<<endl;
    cout<<endl;

    cout<<" -------------- System"<<endl;
    cout<<"Q_theoriticalDuty_watts = "<<heatExchanger.Q_theoriticalDuty_watts(_verbose)<<endl;
    cout<<"Qbis_realDuty_watts = "<<heatExchanger.Qbis_realDuty_watts(_verbose)<<endl;
    cout<<"deltaTLM = "<<heatExchanger.deltaTLM(_verbose)<<endl;
    cout<<"R = "<<heatExchanger.R(_verbose)<<endl;
    cout<<"S = "<<heatExchanger.S(_verbose)<<endl;
    cout<<"F = "<<heatExchanger.F<<endl;
    cout<<"A = "<<heatExchanger.A(_verbose)<<endl;
    cout<<"lengthPipe = "<<heatExchanger.lengthPipe<<endl;
    cout<<"d_zero = "<<heatExchanger.d_zero<<endl;
    cout<<"innerPipeWidth = "<<heatExchanger.innerPipeWidth<<endl;
    cout<<"d_one = "<<heatExchanger.d_one(_verbose)<<endl;
    cout<<"areaOneTube = "<<heatExchanger.areaOneTube(_verbose)<<endl;
    cout<<"theoriticalTubesNeeded = "<<heatExchanger.theoriticalTubesNeeded(_verbose)<<endl;
    cout<<"roundTubesNeeded = "<<heatExchanger.roundTubesNeeded(_verbose)<<endl;
    cout<<"numberPass = "<<heatExchanger.numberPass<<endl;
    cout<<"pt = "<<heatExchanger.pt(_verbose)<<endl;
    cout<<"k_one = "<<heatExchanger.k_one<<endl;
    cout<<"n_one = "<<heatExchanger.n_one<<endl;
    cout<<"db_bundle_diameter = "<<heatExchanger.db_bundle_diameter(_verbose)<<endl;
    cout<<"ds = "<<heatExchanger.ds(_verbose)<<endl;
    cout<<"Sflow = "<<heatExchanger.Sflow(_verbose)<<endl;
    cout<<"material_K = "<<heatExchanger.material_K<<endl;
    cout<<endl;
    cout<<"Usuggested = "<<heatExchanger.Usuggested<<endl;
    cout<<"Uestimate = "<<heatExchanger.Uestimate(_verbose)<<endl;
    cout<<"Uactual = "<<heatExchanger.Uactual(_verbose)<<endl;
    cout<<"Uerror = "<<heatExchanger.Uerror(_verbose)<<endl;
    cout<<endl;
    cout<<endl;
    cout<<" -------------------------  END   ------------------------- "<<endl;
    cout<<" -------------------------  END   ------------------------- "<<endl;
    cout<<" -------------------------        ------------------------- "<<endl;
    cout<<" -------------------------        ------------------------- "<<endl;
    cout<<" -------------------------        ------------------------- "<<endl;
    cout<<" -------------------------        ------------------------- "<<endl;
    cout<<" -------------------------        ------------------------- "<<endl;
    cout<<" -------------------------  END   ------------------------- "<<endl;
    cout<<" -------------------------  END   ------------------------- "<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
}

void Calculator::demo(HeatExchanger &heatExchanger, bool _verbose)
{
    cout << "enter fluid.flowRate_kilogramPerSecond: ";
    cin >> heatExchanger.fluid.flowRate_kilogramPerSecond;
    
    cout << "enter fluid.startTemperature_kelvin: ";
    cin >> heatExchanger.fluid.startTemperature_kelvin;
    cout << "enter fluid.endTemperature_kelvin: ";
    cin >> heatExchanger.fluid.endTemperature_kelvin;
    
    
    cout << "enter fluid.propreties for fluid average temp: "<< heatExchanger.fluid.averageTemperature_kelvin(_verbose) << endl;
    cout << "enter k: ";
    cin >> heatExchanger.fluid.k;
    cout << "enter Cp: ";
    cin >> heatExchanger.fluid.Cp;
    cout << "enter mu: ";
    cin >> heatExchanger.fluid.mu;
    cout << "enter rho: ";
    cin >> heatExchanger.fluid.rho;

    
    cout << "fluid Pr: "<< heatExchanger.fluid.Pr(_verbose) << endl;
    cout << "enter anticipate fouling resistance: ";
    cin >> heatExchanger.fluid.Rf;
    cout << "fluid duty: "<< heatExchanger.Q_theoriticalDuty_watts(_verbose) << endl;
    cout << "real fluid duty: "<< heatExchanger.Qbis_realDuty_watts(_verbose) << " due to the HEAT_TRANSFER_EFFICIENCY=" << HEAT_TRANSFER_EFFICIENCY << endl;

    
    cout << "enter coolant.startTemperature_kelvin: ";
    cin >> heatExchanger.coolant.startTemperature_kelvin;
    cout << "enter coolant.endTemperature_kelvin: ";
    cin >> heatExchanger.coolant.endTemperature_kelvin;
    
    cout << "enter coolant.propreties for coolant average temp: "<< heatExchanger.coolant.averageTemperature_kelvin(_verbose) << endl;
    cout << "enter k: ";
    cin >> heatExchanger.coolant.k;
    cout << "enter Cp: ";
    cin >> heatExchanger.coolant.Cp;
    cout << "enter mu: ";
    cin >> heatExchanger.coolant.mu;
    cout << "enter rho: ";
    cin >> heatExchanger.coolant.rho;

    
    cout << "coolant Pr: "<< heatExchanger.coolant.Pr(_verbose) << endl;
    cout << "enter anticipate fouling resistance: ";
    cin >> heatExchanger.coolant.Rf;
    cout << "coolant flowRate_kilogramPerSecond: "<< heatExchanger.coolant.calculate_flowRate_kilogramPerSecond(heatExchanger.Qbis_realDuty_watts(_verbose)) << endl;

    cout << "Cannot calculate log mean >:)" << endl;
    cout << "R: " << heatExchanger.R(_verbose) << endl;
    cout << "S: " << heatExchanger.S(_verbose) << endl;
    cout << "deltaTlm: " << heatExchanger.deltaTLM(_verbose) << endl;
    cout << "enter F (correction factor) according to previous values: ";
    cin >> heatExchanger.F;

    cout << "TODO DECISION TREE FOR EXCHANGER TYPE" << endl;

    cout << "enter U suggested according to graph: ";
    cin >> heatExchanger.Usuggested;
    cout << "A (may be area): " << heatExchanger.A(_verbose) << endl;

    cout << "Use NT to fix estimated coefficient as Uestimate" << endl;
    cout << "enter LengthPipe: ";
    cin >> heatExchanger.lengthPipe;
    cout << "enter dzero (meter): ";
    cin >> heatExchanger.d_zero;
    cout << "areaOneTube: " << heatExchanger.areaOneTube(_verbose) << endl;
    cout << "numbertubesneeded (theoritical value): " << heatExchanger.theoriticalTubesNeeded(_verbose) << endl;
    cout << "numbertubes (true value): " << heatExchanger.roundTubesNeeded(_verbose) << endl;
    cout << "Aim to build exchanger with Uestimate = " << heatExchanger.Uestimate(_verbose) << endl;

    cout << "Calculate tube side velocity" << endl;
    heatExchanger.satisfied = false;
    do
    {
        cout << "Enter number of pass (preferably pair?): ";
        cin >> heatExchanger.numberPass;

        cout << "Current velocity: " << heatExchanger.fluid.ut(heatExchanger.numberPass, heatExchanger.roundTubesNeeded(_verbose), heatExchanger.d_one(_verbose), _verbose) << endl;

        cout << "Are you satisfied ? (yes 1, no 0): ";
        cin >> heatExchanger.satisfied;
    } while (heatExchanger.satisfied == false);
    
    cout << "Fluid Reynold's value: " << heatExchanger.fluid.reynold(heatExchanger.d_one(_verbose), _verbose) << endl;

    cout << "Use Nusselt turbulent correlation for forced convection in tubes" << endl;
    cout << "Fluid Nusselt's value: " << heatExchanger.fluid.nusselt(heatExchanger.d_one(_verbose), heatExchanger.lengthPipe, _verbose) << endl;
    cout << "Fluid H1's value (Wm-2K-1): " << heatExchanger.fluid.h(heatExchanger.d_one(_verbose), _verbose) << endl;

    cout << "Find tube bundle diameter DB thus: assume tube pitch (pt)= 1.25 * d_zero = "<< heatExchanger.pt(_verbose) << endl;
    cout << "According to the number of pass ("<< heatExchanger.numberPass <<"), give the following values" << endl;
    cout << "enter K1: ";
    cin >> heatExchanger.k_one;
    cout << "enter N1: ";
    cin >> heatExchanger.n_one;
    cout << "Db value: " << heatExchanger.db_bundle_diameter(_verbose) << endl;

    cout << "Use graph to find clearance between bundle and shell diameter DS" << endl;
    cout << "There is a difference of " << heatExchanger.db_bundle_diameter(_verbose) <<" - " << heatExchanger.pt(_verbose) <<" = "<< heatExchanger.db_bundle_diameter(_verbose) - heatExchanger.pt(_verbose) << " = Ds - Db"<< endl;
    cout << "There is also Number of tubes at “equator” n = DB ÷ pt = " << floor(heatExchanger.db_bundle_diameter(_verbose)/heatExchanger.pt(_verbose)) << " tubes at widest point" << endl;
    
    cout << "Normal shell diameter is between 10percent and 20percent of tube length" << endl;
    cout << "Currently, the value is "<<heatExchanger.ds(_verbose) << " and should be between "<<  heatExchanger.lengthPipe/10 <<" and" << heatExchanger.lengthPipe/5 << endl;

    cout << "minimum baffle spacing DS ÷ 5 = "<<heatExchanger.theoriticalBaffleSpacing(_verbose)<<" m" << endl;
    cout << "maximum baffle (theoritical) "<<heatExchanger.theoriticalBaffleNeeded(_verbose) << endl;
    cout << "maximum baffle (real) "<<heatExchanger.roundBaffleNeeded(_verbose)<< endl;
    cout << "actual baffle spacing "<<heatExchanger.actualBaffleSpacing(_verbose)<< endl;

    cout << "Calculate equivalent diameter of shell-side fluid (De)" << heatExchanger.de(_verbose) << endl;
    
    cout << "Calculate cross-section for flow (S) for hypothetical tube row mid-shell of “n” tubes: " << heatExchanger.Sflow(_verbose) << endl;

    
    cout << "Determine material's K: ";
    cin >> heatExchanger.material_K;

    cout << "Calculate shell side velocity: " << heatExchanger.coolant.ut(heatExchanger.Sflow(_verbose), _verbose) << endl;
    cout << "Calculate shell side reynolds: " << heatExchanger.coolant.reynold(heatExchanger.de(_verbose), _verbose) << endl;
    
    cout<<"Grimison correlation for outside square pitch tube banks for pt=1.25:"<<endl;
    cout << "enter C: ";
    cin >> heatExchanger.coolant.Cnusselt;
    cout << "enter n: ";
    cin >> heatExchanger.coolant.Nnusselt;
    
    cout << "Coolant Nusselt's value: " << heatExchanger.coolant.nusselt2(heatExchanger.coolant.Cnusselt, heatExchanger.coolant.Nnusselt, _verbose) << endl;

    cout << "Not done yet TODO: following "<<endl;
    cout<<"for Pr>= 0.7, 2000 < Re < 4 * 10^4 && "<<heatExchanger.roundTubesNeeded(_verbose)<<" < 10"<<endl;

    cout << "Coolant H0's value (Wm-2K-1): " << heatExchanger.coolant.h(heatExchanger.de(_verbose), _verbose) << endl;

    cout << "Estimated U value: " << heatExchanger.Uestimate(_verbose) << endl;
    cout << "Actual U value: " << heatExchanger.Uactual(_verbose) << endl;
    cout << "U error: " << heatExchanger.Uerror(_verbose)*100 <<"%" << endl;
}