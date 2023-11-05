int segmentos[] = {2, 3, 4, 5, 6, 7, 8};
const int triggerPin = 13;
const int echoPin = 12;
long duration;
int distance;

void setup() {
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Configurar los pines de los segmentos como salidas
  for (int i = 0; i < 7; i++) {
    pinMode(segmentos[i], OUTPUT);
  }
    Serial.begin(9600);
}

void loop() {
  // Genera un pulso en el pin Trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  // Lee la duración del pulso en el pin Echo
  duration = pulseIn(echoPin, HIGH);

  // Convierte la duración en distancia en centímetros
  distance = duration * 0.034 / 2;

  // Imprime la distancia en el puerto serie
  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  //Muestra el resultado en el display de 7 segmentos
  if(distance < 10){
    mostrarNumero(0);
  }else if(distance < 20){
    mostrarNumero(1);
  }else if(distance < 30){
    mostrarNumero(2);
  }else if(distance < 40){
    mostrarNumero(3);
  }else if(distance < 50){
    mostrarNumero(4);
  }else if(distance < 60){
    mostrarNumero(5);
  }else if(distance < 70){
    mostrarNumero(6);
  }else if(distance < 80){
    mostrarNumero(7);
  }else if(distance < 90){
    mostrarNumero(8);
  }else {
    mostrarNumero(9);
  }
  delay(1000); // Espera un segundo antes de realizar otra medición
  // Imprime l
}

void mostrarNumero(int numero) {
  // Definir los patrones de segmentos para cada número del 0 al 9
  byte patrones[] = {
    B00111111,  // 0
    B00000110,  // 1
    B01011011,  // 2
    B01001111,  // 3
    B01100110,  // 4
    B01101101,  // 5
    B01111101,  // 6
    B00000111,  // 7
    B01111111,  // 8
    B01101111   // 9
  };

  // Mostrar el número en el display de 7 segmentos
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentos[i], bitRead(patrones[numero], i));
  }
}
