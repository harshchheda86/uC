/*
 * PWM.c
 *
 *  Created on: Nov 8, 2015
 *      Author: harsh
 */

#include "PWM.h"

void PwmInit()
{
    // Setup M1PWM7 / PF3 as PWM generator.
    
    { // 1. Enable PWM Clocks
        REG_WRITE(SYSCTL_RCGCPWM_R,0x2); // generalize later
    }
    {
        RCGC2_REG   Rcgc2Reg = {0};
        
        // 2. Enable clock to GPIO Module via RCGC2 register
        Rcgc2Reg.GPIOF_Clock_En = 1;
        REG_WRITE(SYSCTL_RCGC2_R, Rcgc2Reg.Value);
    }
    
    {
        GPIOCONFIG_REG GpioAfsel_Reg = {0};
        
        // 3. Select alternate function for PORT PF3.
        GpioAfsel_Reg.PortBit3Cfg = 1;
        REG_WRITE(GPIO_PORTF_AFSEL_R, GpioAfsel_Reg.Value);
    }
    
    {
        GPIOPCTL_REG   GpioPctlReg = {0};
        
        // 4. Select Port Mux Control N to GPIOPCTL register to send PWM signal to appropriate pins
        GpioPctlReg.PortMuxControl3 = M1PWM7_ENCODING; // Use PortMuxCtrl(x) for xth bit in Port
        REG_WRITE(GPIO_PORTF_PCTL_R, GpioPctlReg.Value);
    }
    
    {
        RCC_REG RccReg = {0};
        
        // 5. Use System Clock and Divide it by 2
        RccReg.Value = REG_READ(SYSCTL_RCC_R);
        RccReg.PwmClockDivisorEn = 1;
        RccReg.PwmClockDivisor   = 0;

        // move below line to init
        // RccReg.XTALValue = 0x15;

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
    REG_WRITE(PWM1_3_LOAD_R, 0x18f);
    
    // 8. We need 25% Duty Cycle. Signal is high from load to PWMA and low from PWMA to 0.
    // Program PWMA to be at 100 - 25 = 75% of 400 = 300 - 1 = 0x12B
    REG_WRITE(PWM1_3_CMPB_R, 0x12B);
    
    {
        PWMxCTL_REG PWMxCtlReg = {0};
        
        // Enable PWM Module
        PWMxCtlReg.PWMxBlockEnable = 1;
        PWMxCtlReg.DebugMode = 1;
        REG_WRITE(PWM1_3_CTL_R,PWMxCtlReg.Value);
    }
    
    {
        PWMENABLE_REG   PwmEnReg = {0};
        
        PwmEnReg.PWM7OutputEn = 1;
        REG_WRITE(PWM1_ENABLE_R, PwmEnReg.Value);
    }
    return;
}
