int trigPin = 2;
int echoPin = 4;

long zaman;
long distance = 0, distance_old = 0;
int i = 0;


#define sagmotorhiz 11
#define solmotorhiz 6
#define sagmotoron 12
#define solmotoron 8
#define sagmotorarka 10
#define solmotorarka 9

#include <Wire.h>
#include <HMC5883L.h>

HMC5883L compass;
void setup() {

  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);


  pinMode(sagmotorhiz, OUTPUT);
  pinMode(solmotorhiz, OUTPUT);
  pinMode(sagmotoron, OUTPUT);
  pinMode(solmotoron, OUTPUT);
  pinMode(sagmotorarka, OUTPUT);
  pinMode(solmotorarka, OUTPUT);
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

  // Kalibrasyon offset ayarı yapılır. HMC5883L_calibration.ino dosyasına bakın.(Kütüphane dosyasında bulunmaktadır)
  compass.setOffset(-110, -402); // -148 -13 //-127, 78 // -157,-61   -146,-20

}

void loop() {


  if (distance > 0)
  {
    distance_old = distance ;
  }
  // Send ping, get distance in cm

  if (distance <= 0)
  {
    distance = distance_old  ;
  }

  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  zaman = pulseIn(echoPin, HIGH);
  distance = (zaman / 29.1) / 2;
  Serial.print("Uzaklik ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(50);
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
  float headingDegrees = heading * 180 / M_PI;

  // Çıktı
  //  Serial.print(" Heading = ");
  //  Serial.print(heading);
  Serial.print(" Degress = ");
  Serial.print(floor(headingDegrees));
  Serial.println();



  Serial.print(distance);
  Serial.println(" cm");
  //    Serial.print("i degeri =");
  //    Serial.println(i);

  delay(50);
if (distance<20 && i%2==0) {
  sol();
  delay(1000);
  ileri();
  delay(1000);
  sol();
  delay(1000);
  i=i+1;
}
if (distance<20 && i%2==1) {
  sag();
  delay(1000);
  ileri();
  delay(1000);
  sag();
  delay(1000);
  i=i+1;
}
while(distance>20) {
  if(headingDegrees >113) {
    hsol();
    }
    else if (headingDegrees < 93) {
      hsag();
      }
      else {
        ileri();
        }
        }
         delay(50);
}

void ileri()
{
  analogWrite(sagmotorhiz, 255);
  digitalWrite(sagmotoron, 0);
  digitalWrite(sagmotorarka, 1);

  analogWrite(solmotorhiz, 255);
  digitalWrite(solmotoron, 1);
  digitalWrite(solmotorarka, 0);
}

void sol()
{
  analogWrite(sagmotorhiz, 155);
  digitalWrite(sagmotoron, 1);
  digitalWrite(sagmotorarka, 0);

  analogWrite(solmotorhiz, 0);
  digitalWrite(solmotoron, 1);
  digitalWrite(solmotorarka, 0);
}
void hsag()
{
  analogWrite(sagmotorhiz, 255);
  digitalWrite(sagmotoron, 0);
  digitalWrite(sagmotorarka, 1);

  analogWrite(solmotorhiz, 230);
  digitalWrite(solmotoron, 0);
  digitalWrite(solmotorarka, 1);
}
void hsol()
{
  analogWrite(sagmotorhiz, 230);
  digitalWrite(sagmotoron, 0);
  digitalWrite(sagmotorarka, 1);

  analogWrite(solmotorhiz, 255);
  digitalWrite(solmotoron, 1);
  digitalWrite(solmotorarka, 0);
}
void sag()
{
  analogWrite(sagmotorhiz, 0);
  digitalWrite(sagmotoron, 0);
  digitalWrite(sagmotorarka, 1);

  analogWrite(solmotorhiz, 155);
  digitalWrite(solmotoron, 0);
  digitalWrite(solmotorarka, 1);
}
void geri()
{
  analogWrite(sagmotorhiz, 255);
  digitalWrite(sagmotoron, 0);
  digitalWrite(sagmotorarka, 1);

  analogWrite(solmotorhiz, 255);
  digitalWrite(solmotoron, 0);
  digitalWrite(solmotorarka, 1);
}
void dur()
{
  analogWrite(sagmotorhiz, 0);
  digitalWrite(sagmotoron, 0);
  digitalWrite(sagmotorarka, 0);

  analogWrite(solmotorhiz, 0);
  digitalWrite(solmotoron, 0);
  digitalWrite(solmotorarka, 0);
}
