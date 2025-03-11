#ifndef SENSORDATA_H
#define SENSORDATA_H

struct SensorData {
    uint8_t buffer_star1, buffer_star2;
    float latitude, longitude;
    uint8_t temperatura_motor, temperatura_cvt, velocidade, odometro, hora, minuto, mes, ano;
    uint16_t altitude, rpm_motor;
    bool batteryLevel, farol, conct_LAN, low_gas, high_gas;
    uint8_t buffer_end1, buffer_end2;
};

#endif // SENSORDATA_H