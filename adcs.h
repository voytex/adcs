

#ifndef _ADCS_H
#define _ADCS_H

// 12-bit ADC max
#define ADC_MAX (0x0FFF)
// ADC min
#define ADC_MIN (0x0)
// Darkness threshold
#define DARKNESS_THRESHOLD (0x000F)


typedef struct AdcPhotodiodesData {
    unsigned int plus_x;
    unsigned int plus_y;
    unsigned int plus_z;
    unsigned int minus_x;
    unsigned int minus_y;
    unsigned int minus_z;
} AdcPhotodiodesData_t;


typedef union AdcData {
    AdcPhotodiodesData_t components;
    unsigned int array[6];
} AdcData_t;


typedef struct SunVector {
    float x;
    float y;
    float z;
} SunVector_t;


typedef enum ComputationStatus {
    SUCCESS,
    ECLIPSE,
    NULL_PTR_ERR
} ComputationStatus_t;


ComputationStatus_t Adcs_ComputeSunVector(AdcData_t *adcData, SunVector_t *sunVector);


#endif

