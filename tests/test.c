#include <criterion/criterion.h>
#include "../adcs.h"

#define FLT_TOL (0.01)

AdcData_t adcData;
SunVector_t sunVector;

static void populateAdcData(unsigned int values[6])
{
    for (int i = 0; i < 6; i++)
    {
        adcData.array[i] = values[i];
    }
}

Test(adcs, eclipse)
{   
    populateAdcData((unsigned int[]){14, 12, 8, 10, 14, 0});
    ComputationStatus_t status = Adcs_ComputeSunVector(&adcData, &sunVector);
    cr_assert_eq(status, ECLIPSE);

    cr_assert_float_eq(sunVector.x, 0.0f, FLT_TOL);
    cr_assert_float_eq(sunVector.y, 0.0f, FLT_TOL);
    cr_assert_float_eq(sunVector.z, 0.0f, FLT_TOL);
}

Test(adcs, null)
{
    ComputationStatus_t status = Adcs_ComputeSunVector(NULL, &sunVector);
    cr_assert_eq(status, NULL_PTR_ERR);

    status = Adcs_ComputeSunVector(&adcData, NULL);
    cr_assert_eq(status, NULL_PTR_ERR);

    status = Adcs_ComputeSunVector(NULL, NULL);
    cr_assert_eq(status, NULL_PTR_ERR);
}

Test(adcs, basic_1)
{
    populateAdcData((unsigned int[]){4095, 0, 0, 0, 0, 0});
    ComputationStatus_t status = Adcs_ComputeSunVector(&adcData, &sunVector);
    cr_assert_eq(status, SUCCESS);
    cr_assert_float_eq(sunVector.x, 1.0f, FLT_TOL);
    cr_assert_float_eq(sunVector.y, 0.0f, FLT_TOL);
    cr_assert_float_eq(sunVector.z, 0.0f, FLT_TOL);

    populateAdcData((unsigned int[]){0, 4095, 0, 0, 0, 0});
    status = Adcs_ComputeSunVector(&adcData, &sunVector);
    cr_assert_eq(status, SUCCESS);
    cr_assert_float_eq(sunVector.x, 0.0f, FLT_TOL);
    cr_assert_float_eq(sunVector.y, 1.0f, FLT_TOL);
    cr_assert_float_eq(sunVector.z, 0.0f, FLT_TOL);

    populateAdcData((unsigned int[]){0, 0, 4095, 0, 0, 0});
    status = Adcs_ComputeSunVector(&adcData, &sunVector);
    cr_assert_eq(status, SUCCESS);
    cr_assert_float_eq(sunVector.x, 0.0f, FLT_TOL);
    cr_assert_float_eq(sunVector.y, 0.0f, FLT_TOL);
    cr_assert_float_eq(sunVector.z, 1.0f, FLT_TOL);

    populateAdcData((unsigned int[]){0, 0, 0, 4095, 0, 0});
    status = Adcs_ComputeSunVector(&adcData, &sunVector);
    cr_assert_eq(status, SUCCESS);
    cr_assert_float_eq(sunVector.x, -1.0f, FLT_TOL);
    cr_assert_float_eq(sunVector.y, 0.0f, FLT_TOL);
    cr_assert_float_eq(sunVector.z, 0.0f, FLT_TOL);

    populateAdcData((unsigned int[]){0, 0, 0, 0, 4095, 0});
    status = Adcs_ComputeSunVector(&adcData, &sunVector);
    cr_assert_eq(status, SUCCESS);
    cr_assert_float_eq(sunVector.x, 0.0f, FLT_TOL);
    cr_assert_float_eq(sunVector.y, -1.0f, FLT_TOL);
    cr_assert_float_eq(sunVector.z, 0.0f, FLT_TOL);

    populateAdcData((unsigned int[]){0, 0, 0, 0, 0, 4095});
    status = Adcs_ComputeSunVector(&adcData, &sunVector);
    cr_assert_eq(status, SUCCESS);
    cr_assert_float_eq(sunVector.x, 0.0f, FLT_TOL);
    cr_assert_float_eq(sunVector.y, 0.0f, FLT_TOL);
    cr_assert_float_eq(sunVector.z, -1.0f, FLT_TOL);
}

Test(adcdataunion, arbitrary_1)
{
    AdcData_t testAdcData;
    for (int i = 0; i < 6; i++)
    {
        testAdcData.array[i] = i * 10;
    }

    cr_assert_eq(testAdcData.components.plus_x, 0);
    cr_assert_eq(testAdcData.components.plus_y, 10);
    cr_assert_eq(testAdcData.components.plus_z, 20);
    cr_assert_eq(testAdcData.components.minus_x, 30);
    cr_assert_eq(testAdcData.components.minus_y, 40);
    cr_assert_eq(testAdcData.components.minus_z, 50);
}

Test(adcs, arbitrary_2)
{
    populateAdcData((unsigned int []){1808, 2711, 20, 10, 12, 2480});
    ComputationStatus_t status = Adcs_ComputeSunVector(&adcData, &sunVector);
    cr_assert_eq(status, SUCCESS);

    cr_assert_float_eq(sunVector.x, 0.441304237512, FLT_TOL);
    cr_assert_float_eq(sunVector.y, 0.661956356268, FLT_TOL);
    cr_assert_float_eq(sunVector.z, -0.605858359974, FLT_TOL);
}

Test(adcs, arbitrary_3)
{
    populateAdcData((unsigned int []){2739, 102, 3043, 10, 12, 14});
    ComputationStatus_t status = Adcs_ComputeSunVector(&adcData, &sunVector);
    cr_assert_eq(status, SUCCESS);

    cr_assert_float_eq(sunVector.x, 0.668759496234, FLT_TOL);
    cr_assert_float_eq(sunVector.y, 0.0247688702309, FLT_TOL);
    cr_assert_float_eq(sunVector.z, 0.743066106927, FLT_TOL);
}

Test(adcs, arbitrary_4)
{
    populateAdcData((unsigned int []){13, 205, 14, 4084, 10, 204});
    ComputationStatus_t status = Adcs_ComputeSunVector(&adcData, &sunVector);
    cr_assert_eq(status, SUCCESS);

    cr_assert_float_eq(sunVector.x, -0.997509336108, FLT_TOL);
    cr_assert_float_eq(sunVector.y, 0.0498754668054, FLT_TOL);
    cr_assert_float_eq(sunVector.z, -0.0498754668054, FLT_TOL);
}
