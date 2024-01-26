#include "UltrasonicSensor.h"
#ifdef __linux__ // O usar una directiva más específica si es necesario
#include <pigpio.h>
#else
// Definiciones alternativas o vacías para Windows
#endif
#include <chrono>
#include <thread>

UltrasonicSensor::UltrasonicSensor(int triggerPin, int echoPin) : triggerPin(triggerPin), echoPin(echoPin) {
#ifdef __linux__
    gpioSetMode(triggerPin, PI_OUTPUT);
    gpioSetMode(echoPin, PI_INPUT);
#endif
}

UltrasonicSensor::~UltrasonicSensor() {
    // Limpieza, si es necesaria.
}

void UltrasonicSensor::sendPulse() {
#ifdef __linux__
    gpioWrite(triggerPin, PI_LOW);
    std::this_thread::sleep_for(std::chrono::microseconds(2));
    gpioWrite(triggerPin, PI_HIGH);
    std::this_thread::sleep_for(std::chrono::microseconds(10));
    gpioWrite(triggerPin, PI_LOW);
#endif
}

double UltrasonicSensor::getDistance() {
#ifdef __linux__
// Tu código existente para calcular la distancia
    sendPulse();

    auto start = std::chrono::high_resolution_clock::now();
    while (gpioRead(echoPin) == PI_LOW) {
        start = std::chrono::high_resolution_clock::now();
    }

    auto stop = std::chrono::high_resolution_clock::now();
    while (gpioRead(echoPin) == PI_HIGH) {
        stop = std::chrono::high_resolution_clock::now();
    }

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
    double distanceCm = duration * 0.034 / 2;
    return distanceCm;
#else
    return -1; // O manejar de otra manera cuando no esté en Linux
#endif
}
