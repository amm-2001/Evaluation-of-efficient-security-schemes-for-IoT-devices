#include <Arduino.h>
#include <WiFi.h>
#define ssid "" // SSID of the WiFi network
#define password "" // Password of the WiFi network
#define N 256

WiFiClient client;
const uint16_t port = 8090;
IPAddress server(, , , ); // IP address of the server
const char key[] = ""; // Key to encrypt the message
  int key_len = strlen(key);
unsigned char perm[N];
  char message[] = "";// Message we want to encrypt
  int message_len = strlen(message);

void init_permutation(unsigned char perm[], const char key[], int key_len) {
  
  for (int i = 0; i < N; i++) {
    perm[i] = i;
  }

  int j = 0;
  for (int i = 0; i < N; i++) {
    j = (j + perm[i] + key[i % key_len]) % N;
    unsigned char temp = perm[i];
    perm[i] = perm[j];
    perm[j] = temp;
  }
}


void rc4(unsigned char perm[], char message[], int message_len) {
  int i = 0, j = 0;
  for (int k = 0; k < message_len; k++) {
    i = (i + 1) % N;
    j = (j + perm[i]) % N;
    unsigned char temp = perm[i];
    perm[i] = perm[j];
    perm[j] = temp;
    message[k] ^= perm[(perm[i] + perm[j]) % N];
  }
  
}

void setup() {
  Serial.begin(115200);
  
init_permutation(perm, key, key_len); 
rc4(perm, message, message_len);

Serial.printf("The encrypted message: %s \n",message );

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("connecting...");
  }
 
  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());

 
    if (!client.connect(server, port)) {
 
        Serial.println("Connection to host failed");
        delay(1000);
        return;
    }
 
    Serial.println("Connected to server successful!");

 client.printf("%s", message);
   
 
    Serial.println("Disconnecting...");
    client.stop();
}



void loop() {
  
}