//--------------------------------------------------------
// Incluindo bibliotecas e definindo pinos
//--------------------------------------------------------

#include <LiquidCrystal.h>

LiquidCrystal lcd (5, 6, 7, 8, 9, 10);

int ledVerde = 2;
int ledAmarelo = 3;
int ledVermelho = 4;

int sensorPeso = A0;

int sensorUmidOut = A0;
int sensorUmidIn = A1;

//--------------------------------------------------------
// Estabalecendo variáveis utilizadas no código
//--------------------------------------------------------
  
int peso = 0;

int mensagemAtual = 0;
int mensagemAnterior = 0;

//--------------------------------------------------------
// Definindo tipos dos pinos
//--------------------------------------------------------

void setup() {
 
  Serial.begin(9600);
  
  lcd.begin(16, 2);
  
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
}

//--------------------------------------------------------
// Estabelecendo o loop principal e suas funções
//--------------------------------------------------------

void loop() {
  
  lerPeso();
  
  mensagemAtual = millis();
  if (mensagemAtual - mensagemAnterior >= 5000){
    controleLCD();
    mensagemAnterior = mensagemAtual;
  } 
}

//--------------------------------------------------------
// Relizando a leitura da umidade do peso
//--------------------------------------------------------

void lerPeso() {
  
  peso = analogRead(sensorPeso);
  
  peso = map(peso, 0, 301, 0, 1000); 
  
  controleLEDs();
  
  Serial.println(peso);
}

//--------------------------------------------------------
// Acionando LEDs de acordo com as leituras realizadas
//--------------------------------------------------------

void controleLEDs() {
  if (peso >= 700) {
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, LOW);
  }
  
  else if (peso < 700 && peso >= 500) {
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, HIGH);
    digitalWrite(ledVermelho, LOW);
  }
  else {
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, HIGH);
  }
}

//--------------------------------------------------------
// Imprimindo mensagens no LCD (a cada 5 seg - vide Loop)
//--------------------------------------------------------

void controleLCD() {
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Suprimentos:");
  lcd.setCursor(4, 1);
  lcd.print(String(peso) + "kg");
  
}