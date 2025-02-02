#include <stdio.h>
#include <stdbool.h>
#include <float.h>
#include "adcs.h"


static float quantizedToFloat(unsigned int val) 
{
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
    pSunVector->x = quantizedToFloat(pComponents->plus_x) - quantizedToFloat(pComponents->minus_x);
    pSunVector->y = quantizedToFloat(pComponents->plus_y) - quantizedToFloat(pComponents->minus_y);
    pSunVector->z = quantizedToFloat(pComponents->plus_z) - quantizedToFloat(pComponents->minus_z);
    return SUCCESS;
}
