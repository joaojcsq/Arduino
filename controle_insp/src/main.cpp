#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>


RF24 radio(9,10);  // CE, CSN
const byte address[6] = "00001"; // Endereço

byte envio[8]; // Variável para guardar os valores em bytes ( 0 - 255 ) 8bits. Colocar uma posição a mais para /0
/*
f | t | e | d | a  | s  | p | pwm
0 | 1 | 2 | 3 | 4  | 5  | 6 | 7
0 | 2 | 4 | 8 | 16 | 32 | 64| 140 --> 255
*/

void setup() {
  Serial.begin(9600); // Inicia a serial para debugging
  radio.begin(); // Inicia o NRF24l01
  radio.openWritingPipe(address); // Abre a comunicação no endereço acima
  radio.setPALevel(RF24_PA_LOW); // Configura o nível do sinal. Quando mais alto, maior o consumo e a distância
  /*
  RF24_PA_MIN = -18dBm, RF24_PA_LOW = -12dBm, RF24_PA_HIGH = -6dBm, RF24_PA_MAX = 0dBm
  */
  radio.stopListening(); // Define o modulo apenas para enviar. Não escuta, só fala
}

void loop() {
  envio[0] = 0; // Armazena na posição 0 o valor 0
  envio[1] = 2;
  envio[2] = 4;
  envio[3] = 8;
  envio[4] = 16;
  envio[5] = 32;
  envio[6] = 64;
  // envio[7] = 255;
  for (int i = 140; i <= 255; i=i+10) { // Loop para alterar a posição 7
    envio[7] = i; // Abribui o valor de i na posição 7
  radio.write(&envio, sizeof(envio)); // Envia os valores da variável "envio"
  delay(500); // Pequeno delay
  }
}