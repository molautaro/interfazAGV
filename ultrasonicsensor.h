#ifndef ULTRASONICSENSOR_H
#define ULTRASONICSENSOR_H

class UltrasonicSensor {
public:
    UltrasonicSensor(int triggerPin, int echoPin);
    ~UltrasonicSensor();
    double getDistance(); // Devuelve la distancia en centímetros.

private:
    int triggerPin;
    int echoPin;
    void sendPulse();
};

#endif // ULTRASONICSENSOR_H
