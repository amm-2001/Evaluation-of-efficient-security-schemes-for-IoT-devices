/*#include <Arduino.h>
#include "mbedtls/camellia.h"
#include <WiFi.h>

#define ssid "" //SSID of the WiFi network
#define password "" //Password of the WiFi network
const uint16_t port = 8090;
char * key = ""; //Key to encrypt the message
char *input = "";//Message we want to encrypt
unsigned char output[16];
IPAddress server(, , , ); //IP address of the server

void setup() {
  Serial.begin(115200);
    mbedtls_camellia_context ctx;
    //size_t i;

     mbedtls_camellia_init(&ctx);

    // Set the encryption key
    mbedtls_camellia_setkey_enc(&ctx, (const unsigned char*)key, strlen(key)*8);
    
    // Encrypt the plaintext
    
    mbedtls_camellia_crypt_ecb(&ctx, MBEDTLS_CAMELLIA_ENCRYPT, (const unsigned char*)input, output);
    Serial.printf("%s",output);
    // Cleanup
    mbedtls_camellia_free(&ctx);

WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("connecting...");
  }
 
  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());

 
  WiFiClient client;
    if (!client.connect(server, port)) {
 
        Serial.println("Connection to host failed");
 
        delay(1000);
        return;
    }
 
    Serial.println("Connected to server successful!");

 client.printf("%s", output);
   
 
    Serial.println("Disconnecting...");
    client.stop();
}

void loop() {
  // put your main code here, to run repeatedly:
}*/
#include <Arduino.h>
#include "mbedtls/camellia.h"
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
  mbedtls_camellia_context ctx;
  
  token = strtok(input_string, ",");
  
  while (token != NULL) {
   
    token_len = strlen(token);
    char* plaintext[token_len];
    unsigned char output[16];
    unsigned char dec[16];
    memcpy(plaintext, token, token_len);
    
   
    
    // Encrypt plaintext using Camellia
    mbedtls_camellia_init(&ctx);
    mbedtls_camellia_setkey_enc(&ctx, (const unsigned char*)key, strlen(key)*8);
    mbedtls_camellia_crypt_ecb(&ctx, MBEDTLS_CAMELLIA_ENCRYPT, (const unsigned char*)plaintext, output);
    // Print ciphertext
    Serial.printf("Ciphertext: ");
    for (int i = 0; i < token_len; i++) {
      Serial.printf("%c",output[i]);
  
    }
    printf("\n");
    

    mbedtls_camellia_free(&ctx);
    
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