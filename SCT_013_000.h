#ifndef SCT_013_000
#define SCT_013_000

#include "mbed.h"

class SCT013000 {

    public:

        SCT013000(PinName pin);

        float current();

    protected:
        AnalogIn    _pin;
        float       _rburden;
        float       _fudge_factor;
        float       _noise;
        float       _ICAL;
        float       _ADC_COUNTS; 
        float       _Number_of_Samples; 
        float       _SupplyVoltage; 
        float       _offsetI;
        float       _sum_squared_current; 
        float       _filteredI; 
        float       _sampleI;
        float       _squared_current;
        float       _Prms; 
        float       _Vrms;
        float       _Irms;
};

#endif