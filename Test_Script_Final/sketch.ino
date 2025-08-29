#include <stdint.h>
// #include <Crypto.h> //ChaCha:use library
#include "Crypto.h" //SPECK and ASCON: use file
#include "CryptoLW.h" //ASCON and SPECK with added files
// #include <ChaCha.h>
#include "Ascon128.h"
// #include "Speck.h"
#include <string.h>

// ChaCha chacha;
Ascon128 ascon;
// Speck speck;
 
//Define the key and nonce 
// unsigned char key[32]; //ChaCha
// unsigned char nonce[8]; //ChaCha
// unsigned char counter[4]; //ChaCha

unsigned char key[16]; //ASCON and SPECK
unsigned char nonce[16]; //ASCON

//Define the plaintext and ciphertext
unsigned char plaintext[16]; //ChaCha, SPECK, and ASCON
// unsigned char ciphertext[16]; //SPECK and ChaCha
unsigned char ciphertext[32]; //ASCON 

void setup() {
  Serial.begin(115200);

  //Generate a random key and nonce
  //ChaCha
  // for (int i = 0; i < 32; i++) {
  //   key[i] = random(256);
  // }
  // for (int i = 0; i < 12; i++) {
  //   nonce[i] = random(256); 
  // }

  // chacha.setKey(key, 32);
  // chacha.setIV(nonce, 8);
  // chacha.setCounter(counter, 4);

  //ASCON and SPECK
  for (int i = 0; i < 16; i++) {
    key[i] = random(256);
    nonce[i] = random(256); //ASCON only 
  }

  ascon.setKey(key, 16);
  ascon.setIV(nonce, 16);
  // speck.setKey(key, 128); 

  //Initialize the plaintext with random data
  for (int i = 0; i < 16; i++) {
    plaintext[i] = random(256);
  }

  // Serial.println("Using ChaCha20");
  Serial.println("Using ASCON-128");
  // Serial.println("Using Speck128");
}

void loop() {
  int iterations = 1000;
  unsigned long start_time, end_time;

  // Measure Encryption Speed and Energy Consumption and Print Results
  start_time = micros();

  //ChaCha 
  // for (int i = 0; i < iterations; i++) {
  //   chacha.encrypt(ciphertext, plaintext, 16);
  // }

  //ASCON
  for (int i = 0; i < iterations; i++) {
    ascon.encrypt(ciphertext, plaintext, 16);
  }

  //SPECK
  // for (int i = 0; i < iterations; i++) {
  //   speck.encryptBlock(ciphertext, plaintext);
  // }

  end_time = micros();

  unsigned long time = end_time - start_time;
  float time_ms = (float)time / iterations / 1000.0; //Average time of iterations in milliseconds  
  const float current_consumption = 100.0; //Maximum mA for IoT devices in Running State
  const float voltage = 3.3; //Average Voltage of IoT device
  float energy_consumption = (current_consumption * voltage * time_ms) / 1000.0; //Energy Consumption Approximation

  Serial.println("Encryption time (ms): ");
  Serial.print(time_ms); 
  Serial.println("");
  Serial.println("Energy consumption for Encryption(mj): ");
  Serial.print(energy_consumption);
  Serial.println("");

  //Measure Decryption Speed and Energy Consumption and Print Results
  start_time = micros();
  
  //ChaCha
  // for (int i = 0; i < iterations; i++) {
  //   chacha.decrypt(plaintext, ciphertext, sizeof ciphertext);
  // }

  //ASCON
  for (int i = 0; i < iterations; i++) {
    ascon.decrypt(plaintext, ciphertext, 32);
  }

  //SPECK
  // for (int i = 0; i < iterations; i++) {
  //   speck.decryptBlock(plaintext, ciphertext);
  // }
  
  end_time = micros();

  time = end_time - start_time;
  time_ms = (float)time / iterations / 1000.0;   
  energy_consumption = (current_consumption * voltage * time_ms) / 1000.0; 

  Serial.println("Decryption time (ms): ");
  Serial.print(time_ms); 
  Serial.println("");
  Serial.println("Energy consumption for Decryption(mj): ");
  Serial.print(energy_consumption);
  Serial.println("");

  delay(1000); 
}