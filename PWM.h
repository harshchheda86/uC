/*
 * PWM.h
 *
 *  Created on: Nov 8, 2015
 *      Author: harsh
 */

#ifndef PWM_H_
#define PWM_H_

#include "device.h"

#define M1PWM7_ENCODING (5)

#define PWM_0_0_LOAD_VALUE (0x190) // 400 ticks
#define PWM_0_1_LOAD_VALUE (0x190) // 400 ticks
#define PWM_0_2_LOAD_VALUE (0x190) // 400 ticks
#define PWM_0_3_LOAD_VALUE (0x190) // 400 ticks
#define PWM_0_4_LOAD_VALUE (0x190) // 400 ticks
#define PWM_0_5_LOAD_VALUE (0x190) // 400 ticks
#define PWM_0_6_LOAD_VALUE (0x190) // 400 ticks
#define PWM_0_7_LOAD_VALUE (0x190) // 400 ticks
#define PWM_1_0_LOAD_VALUE (0x190) // 400 ticks
#define PWM_1_1_LOAD_VALUE (0x190) // 400 ticks
#define PWM_1_2_LOAD_VALUE (0x190) // 400 ticks
#define PWM_1_3_LOAD_VALUE (0x190) // 400 ticks
#define PWM_1_4_LOAD_VALUE (0x190) // 400 ticks
#define PWM_1_5_LOAD_VALUE (0x190) // 400 ticks
#define PWM_1_6_LOAD_VALUE (0x190) // 400 ticks
#define PWM_1_7_LOAD_VALUE (0x190) // 400 ticks

typedef enum PWM_MODULE_ENUM
{
    M0_PWM0 = 0x0,  // M0_PWM_0_A
    M0_PWM1,        // M0_PWM_0_B Table 20.1 page 1233 of datasheet
    M0_PWM2,
    M0_PWM3,
    M0_PWM4,
    M0_PWM5,
    M0_PWM6,
    M0_PWM7,
    M1_PWM0,
    M1_PWM1,
    M1_PWM2,
    M1_PWM3,
    M1_PWM4,
    M1_PWM5,
    M1_PWM6,
    M1_PWM7,

    // Keep this as last
    M1_PWM_MAX,   
}PWM_MODULE;

typedef struct PWMxCTL_REG_ENUM
{
    union
    {
        struct
        {
            uint32_t PWMxBlockEnable        : BIT      (0    );
            uint32_t CounterMode            : BIT      (1    );
            uint32_t DebugMode              : BIT      (2    );
            uint32_t LoadRegUpdateMode      : BIT      (3    );
            uint32_t CompAUpdateMode        : BIT      (4    );
            uint32_t CompBUpdateMode        : BIT      (5    );
            uint32_t PWMnGenAUpdateMode     : BIT_RANGE(7,6  );
            uint32_t PWMnGenBUpdateMode     : BIT_RANGE(9,8  );
            uint32_t PWMnDBCtlUpdateMode    : BIT_RANGE(11,10);
            uint32_t PWMnDBRiseUpdateMode   : BIT_RANGE(13,12);
            uint32_t PWMnDBFallUpdateMode   : BIT_RANGE(15,14);
            uint32_t FaultConditionSource   : BIT      (16   );
            uint32_t MinimumFaultPeriod     : BIT      (17   );
            uint32_t LatchFaultInput        : BIT      (18   );
            uint32_t                        : BIT_RANGE(31,19);
            };
        uint32_t Value;
    };
}PWMxCTL_REG;

typedef enum PWM_ACTION_ENUM
{
    PWM_ACTION_NOACTION,
    PWM_ACTION_INVERT,
    PWM_ACTION_DRIVE_LOW,
    PWM_ACTION_DRIVE_HIGH,
}PWM_ACTION;

typedef struct PWMxGENAB_REG_STRUCT
{
    union
    {
        struct
        {
            uint32_t ActionForCounerEq0     :BIT_RANGE(1,0  );
            uint32_t ActionForCounterEqLoad :BIT_RANGE(3,2  );
            uint32_t ActionForCompAUp       :BIT_RANGE(5,4  );
            uint32_t ActionForCompADown     :BIT_RANGE(7,6  );
            uint32_t ActionForCompBUp       :BIT_RANGE(9,8  );
            uint32_t ActionForCompBDown     :BIT_RANGE(11,10);
            uint32_t                        :BIT_RANGE(31,12);
        };
        uint32_t Value;
    };
}PWMxGENAB_REG;

typedef struct PWMENABLE_REG_STRUCT
{
    union
    {
        struct
        {
            uint32_t PWM0OutputEn   :BIT(0);
            uint32_t PWM1OutputEn   :BIT(1);
            uint32_t PWM2OutputEn   :BIT(2);
            uint32_t PWM3OutputEn   :BIT(3);
            uint32_t PWM4OutputEn   :BIT(4);
            uint32_t PWM5OutputEn   :BIT(5);
            uint32_t PWM6OutputEn   :BIT(6);
            uint32_t PWM7OutputEn   :BIT(7);
            uint32_t                :BIT_RANGE(31,8);
        };
        uint32_t Value;
    };
}PWMENABLE_REG;

void PwmInit();
void SetPwmDutyCycle(uint32_t DutyCycle, PWM_MODULE Module);

#endif /* PWM_H_ */
