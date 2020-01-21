#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "sd_hal_mpu6050.h"
#define     PI              3.14159265358979323846
#define     RAD_TO_DEG      (180 / PI)
float Accel_to_Angle(int16_t, int16_t, int16_t);


int main(int argc, char **argv)
{
    int i;
    SD_MPU6050_Result result;
    SD_MPU6050 mpu;
    int16_t g_x, g_y, g_z ;
	int16_t a_x, a_y, a_z;
		
	float g_y_real;
	float angleY_from_accel;
    result = SD_MPU6050_Init(&mpu, SD_MPU6050_Device_0,
                            SD_MPU6050_Accelerometer_2G,
                            SD_MPU6050_Gyroscope_250s);
    printf("Test I2C program:\n");
    for(i = 0; i < 5; i++)
    {
        SD_MPU6050_ReadGyroscope(&mpu);
        SD_MPU6050_ReadAccelerometer(&mpu);
        g_x = mpu.Gyroscope_X;
        g_y = mpu.Gyroscope_Y;
        g_z = mpu.Gyroscope_Z;

        a_x = mpu.Accelerometer_X;
        a_y = mpu.Accelerometer_Y;
        a_z = mpu.Accelerometer_Z;

        g_y_real = g_y / 131.0;
        angleY_from_accel = Accel_to_Angle(-a_x, a_y, a_z);

        printf("#%d:\n", i);
        printf("gx=%d, gy=%d, gz=%d\n", g_x, g_y, g_z);
        printf("angleY=%.2f\n", angleY_from_accel);
        sleep(1);
    }
    

    return 0;
}

float Accel_to_Angle(int16_t accel_byte_x, int16_t accel_byte_y, int16_t accel_byte_z)
{
	float angle = (
                    atan2(accel_byte_x,
                    sqrt(accel_byte_y*accel_byte_y + accel_byte_z*accel_byte_z))
                ) * RAD_TO_DEG ;
	return angle;
}
