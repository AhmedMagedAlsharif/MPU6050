#include "main.h"

#define CALC_dt         0.01f

void Calc_Routine(void);
void Control_Routine(void);
void Serial_Routine(void);

int main(void)
{
    I2C_Init(I2C_FREQ_400K, I2C_PULLUP_ON);
    imu_init();
    UART_Init(250000);
    gyro_offset();
    
    SCH_Init_T0();
    SCH_Add_Task(Calc_Routine, 0, 1, 10);
    SCH_Add_Task(Serial_Routine, 0, 1, 100);
    
    SCH_Start();
    while(1)
    {
        SCH_Dispatch_Tasks();
    }
    return 0;
}

void Calc_Routine(void)
{
    sample_meters();
    matrix_update(CALC_dt);
    normalize();
    drift_correction();
    euler_angles();	
}
void Control_Routine(void)
{
    
}
void Serial_Routine(void)
{
    UART_Send_String("\nRoll=");
    UART_Send_Float(a_result[0], 2);
    UART_Send_String("\tPitch=");
    UART_Send_Float(a_result[1], 2);
    UART_Send_String("\tYaw=");
    UART_Send_Float(a_result[2], 2);
}
