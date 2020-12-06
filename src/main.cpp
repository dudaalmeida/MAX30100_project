#include <mbed.h>
#include "MAX30100_PulseOximeter.h"

PulseOximeter pox;
Serial pc(PA_2, PA_3);
Ticker tic;

void bearCallback();
void readSensor();

bool flag = false;
uint8_t spo2;
uint8_t batimentos;


int main() {

  if (!pox.begin(PULSEOXIMETER_DEBUGGINGMODE_PULSEDETECT)) {
    pc.printf("ERRO: falha ao iniciar o pulse oximeter");
    for(;;);
  }

  pox.setOnBeatDetectedCallback(beatCallback);
  tic.attach(&readSensor, 2.0);

  while(1) {
    pox.update();

    if (flag) {
      printf("Batimentos: %d bpm \n", batimentos);
      printf("SPO2: %d % \n", spo2);
      flag = false;
    }
  }
}

void beatCallback() {
  pc.printf("Tum Tum");
}

void readSensor() {
  spo2 = pox.getSpO2();
  batimentos = pox.getHeartRate();
  flag = true;
}
