#include <Wire.h>
#include <HMC5883L.h>

HMC5883L compass;

void setup()
{
Serial.begin(9600);

//HMC5883L Başlatılır…
Serial.println("Baslatiliyor HMC5883L");
while (!compass.begin())
{
Serial.println("Ölçüm yapılamıyor! Kablo bağlantılarını kontrol edin");
delay(500);
}

// Ölçüm menzili kurulur
compass.setRange(HMC5883L_RANGE_1_3GA);

// Ölçüm modu kurulur
compass.setMeasurementMode(HMC5883L_CONTINOUS);

// Data oranı
compass.setDataRate(HMC5883L_DATARATE_30HZ);

// Örnekleme sayısı ayarlanır
compass.setSamples(HMC5883L_SAMPLES_8);

// Kalibrasyon offset ayarı yapılır. 
compass.setOffset(2,22); // -148 -13 //-127, 78 // -157,-61 // -146,-20
}

void loop()
{
Vector norm = compass.readNormalize();

// Başlık hesaplanır
float heading = atan2(norm.YAxis, norm.XAxis);
///////////////////AŞAĞIDAKİ NOTU OKUYUNUZ.
float declinationAngle = (5.0 + (24.0 / 60.0)) / (180 / M_PI);
heading += declinationAngle;
//////////////////
// 0 dereceden küçükse ve 360 dereceden büyükse
if (heading < 0)
{
heading += 2 * PI;
}

if (heading > 2 * PI)
{
heading -= 2 * PI;
}

// Açı değerine dönüşüm yapılır.
float headingDegrees = heading * 180/M_PI;

// Çıktı
Serial.print(" Heading = ");
Serial.print(heading);
Serial.print(" Degress = ");
Serial.print(floor(headingDegrees));
Serial.println();

delay(100);
}
