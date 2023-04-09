#include <Arduino.h>
#include "mbedtls/aes.h"
#include <WiFi.h>
#define ssid ""// SSID of the WiFi network
#define password ""// Password of the WiFi network
WiFiClient client;
const uint16_t port = 8090;
IPAddress server(, , , );// IP address of the server
void split_and_encrypt(char *input_string) {
  char *token;
  int token_len;
  char * key = "";//Key to encrypt the message
  mbedtls_aes_context aes;
  
  token = strtok(input_string, ",");
  
  while (token != NULL) {
   
    token_len = strlen(token);
    char* plaintext[token_len];
    unsigned char output[16];
    unsigned char dec[16];
    memcpy(plaintext, token, token_len);
    
   
    
    // Encrypt plaintext using AES
    mbedtls_aes_init(&aes);
    mbedtls_aes_setkey_enc(&aes, (const unsigned char*)key, strlen(key)*8);
    mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_ENCRYPT, (const unsigned char*)plaintext, output);
    // Print ciphertext
    Serial.printf("Ciphertext: ");
    for (int i = 0; i < token_len; i++) {
      Serial.printf("%c",output[i]);
      client.printf("%c",output[i]);
    }
    printf("\n");
    

    mbedtls_aes_free(&aes);
    
     token = strtok(NULL, ",");
    
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("connecting...");
  }
   
    if (!client.connect(server, port)) {
 
        Serial.println("Connection to host failed");
 
        delay(1000);
        return;
    }
 
    Serial.println("Connected to server successful!");
  char input_string[] = "";//Message we want to encrypt
  
  split_and_encrypt(input_string);
  Serial.println("Disconnecting...");
    client.stop();
}

void loop() {
  // your loop code here
}