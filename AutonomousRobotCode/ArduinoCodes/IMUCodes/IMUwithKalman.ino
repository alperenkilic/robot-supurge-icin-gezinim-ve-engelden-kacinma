#include <MPU6050.h>

 
/*
    Kalman Filter for MPU6050. Output for processing with Serial Plotter.
    Web: https://indobot.co.id
    (created) 2021 by Zamisyak Oby Indobot Academy
    The Fastest Way to Electronics Mastery
*/

#include <Wire.h>
#include <MPU6050.h>
#include <KalmanFilter.h>

MPU6050 mpu;

KalmanFilter kalmanX(0.001, 0.003, 0.03);
KalmanFilter kalmanY(0.001, 0.003, 0.03);
KalmanFilter kalmanZ(0.001, 0.003, 0.03);

float accPitch = 0;
float accRoll = 0;

float kalPitch = 0;
float kalRoll = 0;

float kalYaw = 0;
float accYaw = 0;

void setup() 
{
  Serial.begin(115200);

  // Inisialisasi MPU6050
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    delay(500);
  }
 
  // Kalibrasi giroskop. Saat kalibrasi sensor harus diam.
  mpu.calibrateGyro();// Jika Anda tidak ingin mengkalibrasi, beri komentar pada baris ini.

  // Membuat label pada masing-masing keluaran.
  Serial.println("accPitch,kalPitch,accRoll,kalRoll");
}

void loop()
{
  Vector acc = mpu.readNormalizeAccel();
  Vector gyr = mpu.readNormalizeGyro();

  // Menghitung Pitch &amp;amp;amp; Roll dari akselerometer (derajat)
  accPitch = -(atan2(acc.XAxis, sqrt(acc.YAxis*acc.YAxis + acc.ZAxis*acc.ZAxis))*180.0)/M_PI;
  accRoll  = (atan2(acc.YAxis, acc.ZAxis)*180.0)/M_PI;
  accYaw = 180 * atan (acc.ZAxis/sqrt(acc.XAxis*acc.XAxis + acc.ZAxis*acc.ZAxis))/M_PI;



  // Kalman filter
  kalPitch = kalmanY.update(accPitch, gyr.YAxis);
  kalRoll = kalmanX.update(accRoll, gyr.XAxis);
  kalYaw = kalmanZ.update(accYaw,gyr.ZAxis);
  // Menampilkan data Pitch sebelum di Filter
//  Serial.print(accPitch);
//  Serial.print(",");
//
//  // Menampilkan data Pitch setelah di Filter dengan Kalman Filter
//  Serial.print(kalPitch);
//  Serial.print(",");
//
//  // Menampilkan data Roll sebelum di Filter
//  Serial.print(accRoll);
//  Serial.print(",");
//
//  // Menampilkan data Roll setelah di Filter dengan Kalman Filter
//  Serial.print(kalRoll);
//  Serial.println();



  // Menampilkan data Roll sebelum di Filter
  Serial.print(accYaw);
  Serial.print(",");

  // Menampilkan data Roll setelah di Filter dengan Kalman Filter
  Serial.print(kalYaw);
  Serial.println();

  

}
