#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "kyber_includes.h"
#include "randombytes.h"
#include <DHT.h>

// Kyber declarations
extern "C" {
  int PQCLEAN_MLKEM512_CLEAN_crypto_kem_keypair(uint8_t *pk, uint8_t *sk);
  int PQCLEAN_MLKEM512_CLEAN_crypto_kem_enc(uint8_t *ct, uint8_t *ss, const uint8_t *pk);
  int PQCLEAN_MLKEM512_CLEAN_crypto_kem_dec(uint8_t *ss, const uint8_t *ct, const uint8_t *sk);
  void kyber_rng_init(void);
}

// LCD 20x4
LiquidCrystal_I2C lcd(0x27, 20, 4);

// Kyber buffers
uint8_t pk[CRYPTO_PUBLICKEYBYTES];
uint8_t sk[CRYPTO_SECRETKEYBYTES];
uint8_t ct[CRYPTO_CIPHERTEXTBYTES];
uint8_t ss_enc[CRYPTO_BYTES];
uint8_t ss_dec[CRYPTO_BYTES];

// DHT11 config
#define DHTPIN PA0       
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(PD14, OUTPUT); // Red LED
  pinMode(PD15, OUTPUT); // Blue LED
  digitalWrite(PD14, LOW);
  digitalWrite(PD15, LOW);

  Serial.begin(115200);
  lcd.init(); lcd.backlight(); lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Kyber DHT11 Demo");

  dht.begin();
  kyber_rng_init();
  PQCLEAN_MLKEM512_CLEAN_crypto_kem_keypair(pk, sk);

  delay(2000);
}

void loop() {
  lcd.clear();


  float temperature = dht.readTemperature();

  if (isnan(temperature)) {
    lcd.setCursor(0, 0);
    lcd.print("Sensor error!");
    delay(1000);
    return;
  }


  if (temperature > 255) temperature = 255;
  uint8_t tempRaw = (uint8_t)(temperature + 0.5);

  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(tempRaw);
  lcd.print("C ");


  pk[0] = tempRaw;

  unsigned long startTime = micros();
  PQCLEAN_MLKEM512_CLEAN_crypto_kem_enc(ct, ss_enc, pk);
 
  PQCLEAN_MLKEM512_CLEAN_crypto_kem_dec(ss_dec, ct, sk);
   unsigned long endTime = micros();
  unsigned long encTimeNs = (endTime - startTime) * 1000;
  uint8_t tempDecrypted = pk[0];  
  //lcd.setCursor(0, 3);
  lcd.print("D:");
  lcd.print(tempDecrypted);
  lcd.print("C ns:");
  lcd.print(encTimeNs);  
  lcd.print("ns");
 

lcd.setCursor(0, 1);
lcd.print("Enc:");

for (int i = 0; i < 10; i++) {
  lcd.setCursor(4 + i * 2, 1); 
  if (ct[i] < 16) lcd.print('0');
  lcd.print(ct[i], HEX);
}

lcd.setCursor(0, 2);
for (int i = 10; i < 20; i++) {
  if (ct[i] < 16) lcd.print('0');
  lcd.print(ct[i], HEX);
}

  bool ok = (tempRaw == tempDecrypted);
  digitalWrite(ok ? PD14 : PD15, HIGH);

  Serial.print("Encrypted ct: ");
  for (int i = 0; i < CRYPTO_CIPHERTEXTBYTES; i++) {
    if (ct[i] < 16) Serial.print('0');
    Serial.print(ct[i], HEX);
  }
  Serial.println();

  delay(1000);
  //digitalWrite(PD14, LOW); digitalWrite(PD15, LOW);
}
