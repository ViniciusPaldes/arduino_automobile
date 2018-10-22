// Carro bluetooth controlado por iPhone
// Criado: 07/11/15
// Por: Vinícius Paldês

#include <ST_HW_HC_SR04.h>
#include <Servo.h> 
 
Servo myservo;

ST_HW_HC_SR04 ultrasonicSensor(A0, A1); // ST_HW_HC_SR04(TRIG, ECHO)


#define SR_GRAU_INICIAL 30
#define SR_GRAU_FINAL 120
#define SR_GRAU_PASSO 20

// Motor A
#define MT_EN_A 2
#define MT_IN_1 3
#define MT_IN_2 4

// Motor B
#define MT_EN_B 7
#define MT_IN_3 5
#define MT_IN_4 6

#define BT_RXD D1
#define BT_TXD D0 

boolean emMovimento = false;
void setup()
{
  Serial.begin(9600);
  myservo.attach(8);
  setupMotor();
  delay(1000);
  Serial.println("======INICIANDO O CARRO======");
  acelerar();
}


/**
 * Ativa os motores A e B e ativa as portas seriais 1,2,3,4
 */
void setupMotor() {
  pinMode(MT_EN_A, OUTPUT);
  pinMode(MT_EN_B, OUTPUT);
  pinMode(MT_IN_1, OUTPUT);
  pinMode(MT_IN_2, OUTPUT);
  pinMode(MT_IN_3, OUTPUT);
  pinMode(MT_IN_4, OUTPUT);
}


void loop()
{

  //Girar direita para esquerda 30º para 120ª
  for (int angulo = SR_GRAU_INICIAL; angulo < SR_GRAU_FINAL; angulo+=SR_GRAU_PASSO) {
//    myservo.write(angulo);
    checkDistance();
    delay(300);
  }

  // Girar esquerda para direita 120º para 30º
  for (int angulo = SR_GRAU_FINAL; angulo > SR_GRAU_INICIAL; angulo-=SR_GRAU_PASSO) {
//    myservo.write(angulo);
    checkDistance();
    delay(300);
  }
}

void checkDistance() {
  // Recupera o tempo do pulso ultrasônico
  int hitTime = ultrasonicSensor.getHitTime();
  // Calcula a distância em CM
  int distanceInCm = hitTime / 28;
  
//  Serial.print("HitTime: ");
//  Serial.println(hitTime);
//  Serial.print("Distance In CM: ");
//  Serial.println(distanceInCm);

  if (emMovimento && distanceInCm != 0 && distanceInCm < 20) {
    pausar();
  }
}

void acelerar() {
  Serial.println("Acelerando");
  emMovimento = true;
  digitalWrite(MT_IN_1, LOW);
  digitalWrite(MT_IN_2, HIGH);
  digitalWrite(MT_IN_3, HIGH);
  digitalWrite(MT_IN_4, LOW); 
  analogWrite(MT_EN_A, 255);
  analogWrite(MT_EN_B, 255);
}

void pausar() {
  Serial.println("Parando");
  emMovimento = false;
  digitalWrite(MT_IN_1, LOW);
  digitalWrite(MT_IN_2, LOW);
  digitalWrite(MT_IN_3, LOW);
  digitalWrite(MT_IN_4, LOW); 
  analogWrite(MT_EN_A, 255);
  analogWrite(MT_EN_B, 255);
}

 
/* Explicações gerais necessárias para avanço e catálogo de conhecimento
 * 
 * Sequência LCD Parallel
  Verde Vazio Branco Preto Roxo Azul Verde Amarelo Laranja Vermelho (Acima Laranja)
  marrom vermelho laranja amarelo
  rxd    txd      gnd     5v

  txd   rxd    -   +



  xinda keyes - IR receiver

  // Os 4 LOW -> Nada acontece
  // Os 4 HIGH -> Nada acontece
  // O primeiro e o segundo HIGH, o terceiro e o quarto LOW -> Nada acontece
  // O primeiro e o terceiro HIGH, o segundo e o quarto LOW -> Vira para direita
  // O primeiro e o quarto HIGH , o segundo e o terceiro LOW -> Vai para trás
  // O segundo e o terceiro HIGH , o primeiro e o quarto LOW -> Vai para frente
  // O terceiro e o quarto HIGH , o primeiro e o segundo LOW -> Vai para trás
  // Apenas o primeiro LOW -> Vira esquerda
  // Apenas o segundo LOW -> Vira esquerda de ré
  // Apenas o terceiro LOW -> Vira direita de ré
  // Apenas o quarto LOW -> Vira para direita
  */

