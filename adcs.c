#include <stdio.h>
#include <stdbool.h>
#include "adcs.h"


static inline float quantizedToFloat(unsigned int val) 
{
    // Assuming that: 
    //    0.1 V -> val == 0x0000
    //    3.2 V -> val == 0x0FFF
    return (float)val / (float)ADC_MAX;
}


static bool detectEclipse(AdcData_t *pAdcData)
{
    for (int i = 0; i < 6; i++) 
    {
        if (pAdcData->array[i] > DARKNESS_THRESHOLD) 
        {
            return false;
        }
    }
    return true;
}


static inline float computeComponent(unsigned int plus, unsigned int minus) 
{
    return plus >= minus ? quantizedToFloat(plus) : -quantizedToFloat(minus);
}


ComputationStatus_t Adcs_ComputeSunVector(AdcData_t *pAdcData, SunVector_t *pSunVector) 
{
    if ((NULL == pAdcData) || (NULL == pSunVector)) 
    {
        return NULL_PTR_ERR;
    }

    if (detectEclipse(pAdcData)) 
    {
        return ECLIPSE;
    }

    AdcPhotodiodesData_t *pComponents = &pAdcData->components;
    pSunVector->x = computeComponent(pComponents->plus_x, pComponents->minus_x);
    pSunVector->y = computeComponent(pComponents->plus_y, pComponents->minus_y);
    pSunVector->z = computeComponent(pComponents->plus_z, pComponents->minus_z);
    return SUCCESS;
}
