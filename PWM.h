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

typedef enum PWM_MODULE_ENUM
{
    PWM_MODULE_0,
    PWM_MODULE_1,
    
    // keep this as last
    PWM_MODULE_MAX,
}PWM_MODULE;

typedef enum PWM_INSTANCE_ENUM
{
    PWM_0,
    PWM_1,
    PWM_2,
    PWM_3,
    PWM_4,
    PWM_5,
    PWM_6,
    PWM_7,
    
    // keep this as last
    PWM_MAX,
}PWM_INSTANCE;

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

#endif /* PWM_H_ */
