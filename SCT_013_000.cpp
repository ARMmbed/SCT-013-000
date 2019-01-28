#include "SCT_013_000.h"

SCT013000::SCT013000(PinName pin): _pin(pin){
    _rburden = 22.0;
    _fudge_factor =1.22;
    _noise = 0.127;
    _ICAL = 2000.0/_rburden;
    _ADC_COUNTS = 4096.0; 
    _Number_of_Samples = 30000; 
    _SupplyVoltage = 3.3; 
    _offsetI = 2048.0;
    _sum_squared_current = 0.0;; 
    _filteredI = 0.0; 
    _sampleI = 0.0;
    _squared_current = 0.0;
    _Prms = 0.0; 
    _Vrms = 230;
    _Irms = 0.0;
}
 
float SCT013000::current() {
            float ratio = _fudge_factor * _ICAL *((_SupplyVoltage) / (_ADC_COUNTS));

        // Iterate over the signal samples
        for (int i=0; i<_Number_of_Samples; i++) { 
            // Analog input value from the sensor (varies between 0-1), multiply by ADC BITS to be able to calculate with Offset           
            _sampleI = (_pin.read()*_ADC_COUNTS); 

            //pc.printf("\n\r sample I is: %0.3f ", sampleI);

            // Digital low pass filter extracts the 1.65 V DC offset,
            // Then subtract this - signal is now centered on 0 counts.
            _offsetI = _offsetI + ((_sampleI-_offsetI)/_ADC_COUNTS); 
            _filteredI = _sampleI - _offsetI;
            //pc.printf("\n\r sampleI %0.3f ", sampleI);
    
            // Square current values
            _squared_current = _filteredI * _filteredI; 
            _sum_squared_current += _squared_current;
        }

        // Calculate average RMS current
        _Irms = ((ratio * sqrt(_sum_squared_current / _Number_of_Samples)) /*- _noise*/);
 //       if (_Irms<0.00) _Irms=0; //get rid of null values
        _sum_squared_current = 0; // Reset accumulator

        return _Irms;
}
