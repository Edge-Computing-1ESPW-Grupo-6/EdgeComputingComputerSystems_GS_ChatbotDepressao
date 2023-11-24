//--------------------------------------------------------
// Incluindo bibliotecas e definindo pinos
//--------------------------------------------------------

#include <LiquidCrystal.h>

LiquidCrystal lcd (2, 3, 4, 5, 6, 7);

int ledVerde = 8;
int ledAmarelo = 9;
int ledVermelho = 10;

int sensorTemp = A2;

int sensorUmidOut = A0;
int sensorUmidIn = A1;

//--------------------------------------------------------
// Estabalecendo variáveis utilizadas no código
//--------------------------------------------------------
  
int tempRaw = 0; 
double tempVolt = 0;
int temp = 0;

const int array_temp = 5;
float valor_temp[array_temp];
int index_temp = 0;
int temp_atual = 0;

int umidSolo = 0;
const int array_umid = 5;
float valor_umid[array_umid];
int index_umid = 0;
int umid_atual = 0;

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
  pinMode(sensorTemp, INPUT);
  pinMode(sensorUmidOut, OUTPUT);
  pinMode(sensorUmidIn, INPUT);
}

//--------------------------------------------------------
// Estabelecendo o loop principal e suas funções
//--------------------------------------------------------

void loop() {
  
  lerUmidSolo();
  
  lerTemperatura();
  
  controleLEDs();
  
  mensagemAtual = millis();
  if (mensagemAtual - mensagemAnterior >= 5000){
    controleLCD();
    mensagemAnterior = mensagemAtual;
  } 
}

//--------------------------------------------------------
// Relizando a leitura da umidade do solo, conversão para 
// porcentagem e armazenamento e média de array
//--------------------------------------------------------

void lerUmidSolo() {
  
  digitalWrite(sensorUmidOut, HIGH);
  delay(10);
  umid_atual = analogRead(A1);
  digitalWrite(sensorUmidOut, LOW);
  
  umid_atual = map(umid_atual, 0, 872, 0, 100);
  
  valor_umid[index_umid] = umid_atual;
  index_umid++;
  if (index_umid >= array_umid) {
    index_umid = 0;
  }
  
  int soma_umid = 0;
  for (int i = 0; i < array_umid; i++) {
    soma_umid += valor_umid[i];
  }
  umidSolo = soma_umid / array_umid;
  
  Serial.println(umidSolo);
}

//--------------------------------------------------------
// Relizando a leitura da temperatura, conversão para 
// celsius e armazenamento e média de array
//--------------------------------------------------------

void lerTemperatura() {
  
  tempRaw = analogRead(sensorTemp);
  tempVolt = (tempRaw / 1023.0) * 5000; // 5000 para resultado em millivots.
  temp_atual = (tempVolt-500) * 0.1;
  
  valor_temp[index_temp] = temp_atual;
  index_temp++;
  if (index_temp >= array_temp) {
    index_temp = 0;
  }
  
  int soma_temp = 0;
  for (int i = 0; i < array_temp; i++) {
    soma_temp += valor_temp[i];
  }
  temp = soma_temp / array_temp;
  
  Serial.println(temp);
}

//--------------------------------------------------------
// Acionando LEDs de acordo com as leituras realizadas
//--------------------------------------------------------

void controleLEDs() {
  if (umidSolo >= 80 && temp <= 25 && temp >= 15) {
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, LOW);
  }
  
  else if (umidSolo < 80 && umidSolo >= 50 || temp < 15 && temp >= 10) {
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
  lcd.setCursor(0, 0);
  lcd.print("Temp. = " + String(temp)+ "C");
  lcd.setCursor(0, 1);
  lcd.print("Umid. Solo = " + String(umidSolo) + "%");
  
}


