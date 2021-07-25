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
String readString; // Variável para guardar os dados da serial.


void setup() {
  Serial.begin(9600); // Inicia a serial para debugging
  radio.begin(); // Inicia o NRF24l01
  radio.openWritingPipe(address); // Abre a comunicação no endereço acima
  radio.setPALevel(RF24_PA_LOW); // Configura o nível do sinal. Quando mais alto, maior o consumo e a distância
  /*
  RF24_PA_MIN = -18dBm, RF24_PA_LOW = -12dBm, RF24_PA_HIGH = -6dBm, RF24_PA_MAX = 0dBm
  */
  radio.stopListening(); // Define o modulo apenas para enviar. Não escuta, só fala

envio[0] = 0; // Armazena na posição 0 o valor 0
envio[1] = 2;
envio[2] = 4;
envio[3] = 8;
envio[4] = 16;
envio[5] = 32;
envio[6] = 64;
envio[7] = 255;
}

void loop() {

  while (Serial.available()){ // Enquanto chegar dados na serial
    delay(3); // Atraso de 3 millis
    char c = Serial.read(); // Cria a variável "c" e armazena o valor da serial
    readString += c; // Adiciona o valor da variável "c" no final da string "readString"
  }

  readString.trim(); // Remove quaisquer espaços no começo ou final da String.

  if (readString.length() > 0) { // Se o tamanho de "readString" for maior que zero
    envio[0] = readString.toInt(); // Armazena na posição 0 o valor INT lido da serial
    radio.write(&envio, sizeof(envio)); // Envia os valores da variável "envio"

  readString = ""; // Limpa os dados de "readString".
  }
}