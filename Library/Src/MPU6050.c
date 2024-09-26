#include "MPU6050.h"

#define MPU6050_ADDR 0xD0 // MPU6050 I2C address (0x68 << 1)
#define GYRO_CONFIG_REG 0x1B
#define PWR_MGMT_1_REG 0x6B
#define GYRO_ZOUT_H_REG 0x47
#define GYRO_SENSITIVITY 131.0 * 6 // Sensitivity for 250dps

const float timeDifference = 2e-3; // 2ms time step
const float NOISE_THRESHOLD = 0.05; // Noise threshold


float angle_z = 0;
float last_angle_rate = 0, angle_rate = 0;
float offset = 0;
float noise = 0;

// Function to write to MPU6050 register
void MPU6050_Write(u8 reg, u8 data)
{
    u8 dataBuffer[2];
    dataBuffer[0] = reg;
    dataBuffer[1] = data;
    HAL_I2C_Master_Transmit(&hi2c2, MPU6050_ADDR, dataBuffer, 2, 100);
}

// Function to read from MPU6050 register
u8 MPU6050_Read(u8 reg)
{
    u8 data = 0;
    HAL_I2C_Master_Transmit(&hi2c2, MPU6050_ADDR, &reg, 1, 100);
    HAL_I2C_Master_Receive(&hi2c2, MPU6050_ADDR, &data, 1, 100);
    return data;
}

// Function to initialize the MPU6050
void gyroInit(void)
{
    // Wake up MPU6050 by writing 0 to PWR_MGMT_1
    MPU6050_Write(PWR_MGMT_1_REG, 0x00);
    HAL_Delay(100);

    // Set gyro sensitivity to 250dps
    MPU6050_Write(GYRO_CONFIG_REG, 0x00);
    HAL_Delay(100);
}

// Function to read gyro Z-axis data (raw)
int16_t readGyro(void)
{
    u8 gyroZHigh = MPU6050_Read(GYRO_ZOUT_H_REG);
    u8 gyroZLow = MPU6050_Read(GYRO_ZOUT_H_REG + 1);
    int16_t gyroZ = (int16_t)(gyroZHigh << 8 | gyroZLow);
    return gyroZ;
}

// Function to calibrate the gyroscope
void gyroCalibration(void)
{
	int16_t calibration_buffer[BUFFER_LENGTH];
    int32_t calibrationSum = 0;

    for (u32 i = 0; i < BUFFER_LENGTH; i++)
    {
    	calibration_buffer[i] = readGyro();
        HAL_Delay(2);
        calibrationSum += calibration_buffer[i];
    }

    offset = (float)calibrationSum / BUFFER_LENGTH;

    // Calculate noise level
	for (u32 i = 0; i < BUFFER_LENGTH; i++)
		noise += pow(calibration_buffer[i] - offset, 2);
	noise = pow(noise, .5) / 2 / GYRO_SENSITIVITY;

    printf("Calibration complete. Offset: %f, Noise: %f\r\n", offset, noise);
}


// Function to update gyroscope data
int gyroUpdate(void)
{
    int16_t gyroZ = readGyro();
    angle_rate = ((float)(gyroZ - offset)) / GYRO_SENSITIVITY;

    // Apply noise filtering
    if (fabs(angle_rate) < NOISE_THRESHOLD && fabs(angle_rate) < noise)
    {
        angle_rate = 0;
    }

    // Update angle using trapezoidal rule for integration
    angle_z += ((angle_rate + last_angle_rate) * timeDifference) / 2.0f;
    last_angle_rate = angle_rate;

    printf("Angle Z: %f\r\n", angle_z);
    return 0;
}
