/*
 * PWM.c
 *
 *  Created on: Nov 8, 2015
 *      Author: harsh
 */

#include "PWM.h"

void SetPwmDutyCycle(uint32_t DutyCycle, PWM_MODULE Module)
{
    uint32_t CompareRegValue = 0;

    switch(Module)
    {
        case M0_PWM0:
        CompareRegValue = ((100 - DutyCycle)*PWM_0_0_LOAD_VALUE) / 100;
        REG_WRITE(PWM0_0_CMPA_R, CompareRegValue);
        break;

        case M0_PWM1:
        CompareRegValue = ((100 - DutyCycle)*PWM_0_1_LOAD_VALUE) / 100;
        REG_WRITE(PWM0_0_CMPB_R, CompareRegValue);
        break;

        case M0_PWM2:
        CompareRegValue = ((100 - DutyCycle)*PWM_0_2_LOAD_VALUE) / 100;
        REG_WRITE(PWM0_1_CMPA_R, CompareRegValue);
        break;

        case M0_PWM3:
        CompareRegValue = ((100 - DutyCycle)*PWM_0_3_LOAD_VALUE) / 100;
        REG_WRITE(PWM0_1_CMPB_R, CompareRegValue);
        break;

        case M0_PWM4:
        CompareRegValue = ((100 - DutyCycle)*PWM_0_4_LOAD_VALUE) / 100;
        REG_WRITE(PWM0_2_CMPA_R, CompareRegValue);
        break;

        case M0_PWM5:
        CompareRegValue = ((100 - DutyCycle)*PWM_0_5_LOAD_VALUE) / 100;
        REG_WRITE(PWM0_2_CMPB_R, CompareRegValue);
        break;

        case M0_PWM6:
        CompareRegValue = ((100 - DutyCycle)*PWM_0_6_LOAD_VALUE) / 100;
        REG_WRITE(PWM0_3_CMPA_R, CompareRegValue);
        break;

        case M0_PWM7:
        CompareRegValue = ((100 - DutyCycle)*PWM_0_7_LOAD_VALUE) / 100;
        REG_WRITE(PWM0_3_CMPB_R, CompareRegValue);
        break;

        case M1_PWM0:
        CompareRegValue = ((100 - DutyCycle)*PWM_1_0_LOAD_VALUE) / 100;
        REG_WRITE(PWM1_0_CMPA_R, CompareRegValue);
        break;

        case M1_PWM1:
        CompareRegValue = ((100 - DutyCycle)*PWM_1_1_LOAD_VALUE) / 100;
        REG_WRITE(PWM1_0_CMPB_R, CompareRegValue);
        break;

        case M1_PWM2:
        CompareRegValue = ((100 - DutyCycle)*PWM_1_2_LOAD_VALUE) / 100;
        REG_WRITE(PWM1_1_CMPA_R, CompareRegValue);
        break;

        case M1_PWM3:
        CompareRegValue = ((100 - DutyCycle)*PWM_1_3_LOAD_VALUE) / 100;
        REG_WRITE(PWM1_1_CMPB_R, CompareRegValue);
        break;

        case M1_PWM4:
        CompareRegValue = ((100 - DutyCycle)*PWM_1_4_LOAD_VALUE) / 100;
        REG_WRITE(PWM1_2_CMPA_R, CompareRegValue);
        break;

        case M1_PWM5:
        CompareRegValue = ((100 - DutyCycle)*PWM_1_5_LOAD_VALUE) / 100;
        REG_WRITE(PWM1_2_CMPB_R, CompareRegValue);
        break;

        case M1_PWM6:
        CompareRegValue = ((100 - DutyCycle)*PWM_1_6_LOAD_VALUE) / 100;
        REG_WRITE(PWM1_3_CMPA_R, CompareRegValue);
        break;

        case M1_PWM7:
        CompareRegValue = ((100 - DutyCycle)*PWM_1_7_LOAD_VALUE) / 100;
        REG_WRITE(PWM1_3_CMPB_R, CompareRegValue);
        break;

        default:
        break;
    }

}

/*
Function: PwmInit

Parameters:
    
Note: Configures PWM module. GPIO specific configuration is done in SetupGPIO
*/
void PwmInit()
{
    // Setup M1PWM7 / PF3 as PWM generator.
    
    { 
        // 1. Enable PWM Clocks for PWM generator 1
        REG_WRITE(SYSCTL_RCGCPWM_R,SYSCTL_RCGCPWM_R1); // generalize later
    }

    {
        RCGC2_REG   Rcgc2Reg = {0};
        
        // 2. Enable clock to GPIO Module via RCGC2 register
        Rcgc2Reg.GPIOF_Clock_En = ENABLE;
        REG_WRITE(SYSCTL_RCGC2_R, Rcgc2Reg.Value);
    }
        // 3. Select alternate function for PF3, done in SetupGPIO()
        // 4. Select Port Mux Control N to GPIOPCTL register to send PWM signal to appropriate pins  
    
    {
        RCC_REG RccReg = {0};
        
        // 5. Use System Clock and Divide it by 2
        RccReg.Value = REG_READ(SYSCTL_RCC_R);
        RccReg.PwmClockDivisorEn = 1;
        RccReg.PwmClockDivisor   = 0;

        REG_WRITE(SYSCTL_RCC_R, RccReg.Value);
    }
    
    {
        // 6a. Configure PWM with PWMCTRLx register
        REG_WRITE(PWM1_3_CTL_R,0);              // Currently keep this as default use PWMxCTL_REG definition to change values.
    }
    
    {
        PWMxGENAB_REG    PWMxGenABReg = {0};
        
        // 6b. Configure PWM Actions at various points. Load is the max value, PWMA signal stays high from LOAD to PWMA value and low from PWMA till 0 and Load.
        PWMxGenABReg.ActionForCompBDown     = PWM_ACTION_DRIVE_LOW;
        PWMxGenABReg.ActionForCounterEqLoad = PWM_ACTION_DRIVE_HIGH;
        REG_WRITE(PWM1_3_GENB_R, PWMxGenABReg.Value);
    }
    
    // 7. We are using internal clock PIOSC(default 16Mhz).20Khz cycle and 25% duty cycle
    // PWMClock = SysClock / 2 = 16/2 = 8 Mhz
    // #Ticks = 8x10^6/20x10^3 = 400 Ticks = 0x190-1 = 0x18f
    REG_WRITE(PWM1_3_LOAD_R, PWM_1_3_LOAD_VALUE);
    
    // 8. We need 25% Duty Cycle. Signal is high from load to PWMA and low from PWMA to 0.
    // Program PWMA to be at 100 - 25 = 75% of 400 = 300 - 1 = 0x12B
    SetPwmDutyCycle(0, M1_PWM7);
    
    {
        PWMxCTL_REG PWMxCtlReg = {0};
        
        // Enable PWM Module
        PWMxCtlReg.PWMxBlockEnable = 1;
        PWMxCtlReg.DebugMode       = 1;
        REG_WRITE(PWM1_3_CTL_R,PWMxCtlReg.Value);
    }
    
    {
        PWMENABLE_REG   PwmEnReg = {0};
        
        PwmEnReg.PWM7OutputEn = 1;
        REG_WRITE(PWM1_ENABLE_R, PwmEnReg.Value);
    }
    return;
}
