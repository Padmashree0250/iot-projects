#include <WiFi.h>
#include <ESP_Mail_Client.h>

#define WIFI_SSID "Navi"
#define WIFI_PASSWORD "123456789"

#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465 // Use 465 for SSL

#define AUTHOR_EMAIL "esp32snpn@gmail.com"
#define AUTHOR_PASSWORD "twnx etps zhbz bnnd"

#define RECIPIENT_EMAIL "padmashree0250@gmail.com"

#define led 42
#define BUZZER 6
#define vs 9

SMTPSession smtp;

void smtpCallback(SMTP_Status status);
long measureSum = 0;

long vibration(){
  long measurement = pulseIn (vs, HIGH);
  return measurement;
}

void smtpCallback(SMTP_Status status){
  if (status.success()){
    Serial.println("Email sent successfully");
  }
}

void setup(){
  pinMode(led, OUTPUT);
  pinMode(vs, INPUT);

  Serial.begin(115200);
  Serial.print("Connecting to AP...");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(200);
  }
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop(){
  long measurement = vibration();
  measureSum += measurement;
  delay(50);

  Serial.println(measurement);
  Serial.println(measureSum);
  
  if (measureSum >= 10000){
    digitalWrite(led, HIGH);
    Serial.println("TREMOR Detected!");

    smtp.debug(1); // Enable debug messages
    smtp.callback(smtpCallback); // Set callback function

    // Configure SMTP session with your email credentials
    Session_Config config;
    config.server.host_name = SMTP_HOST;
    config.server.port = SMTP_PORT;
    config.login.email = AUTHOR_EMAIL;
    config.login.password = AUTHOR_PASSWORD;

    SMTP_Message message;
    message.sender.name = "TechnoFuturo";
    message.sender.email = AUTHOR_EMAIL;
    message.subject = "TREMOR!!!";
    message.addRecipient("Navani", RECIPIENT_EMAIL);

    // Email content
    String textMsg = "Alert! Tremor Detected";
    message.text.content = textMsg.c_str();

    // Connect and send email
    if (!smtp.connect(&config)) {
      Serial.println("Connection error");
      return;
    }

    if (!MailClient.sendMail(&smtp, &message, true)) {
      Serial.println("Error sending Email");
    }
  }
  else{
    digitalWrite(led, LOW); 
  }
  measureSum=0;
}