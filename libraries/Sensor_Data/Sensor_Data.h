#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

#include <cstdlib>
#include <ctime>

struct SensorData {
    uint8_t buffer_star1, buffer_star2;
    float latitude, longitude;
    uint8_t temperatura_motor, temperatura_cvt, velocidade, odometro, hora, minuto, mes, ano;
    uint16_t altitude, rpm_motor;
    bool batteryLevel, farol, conct_LAN, low_gas, high_gas;
    uint8_t buffer_end1, buffer_end2;
};

void preencherSensorData(SensorData* data) {
    std::srand(std::time(0));

    data->buffer_star1 = 38;
    data->buffer_star2 = 12;
    data->latitude = static_cast<float>(std::rand()) / RAND_MAX * 180.0f - 90.0f;
    data->longitude = static_cast<float>(std::rand()) / RAND_MAX * 360.0f - 180.0f;
    data->temperatura_motor = std::rand() % 80;
    data->temperatura_cvt = std::rand() % 80;
    data->velocidade = std::rand() % 56;
    data->odometro = std::rand() % 256;
    data->hora = std::rand() % 24;
    data->minuto = std::rand() % 60;
    data->mes = std::rand() % 12 + 1;
    data->ano = std::rand() % 100; // Assumindo um valor de 0 a 99 para o ano
    data->altitude = std::rand() % 65536;
    data->rpm_motor = std::rand() % 65536;
    data->batteryLevel = std::rand() % 2;
    data->farol = std::rand() % 2;
    data->conct_LAN = std::rand() % 2;
    data->low_gas = std::rand() % 2;
    data->high_gas = std::rand() % 2;
    data->buffer_end1 = 38;
    data->buffer_end2 = 12;
}

std::string sensorDataToString(SensorData* data) {
    char buffer[512];
    sprintf(buffer, 
            "SensorData: buffer_star1=%u, buffer_star2=%u, latitude=%.6f, longitude=%.6f, "
            "temperatura_motor=%u, temperatura_cvt=%u, velocidade=%u, odometro=%u, "
            "hora=%u, minuto=%u, mes=%u, ano=%u, altitude=%u, rpm_motor=%u, "
            "batteryLevel=%d, farol=%d, conct_LAN=%d, low_gas=%d, high_gas=%d, "
            "buffer_end1=%u, buffer_end2=%u",
            data->buffer_star1, data->buffer_star2, data->latitude, data->longitude, 
            data->temperatura_motor, data->temperatura_cvt, data->velocidade, data->odometro, 
            data->hora, data->minuto, data->mes, data->ano, data->altitude, data->rpm_motor, 
            data->batteryLevel, data->farol, data->conct_LAN, data->low_gas, data->high_gas, 
            data->buffer_end1, data->buffer_end2);

    return std::string(buffer);
}

#endif // SENSORDATA_H