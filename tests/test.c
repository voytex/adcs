#include <criterion/criterion.h>
#include "../adcs.h"

Test(simple, test)
{
    AdcData_t adcData = {
        .components = {
            .plus_x = 0x000C,
            .plus_y = 0x0002,
            .plus_z = 0x000A,
            .minus_x = 0x0,
            .minus_y = 0x0,
            .minus_z = 0x0
        }
    };
    SunVector_t sunVector;
    ComputationStatus_t status = Adcs_ComputeSunVector(&adcData, &sunVector);
    cr_assert_eq(status, ECLIPSE);
    // cr_assert_eq(sunVector.x, 1.0f);
    // cr_assert_eq(sunVector.y, 1.0f);
    // cr_assert_eq(sunVector.z, 1.0f);
}