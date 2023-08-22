#include <DHT.h>
#include <DHT_U.h>

/*
   PROJETO INTEGRADOR: Smart Green
   CURSO: Grad. Engenharia Elétrica
   INSTITUIÇÃO: Universidade Regional Integrada do Alto Uruguai e das Missões - URI
   SKETCH: Irrigação Inteligente
   DATA: 13 maio 2021  
*/
// biblioteca do sensor de temperatura e úmidade relativa do ar 
#include <DHT.h>;
 
// declaração das variáveis como bool, pois o tipo bool pode armazenar dois valores: true (verdadeiro) or (ou) false (falso)
bool leiturasensor;
bool leituraanterior;

void setup() {
  // vamos declarar as entradas e saídas digitais e analógicas do nosso sistema
  
  // Sensor de úmidade do solo
  pinMode(8, INPUT); // declarando que no pino oito, será o sinal de entrada do nosso sensor de úmidade do solo

  // Atuador >> rele, motor, solenoide, válvula
  pinMode(12, OUTPUT); // declarando que no pino 12 será o sinal de saída do nosso atuador
  
  //LEDs indicadores
  pinMode(5, OUTPUT);  //vermelho vai indicar umidade do solo abaixo do recomendado
  pinMode(6, OUTPUT);  //amarelo vai indicar que o sistema esta operando
  pinMode(7, OUTPUT);  //verde vai indicar que o sistema esta com a umidade do solo dentro dos niveis estabelecidos

  #define dht_pin 5; // sensor de temperatura
  pinMode(10, OUTPUT); // cooler de ventilação
  pinMode(A2, INPUT); //sensor de luminosidade
  pinMode(9, OUTPUT); //luz branca para potencializar o cultivo
}

void loop() {

  leiturasensor = digitalRead(8); // Aqui o pino 8 fará a leitura constante do sensor de úmidade e registrará o sinal na variável "leiturasensor"
  analogWrite(9, constrain((analogRead(A2) / 4), 0, 255)); //através da função constrain sera feita a leitura do sensor de luminosidade e ligara a luz branca
  
  // aqui será feito a leitura do sensor de temperátura e acionamento do cooler
  if (-40 + 0.488155 * (analogRead(A1) - 20) >= 40) {
    digitalWrite(10, HIGH);
  } else {
    digitalWrite(10, LOW);
  }

  if (leiturasensor == HIGH) /* o comparador vai verificar se a variável "leiturasensor" vai receber o sinal ligado, assim:*/ {
     //No estado seco
     digitalWrite(5, HIGH);  // vai ligar o LED vermelho
     digitalWrite(7, LOW);   // e desligar o LED verde
  } else /* se não */ {
     //No estado úmido
     digitalWrite(5, LOW);   // vai desligar o LED vermelho
     digitalWrite(7, HIGH);  // e vai ligar o LED verde
  }

  //Ao entrar no estado seco  
  if (leiturasensor && !leituraanterior) /* se, nesta comparação entre as váriáveis "leiturasensor" e "leituraanterior" for diferente */ {
     delay(5000); //passado cinco segundos, se o sistema ainda estiver no estado seco
     digitalWrite(5, LOW);   // vai desligar o LED vermelho
     digitalWrite(6, HIGH);  //e ligar o LED amarelo

     while (digitalRead(8)) /* enquanto o sensor de úmidade estiver com os niveis abaixo do ajustado*/  {
        digitalWrite(12, HIGH);   // o Atuador >> rele, motor, solenoide, válvula vai ser acionado
        delay(500); // passados 5 segundos
        digitalWrite(12, LOW);   // o Atuador >> rele, motor, solenoide, válvula será desligado

        delay(10000); // ele da um pulso para irrigar o solo novamente   
     }
     digitalWrite(6, LOW);  // o LED amarelo vai se desligar
  }
  
  leituraanterior = leiturasensor; //
}
