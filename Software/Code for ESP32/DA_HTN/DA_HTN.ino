#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClient.h>
#include <Arduino_JSON.h>
#include <HardwareSerial.h>
#include <ctime>

#include "images.h"
#include "weatherAPI.h"

#define Tx_PIN 21
#define Rx_PIN 20

String received_str;
uint64_t check_data_result = 0;
unsigned long start_time;
uint32_t error_count = 0;

void check_data(const uint16_t *data, uint16_t index)
{
    if ((index % 2) != 0)
    {
        check_data_result += (data[index - 1] + data[index]) / 64;
    }
}

void check_data_large(const uint32_t *data, uint16_t index)
{
    if ((index % 2) != 0)
    {
        check_data_result += (data[index - 1] + data[index]) / 64;
    }
}

void handshaking()
{
    received_str = "";
    received_str = Serial1.readString();
    if (received_str == "")
    {
        return;
    }
    else
    {
        Serial.println(received_str);
    }
    if (received_str == "STM32: Get INIT")
    {
        Serial.println("Received STM32: Get INIT command");
        delay(5);
        Serial1.println("ESP32: ACK");
        Serial.println("Sending ACK");
        start_time = millis();

        while ((Serial1.readString() != "STM32: OK"))
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 4000)
            {
                Serial1.println("ESP32: ACK");
                Serial.println("Sending ACK again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        // lcd_thermometer
        delay(5);
        Serial1.println("ESP32: SEND lcd_thermometer");
        Serial.println("Sending lcd_thermometer");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND lcd_thermometer");
                Serial.println("Sending lcd_thermometer again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < lcd_thermometer_size; i++)
        {
            Serial1.println(lcd_thermometer[i]);
            Serial.println(lcd_thermometer[i]);
            check_data(lcd_thermometer, i);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < lcd_thermometer_size; i++)
                {
                    Serial1.println(lcd_thermometer[i]);
                    Serial.println(lcd_thermometer[i]);
                    check_data(lcd_thermometer, i);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // lcd_thermometer_small
        delay(5);
        Serial1.println("ESP32: SEND lcd_thermometer_small");
        Serial.println("Sending lcd_thermometer_small");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial.println("Sending lcd_thermometer_small again");
                Serial1.println("ESP32: SEND lcd_thermometer_small");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < lcd_thermometer_small_size; i++)
        {
            Serial1.println(lcd_thermometer_small[i]);
            Serial.println(lcd_thermometer_small[i]);
            check_data(lcd_thermometer_small, i);
            // delay(1);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < lcd_thermometer_small_size; i++)
                {
                    Serial1.println(lcd_thermometer_small[i]);
                    Serial.println(lcd_thermometer_small[i]);
                    check_data(lcd_thermometer_small, i);
                    // delay(1);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // lcd_humidity
        delay(5);
        Serial1.println("ESP32: SEND lcd_humidity");
        Serial.println("Sending lcd_humidity");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial.println("Sending lcd_humidity again");
                Serial1.println("ESP32: SEND lcd_humidity");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < lcd_humidity_size; i++)
        {
            Serial1.println(lcd_humidity[i]);
            Serial.println(lcd_humidity[i]);
            check_data(lcd_humidity, i);
            // delay(1);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < lcd_humidity_size; i++)
                {
                    Serial1.println(lcd_humidity[i]);
                    Serial.println(lcd_humidity[i]);
                    check_data(lcd_humidity, i);
                    // delay(1);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // lcd_humidity_small
        delay(5);
        Serial1.println("ESP32: SEND lcd_humidity_small");
        Serial.println("Sending lcd_humidity_small");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial.println("Sending lcd_humidity_small again");
                Serial1.println("ESP32: SEND lcd_humidity_small");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < lcd_humidity_small_size; i++)
        {
            Serial1.println(lcd_humidity_small[i]);
            Serial.println(lcd_humidity_small[i]);
            check_data(lcd_humidity_small, i);
            // delay(1);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < lcd_humidity_small_size; i++)
                {
                    Serial1.println(lcd_humidity_small[i]);
                    Serial.println(lcd_humidity_small[i]);
                    check_data(lcd_humidity_small, i);
                    // delay(1);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // lcd_schedule
        delay(5);
        Serial1.println("ESP32: SEND lcd_schedule");
        Serial.println("Sending lcd_schedule");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND lcd_schedule");
                Serial.println("Sending lcd_schedule again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < lcd_schedule_size; i++)
        {
            Serial1.println(lcd_schedule[i]);
            Serial.println(lcd_schedule[i]);
            check_data(lcd_schedule, i);
            // delay(1);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < lcd_schedule_size; i++)
                {
                    Serial1.println(lcd_schedule[i]);
                    Serial.println(lcd_schedule[i]);
                    check_data(lcd_schedule, i);
                    // delay(1);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // lcd_hbspo2
        delay(5);
        Serial1.println("ESP32: SEND lcd_hbspo2");
        Serial.println("Sending lcd_hbspo2");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND lcd_hbspo2");
                Serial.println("Sending lcd_hbspo2 again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < lcd_hbspo2_size; i++)
        {
            Serial1.println(lcd_hbspo2[i]);
            Serial.println(lcd_hbspo2[i]);
            check_data(lcd_hbspo2, i);
            // delay(1);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < lcd_hbspo2_size; i++)
                {
                    Serial1.println(lcd_hbspo2[i]);
                    Serial.println(lcd_hbspo2[i]);
                    check_data(lcd_hbspo2, i);
                    // delay(1);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // lcd_weather
        delay(5);
        Serial1.println("ESP32: SEND lcd_weather");
        Serial.println("Sending lcd_weather");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND lcd_weather");
                Serial.println("Sending lcd_weather again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < lcd_weather_size; i++)
        {
            Serial1.println(lcd_weather[i]);
            Serial.println(lcd_weather[i]);
            check_data(lcd_weather, i);
            // delay(1);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < lcd_weather_size; i++)
                {
                    Serial1.println(lcd_weather[i]);
                    Serial.println(lcd_weather[i]);
                    check_data(lcd_weather, i);
                    // delay(1);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // lcd_settings
        delay(5);
        Serial1.println("ESP32: SEND lcd_settings");
        Serial.println("Sending lcd_settings");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND lcd_settings");
                Serial.println("Sending lcd_settings again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < lcd_settings_size; i++)
        {
            Serial1.println(lcd_settings[i]);
            Serial.println(lcd_settings[i]);
            check_data(lcd_settings, i);
            // delay(1);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < lcd_settings_size; i++)
                {
                    Serial1.println(lcd_settings[i]);
                    Serial.println(lcd_settings[i]);
                    check_data(lcd_settings, i);
                    // delay(1);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // lcd_game
        delay(5);
        Serial1.println("ESP32: SEND lcd_game");
        Serial.println("Sending lcd_game");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND lcd_game");
                Serial.println("Sending lcd_game again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < lcd_game_size; i++)
        {
            Serial1.println(lcd_game[i]);
            Serial.println(lcd_game[i]);
            check_data(lcd_game, i);
            // delay(1);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < lcd_game_size; i++)
                {
                    Serial1.println(lcd_game[i]);
                    Serial.println(lcd_game[i]);
                    check_data(lcd_game, i);
                    // delay(1);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // // lcd_microsd
        // delay(5);
        // Serial1.println("ESP32: SEND lcd_microsd");
        // Serial.println("Sending lcd_microsd");
        // start_time = millis();

        // while (Serial1.readString() != "STM32: OK") {
        //   if (error_count == 10) {
        //     error_count = 0;
        //     return;
        //   }
        //   if ((millis() - start_time) > 2000) {
        //     Serial1.println("ESP32: SEND lcd_microsd");
        //     Serial.println("Sending lcd_microsd again");
        //     start_time = millis();
        //     error_count++;
        //   }
        // }
        // error_count = 0;

        // delay(50);
        // Serial.println("Sending data:");
        // for (int i = 0; i < lcd_microsd_size; i++) {
        //   Serial1.println(lcd_microsd[i]);
        //   Serial.println(lcd_microsd[i]);
        //   check_data(lcd_microsd, i);
        //   // delay(1);
        // }
        // Serial1.println(check_data_result);
        // Serial.print("Data checksum: ");
        // Serial.println(check_data_result);
        // start_time = millis();

        // while (Serial1.readString() != "STM32: OK") {
        //   if (error_count == 10) {
        //     error_count = 0;
        //     return;
        //   }
        //   if ((millis() - start_time) > 100000) {
        //     check_data_result = 0;
        //     Serial.println("Sending data again:");
        //     for (int i = 0; i < lcd_microsd_size; i++) {
        //       Serial1.println(lcd_microsd[i]);
        //       Serial.println(lcd_microsd[i]);
        //       check_data(lcd_microsd, i);
        //       // delay(1);
        //     }
        //     Serial1.println(check_data_result);
        //     Serial.print("Data checksum: ");
        //     Serial.println(check_data_result);
        //     start_time = millis();
        //     error_count++;
        //   }
        // }
        // check_data_result = 0;
        // error_count = 0;

        // lcd_01d
        delay(5);
        Serial1.println("ESP32: SEND lcd_01d");
        Serial.println("Sending lcd_01d");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND lcd_01d");
                Serial.println("Sending lcd_01d again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < lcd_01d_size; i++)
        {
            Serial1.println(lcd_01d[i]);
            Serial.println(lcd_01d[i]);
            check_data(lcd_01d, i);
            // delay(1);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < lcd_01d_size; i++)
                {
                    Serial1.println(lcd_01d[i]);
                    Serial.println(lcd_01d[i]);
                    check_data(lcd_01d, i);
                    // delay(1);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // lcd_01n
        delay(5);
        Serial1.println("ESP32: SEND lcd_01n");
        Serial.println("Sending lcd_01n");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND lcd_01n");
                Serial.println("Sending lcd_01n again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < lcd_01n_size; i++)
        {
            Serial1.println(lcd_01n[i]);
            Serial.println(lcd_01n[i]);
            check_data(lcd_01n, i);
            // delay(1);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < lcd_01n_size; i++)
                {
                    Serial1.println(lcd_01n[i]);
                    Serial.println(lcd_01n[i]);
                    check_data(lcd_01n, i);
                    // delay(1);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // lcd_02d
        delay(5);
        Serial1.println("ESP32: SEND lcd_02d");
        Serial.println("Sending lcd_02d");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND lcd_02d");
                Serial.println("Sending lcd_02d again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < lcd_02d_size; i++)
        {
            Serial1.println(lcd_02d[i]);
            Serial.println(lcd_02d[i]);
            check_data(lcd_02d, i);
            // delay(1);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < lcd_02d_size; i++)
                {
                    Serial1.println(lcd_02d[i]);
                    Serial.println(lcd_02d[i]);
                    check_data(lcd_02d, i);
                    // delay(1);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // lcd_02n
        delay(5);
        Serial1.println("ESP32: SEND lcd_02n");
        Serial.println("Sending lcd_02n");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND lcd_02n");
                Serial.println("Sending lcd_02n again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < lcd_02n_size; i++)
        {
            Serial1.println(lcd_02n[i]);
            Serial.println(lcd_02n[i]);
            check_data(lcd_02n, i);
            // delay(1);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < lcd_02n_size; i++)
                {
                    Serial1.println(lcd_02n[i]);
                    Serial.println(lcd_02n[i]);
                    check_data(lcd_02n, i);
                    // delay(1);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // lcd_03dn
        delay(5);
        Serial1.println("ESP32: SEND lcd_03dn");
        Serial.println("Sending lcd_03dn");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND lcd_03dn");
                Serial.println("Sending lcd_03dn again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < lcd_03dn_size; i++)
        {
            Serial1.println(lcd_03dn[i]);
            Serial.println(lcd_03dn[i]);
            check_data(lcd_03dn, i);
            // delay(1);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < lcd_03dn_size; i++)
                {
                    Serial1.println(lcd_03dn[i]);
                    Serial.println(lcd_03dn[i]);
                    check_data(lcd_03dn, i);
                    // delay(1);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // lcd_04dn
        delay(5);
        Serial1.println("ESP32: SEND lcd_04dn");
        Serial.println("Sending lcd_04dn");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND lcd_04dn");
                Serial.println("Sending lcd_04dn again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < lcd_04dn_size; i++)
        {
            Serial1.println(lcd_04dn[i]);
            Serial.println(lcd_04dn[i]);
            check_data(lcd_04dn, i);
            // delay(1);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < lcd_04dn_size; i++)
                {
                    Serial1.println(lcd_04dn[i]);
                    Serial.println(lcd_04dn[i]);
                    check_data(lcd_04dn, i);
                    // delay(1);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // lcd_09dn
        delay(5);
        Serial1.println("ESP32: SEND lcd_09dn");
        Serial.println("Sending lcd_09dn");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND lcd_09dn");
                Serial.println("Sending lcd_09dn again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < lcd_09dn_size; i++)
        {
            Serial1.println(lcd_09dn[i]);
            Serial.println(lcd_09dn[i]);
            check_data(lcd_09dn, i);
            // delay(1);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < lcd_09dn_size; i++)
                {
                    Serial1.println(lcd_09dn[i]);
                    Serial.println(lcd_09dn[i]);
                    check_data(lcd_09dn, i);
                    // delay(1);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // lcd_10d
        delay(5);
        Serial1.println("ESP32: SEND lcd_10d");
        Serial.println("Sending lcd_10d");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND lcd_10d");
                Serial.println("Sending lcd_10d again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < lcd_10d_size; i++)
        {
            Serial1.println(lcd_10d[i]);
            Serial.println(lcd_10d[i]);
            check_data(lcd_10d, i);
            // delay(1);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < lcd_10d_size; i++)
                {
                    Serial1.println(lcd_10d[i]);
                    Serial.println(lcd_10d[i]);
                    check_data(lcd_10d, i);
                    // delay(1);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // lcd_10n
        delay(5);
        Serial1.println("ESP32: SEND lcd_10n");
        Serial.println("Sending lcd_10n");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND lcd_10n");
                Serial.println("Sending lcd_10n again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < lcd_10n_size; i++)
        {
            Serial1.println(lcd_10n[i]);
            Serial.println(lcd_10n[i]);
            check_data(lcd_10n, i);
            // delay(1);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < lcd_10n_size; i++)
                {
                    Serial1.println(lcd_10n[i]);
                    Serial.println(lcd_10n[i]);
                    check_data(lcd_10n, i);
                    // delay(1);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // lcd_11dn
        delay(5);
        Serial1.println("ESP32: SEND lcd_11dn");
        Serial.println("Sending lcd_11dn");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND lcd_11dn");
                Serial.println("Sending lcd_11dn again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < lcd_11dn_size; i++)
        {
            Serial1.println(lcd_11dn[i]);
            Serial.println(lcd_11dn[i]);
            check_data(lcd_11dn, i);
            // delay(1);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < lcd_11dn_size; i++)
                {
                    Serial1.println(lcd_11dn[i]);
                    Serial.println(lcd_11dn[i]);
                    check_data(lcd_11dn, i);
                    // delay(1);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // lcd_wind
        delay(5);
        Serial1.println("ESP32: SEND lcd_wind");
        Serial.println("Sending lcd_wind");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND lcd_wind");
                Serial.println("Sending lcd_wind again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < lcd_wind_size; i++)
        {
            Serial1.println(lcd_wind[i]);
            Serial.println(lcd_wind[i]);
            check_data(lcd_wind, i);
            // delay(1);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < lcd_wind_size; i++)
                {
                    Serial1.println(lcd_wind[i]);
                    Serial.println(lcd_wind[i]);
                    check_data(lcd_wind, i);
                    // delay(1);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // lcd_50d
        delay(5);
        Serial1.println("ESP32: SEND lcd_50d");
        Serial.println("Sending lcd_50d");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND lcd_50d");
                Serial.println("Sending lcd_50d again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < lcd_50d_size; i++)
        {
            Serial1.println(lcd_50d[i]);
            Serial.println(lcd_50d[i]);
            check_data(lcd_50d, i);
            // delay(1);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < lcd_50d_size; i++)
                {
                    Serial1.println(lcd_50d[i]);
                    Serial.println(lcd_50d[i]);
                    check_data(lcd_50d, i);
                    // delay(1);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // lcd_01d_small
        delay(5);
        Serial1.println("ESP32: SEND lcd_01d_small");
        Serial.println("Sending lcd_01d_small");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND lcd_01d_small");
                Serial.println("Sending lcd_01d_small again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < lcd_01d_small_size; i++)
        {
            Serial1.println(lcd_01d_small[i]);
            Serial.println(lcd_01d_small[i]);
            check_data(lcd_01d_small, i);
            // delay(1);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < lcd_01d_small_size; i++)
                {
                    Serial1.println(lcd_01d_small[i]);
                    Serial.println(lcd_01d_small[i]);
                    check_data(lcd_01d_small, i);
                    // delay(1);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // lcd_01n_small
        delay(5);
        Serial1.println("ESP32: SEND lcd_01n_small");
        Serial.println("Sending lcd_01n_small");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND lcd_01n_small");
                Serial.println("Sending lcd_01n_small again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < lcd_01n_small_size; i++)
        {
            Serial1.println(lcd_01n_small[i]);
            Serial.println(lcd_01n_small[i]);
            check_data(lcd_01n_small, i);
            // delay(1);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < lcd_01n_small_size; i++)
                {
                    Serial1.println(lcd_01n_small[i]);
                    Serial.println(lcd_01n_small[i]);
                    check_data(lcd_01n_small, i);
                    // delay(1);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // lcd_02d_small
        delay(5);
        Serial1.println("ESP32: SEND lcd_02d_small");
        Serial.println("Sending lcd_02d_small");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND lcd_02d_small");
                Serial.println("Sending lcd_02d_small again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < lcd_02d_small_size; i++)
        {
            Serial1.println(lcd_02d_small[i]);
            Serial.println(lcd_02d_small[i]);
            check_data(lcd_02d_small, i);
            // delay(1);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < lcd_02d_small_size; i++)
                {
                    Serial1.println(lcd_02d_small[i]);
                    Serial.println(lcd_02d_small[i]);
                    check_data(lcd_02d_small, i);
                    // delay(1);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // lcd_02n_small
        delay(5);
        Serial1.println("ESP32: SEND lcd_02n_small");
        Serial.println("Sending lcd_02n_small");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND lcd_02n_small");
                Serial.println("Sending lcd_02n_small again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < lcd_02n_small_size; i++)
        {
            Serial1.println(lcd_02n_small[i]);
            Serial.println(lcd_02n_small[i]);
            check_data(lcd_02n_small, i);
            // delay(1);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < lcd_02n_small_size; i++)
                {
                    Serial1.println(lcd_02n_small[i]);
                    Serial.println(lcd_02n_small[i]);
                    check_data(lcd_02n_small, i);
                    // delay(1);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // lcd_03dn_small
        delay(5);
        Serial1.println("ESP32: SEND lcd_03dn_small");
        Serial.println("Sending lcd_03dn_small");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND lcd_03dn_small");
                Serial.println("Sending lcd_03dn_small again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < lcd_03dn_small_size; i++)
        {
            Serial1.println(lcd_03dn_small[i]);
            Serial.println(lcd_03dn_small[i]);
            check_data(lcd_03dn_small, i);
            // delay(1);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < lcd_03dn_small_size; i++)
                {
                    Serial1.println(lcd_03dn_small[i]);
                    Serial.println(lcd_03dn_small[i]);
                    check_data(lcd_03dn_small, i);
                    // delay(1);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // lcd_04dn_small
        delay(5);
        Serial1.println("ESP32: SEND lcd_04dn_small");
        Serial.println("Sending lcd_04dn_small");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND lcd_04dn_small");
                Serial.println("Sending lcd_04dn_small again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < lcd_04dn_small_size; i++)
        {
            Serial1.println(lcd_04dn_small[i]);
            Serial.println(lcd_04dn_small[i]);
            check_data(lcd_04dn_small, i);
            // delay(1);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < lcd_04dn_small_size; i++)
                {
                    Serial1.println(lcd_04dn_small[i]);
                    Serial.println(lcd_04dn_small[i]);
                    check_data(lcd_04dn_small, i);
                    // delay(1);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // lcd_09dn_small
        delay(5);
        Serial1.println("ESP32: SEND lcd_09dn_small");
        Serial.println("Sending lcd_09dn_small");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND lcd_09dn_small");
                Serial.println("Sending lcd_09dn_small again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < lcd_09dn_small_size; i++)
        {
            Serial1.println(lcd_09dn_small[i]);
            Serial.println(lcd_09dn_small[i]);
            check_data(lcd_09dn_small, i);
            // delay(1);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < lcd_09dn_small_size; i++)
                {
                    Serial1.println(lcd_09dn_small[i]);
                    Serial.println(lcd_09dn_small[i]);
                    check_data(lcd_09dn_small, i);
                    // delay(1);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // lcd_10d_small
        delay(5);
        Serial1.println("ESP32: SEND lcd_10d_small");
        Serial.println("Sending lcd_10d_small");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND lcd_10d_small");
                Serial.println("Sending lcd_10d_small again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < lcd_10d_small_size; i++)
        {
            Serial1.println(lcd_10d_small[i]);
            Serial.println(lcd_10d_small[i]);
            check_data(lcd_10d_small, i);
            // delay(1);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < lcd_10d_small_size; i++)
                {
                    Serial1.println(lcd_10d_small[i]);
                    Serial.println(lcd_10d_small[i]);
                    check_data(lcd_10d_small, i);
                    // delay(1);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // lcd_10n_small
        delay(5);
        Serial1.println("ESP32: SEND lcd_10n_small");
        Serial.println("Sending lcd_10n_small");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND lcd_10n_small");
                Serial.println("Sending lcd_10n_small again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < lcd_10n_small_size; i++)
        {
            Serial1.println(lcd_10n_small[i]);
            Serial.println(lcd_10n_small[i]);
            check_data(lcd_10n_small, i);
            // delay(1);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < lcd_10n_small_size; i++)
                {
                    Serial1.println(lcd_10n_small[i]);
                    Serial.println(lcd_10n_small[i]);
                    check_data(lcd_10n_small, i);
                    // delay(1);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // lcd_11dn_small
        delay(5);
        Serial1.println("ESP32: SEND lcd_11dn_small");
        Serial.println("Sending lcd_11dn_small");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND lcd_11dn_small");
                Serial.println("Sending lcd_11dn_small again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < lcd_11dn_small_size; i++)
        {
            Serial1.println(lcd_11dn_small[i]);
            Serial.println(lcd_11dn_small[i]);
            check_data(lcd_11dn_small, i);
            // delay(1);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < lcd_11dn_small_size; i++)
                {
                    Serial1.println(lcd_11dn_small[i]);
                    Serial.println(lcd_11dn_small[i]);
                    check_data(lcd_11dn_small, i);
                    // delay(1);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // lcd_50dn_small
        delay(5);
        Serial1.println("ESP32: SEND lcd_50dn_small");
        Serial.println("Sending lcd_50dn_small");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND lcd_50dn_small");
                Serial.println("Sending lcd_50dn_small again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < lcd_50dn_small_size; i++)
        {
            Serial1.println(lcd_50dn_small[i]);
            Serial.println(lcd_50dn_small[i]);
            check_data(lcd_50dn_small, i);
            // delay(1);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < lcd_50dn_small_size; i++)
                {
                    Serial1.println(lcd_50dn_small[i]);
                    Serial.println(lcd_50dn_small[i]);
                    check_data(lcd_50dn_small, i);
                    // delay(1);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // lcd_yenbai
        delay(5);
        Serial1.println("ESP32: SEND lcd_yenbai");
        Serial.println("Sending lcd_yenbai");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND lcd_yenbai");
                Serial.println("Sending lcd_yenbai again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < lcd_yenbai_size; i++)
        {
            Serial1.println(lcd_yenbai[i]);
            Serial.println(lcd_yenbai[i]);
            check_data(lcd_yenbai, i);
            // delay(1);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < lcd_yenbai_size; i++)
                {
                    Serial1.println(lcd_yenbai[i]);
                    Serial.println(lcd_yenbai[i]);
                    check_data(lcd_yenbai, i);
                    // delay(1);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // lcd_quangngai
        delay(5);
        Serial1.println("ESP32: SEND lcd_quangngai");
        Serial.println("Sending lcd_quangngai");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND lcd_quangngai");
                Serial.println("Sending lcd_quangngai again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < lcd_quangngai_size; i++)
        {
            Serial1.println(lcd_quangngai[i]);
            Serial.println(lcd_quangngai[i]);
            check_data(lcd_quangngai, i);
            // delay(1);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < lcd_quangngai_size; i++)
                {
                    Serial1.println(lcd_quangngai[i]);
                    Serial.println(lcd_quangngai[i]);
                    check_data(lcd_quangngai, i);
                    // delay(1);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // lcd_khanhhoa
        delay(5);
        Serial1.println("ESP32: SEND lcd_khanhhoa");
        Serial.println("Sending lcd_khanhhoa");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND lcd_khanhhoa");
                Serial.println("Sending lcd_khanhhoa again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < lcd_khanhhoa_size; i++)
        {
            Serial1.println(lcd_khanhhoa[i]);
            Serial.println(lcd_khanhhoa[i]);
            check_data(lcd_khanhhoa, i);
            // delay(1);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < lcd_khanhhoa_size; i++)
                {
                    Serial1.println(lcd_khanhhoa[i]);
                    Serial.println(lcd_khanhhoa[i]);
                    check_data(lcd_khanhhoa, i);
                    // delay(1);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // lcd_nghean
        delay(5);
        Serial1.println("ESP32: SEND lcd_nghean");
        Serial.println("Sending lcd_nghean");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND lcd_nghean");
                Serial.println("Sending lcd_nghean again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < lcd_nghean_size; i++)
        {
            Serial1.println(lcd_nghean[i]);
            Serial.println(lcd_nghean[i]);
            check_data(lcd_nghean, i);
            // delay(1);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < lcd_nghean_size; i++)
                {
                    Serial1.println(lcd_nghean[i]);
                    Serial.println(lcd_nghean[i]);
                    check_data(lcd_nghean, i);
                    // delay(1);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // lcd_longan
        delay(5);
        Serial1.println("ESP32: SEND lcd_longan");
        Serial.println("Sending lcd_longan");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND lcd_longan");
                Serial.println("Sending lcd_longan again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < lcd_longan_size; i++)
        {
            Serial1.println(lcd_longan[i]);
            Serial.println(lcd_longan[i]);
            check_data(lcd_longan, i);
            // delay(1);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < lcd_longan_size; i++)
                {
                    Serial1.println(lcd_longan[i]);
                    Serial.println(lcd_longan[i]);
                    check_data(lcd_longan, i);
                    // delay(1);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // lcd_hue
        delay(5);
        Serial1.println("ESP32: SEND lcd_hue");
        Serial.println("Sending lcd_hue");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND lcd_hue");
                Serial.println("Sending lcd_hue again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < lcd_hue_size; i++)
        {
            Serial1.println(lcd_hue[i]);
            Serial.println(lcd_hue[i]);
            check_data(lcd_hue, i);
            // delay(1);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < lcd_hue_size; i++)
                {
                    Serial1.println(lcd_hue[i]);
                    Serial.println(lcd_hue[i]);
                    check_data(lcd_hue, i);
                    // delay(1);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // lcd_hcmc
        delay(5);
        Serial1.println("ESP32: SEND lcd_hcmc");
        Serial.println("Sending lcd_hcmc");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND lcd_hcmc");
                Serial.println("Sending lcd_hcmc again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < lcd_hcmc_size; i++)
        {
            Serial1.println(lcd_hcmc[i]);
            Serial.println(lcd_hcmc[i]);
            check_data(lcd_hcmc, i);
            // delay(1);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < lcd_hcmc_size; i++)
                {
                    Serial1.println(lcd_hcmc[i]);
                    Serial.println(lcd_hcmc[i]);
                    check_data(lcd_hcmc, i);
                    // delay(1);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // lcd_hanoi
        delay(5);
        Serial1.println("ESP32: SEND lcd_hanoi");
        Serial.println("Sending lcd_hanoi");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND lcd_hanoi");
                Serial.println("Sending lcd_hanoi again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < lcd_hanoi_size; i++)
        {
            Serial1.println(lcd_hanoi[i]);
            Serial.println(lcd_hanoi[i]);
            check_data(lcd_hanoi, i);
            // delay(1);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < lcd_hanoi_size; i++)
                {
                    Serial1.println(lcd_hanoi[i]);
                    Serial.println(lcd_hanoi[i]);
                    check_data(lcd_hanoi, i);
                    // delay(1);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // lcd_haiphong
        delay(5);
        Serial1.println("ESP32: SEND lcd_haiphong");
        Serial.println("Sending lcd_haiphong");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND lcd_haiphong");
                Serial.println("Sending lcd_haiphong again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < lcd_haiphong_size; i++)
        {
            Serial1.println(lcd_haiphong[i]);
            Serial.println(lcd_haiphong[i]);
            check_data(lcd_haiphong, i);
            // delay(1);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < lcd_haiphong_size; i++)
                {
                    Serial1.println(lcd_haiphong[i]);
                    Serial.println(lcd_haiphong[i]);
                    check_data(lcd_haiphong, i);
                    // delay(1);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // lcd_camau
        delay(5);
        Serial1.println("ESP32: SEND lcd_camau");
        Serial.println("Sending lcd_camau");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND lcd_camau");
                Serial.println("Sending lcd_camau again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < lcd_camau_size; i++)
        {
            Serial1.println(lcd_camau[i]);
            Serial.println(lcd_camau[i]);
            check_data(lcd_camau, i);
            // delay(1);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < lcd_camau_size; i++)
                {
                    Serial1.println(lcd_camau[i]);
                    Serial.println(lcd_camau[i]);
                    check_data(lcd_camau, i);
                    // delay(1);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // lcd_dalat
        delay(5);
        Serial1.println("ESP32: SEND lcd_dalat");
        Serial.println("Sending lcd_dalat");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND lcd_dalat");
                Serial.println("Sending lcd_dalat again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < lcd_dalat_size; i++)
        {
            Serial1.println(lcd_dalat[i]);
            Serial.println(lcd_dalat[i]);
            check_data(lcd_dalat, i);
            // delay(1);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < lcd_dalat_size; i++)
                {
                    Serial1.println(lcd_dalat[i]);
                    Serial.println(lcd_dalat[i]);
                    check_data(lcd_dalat, i);
                    // delay(1);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // lcd_hagiang
        delay(5);
        Serial1.println("ESP32: SEND lcd_hagiang");
        Serial.println("Sending lcd_hagiang");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND lcd_hagiang");
                Serial.println("Sending lcd_hagiang again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < lcd_hagiang_size; i++)
        {
            Serial1.println(lcd_hagiang[i]);
            Serial.println(lcd_hagiang[i]);
            check_data(lcd_hagiang, i);
            // delay(1);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < lcd_hagiang_size; i++)
                {
                    Serial1.println(lcd_hagiang[i]);
                    Serial.println(lcd_hagiang[i]);
                    check_data(lcd_hagiang, i);
                    // delay(1);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // Font_Morgan_32x72
        delay(5);
        Serial1.println("ESP32: SEND Font_Morgan_32x72");
        Serial.println("Sending Font_Morgan_32x72");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND Font_Morgan_32x72");
                Serial.println("Sending Font_Morgan_32x72 again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < Font_Morgan_32x72_size; i++)
        {
            Serial1.println(Font_Morgan_32x72[i]);
            Serial.println(Font_Morgan_32x72[i]);
            check_data_large(Font_Morgan_32x72, i);
            // delay(1);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < Font_Morgan_32x72_size; i++)
                {
                    Serial1.println(Font_Morgan_32x72[i]);
                    Serial.println(Font_Morgan_32x72[i]);
                    check_data_large(Font_Morgan_32x72, i);
                    // delay(1);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // Font_Morgan_16x36
        delay(5);
        Serial1.println("ESP32: SEND Font_Morgan_16x36");
        Serial.println("Sending Font_Morgan_16x36");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND Font_Morgan_16x36");
                Serial.println("Sending Font_Morgan_16x36 again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < Font_Morgan_16x36_size; i++)
        {
            Serial1.println(Font_Morgan_16x36[i]);
            Serial.println(Font_Morgan_16x36[i]);
            check_data(Font_Morgan_16x36, i);
            // delay(1);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < Font_Morgan_16x36_size; i++)
                {
                    Serial1.println(Font_Morgan_16x36[i]);
                    Serial.println(Font_Morgan_16x36[i]);
                    check_data(Font_Morgan_16x36, i);
                    // delay(1);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // Font_11x18
        delay(5);
        Serial1.println("ESP32: SEND Font_11x18");
        Serial.println("Sending Font_11x18");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND Font_11x18");
                Serial.println("Sending Font_11x18 again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(50);
        Serial.println("Sending data:");
        for (int i = 0; i < Font_11x18_size; i++)
        {
            Serial1.println(Font11x18[i]);
            Serial.println(Font11x18[i]);
            check_data(Font11x18, i);
            // delay(1);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < Font_11x18_size; i++)
                {
                    Serial1.println(Font11x18[i]);
                    Serial.println(Font11x18[i]);
                    check_data(Font11x18, i);
                    // delay(1);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // Ending transaction
        delay(5);
        Serial1.println("ESP32: END");
        Serial.println("Sending end transaction packet");
    }
    else if (strncmp(received_str.c_str(), "STM32: Get WEATHER_API", 22) == 0)
    {
        Serial.println("Received STM32: Get WEATHER_API command");
        char *selected_city_str = strstr(received_str.c_str(), "STM32: Get WEATHER_API ") + strlen("STM32: Get WEATHER_API ");
        uint8_t selected_city_id = atoi(selected_city_str);
        Serial.print("City id: ");
        Serial.println(selected_city_id);
        delay(20);
        Serial1.println("ESP32: ACK");
        Serial.println("Sending ACK");
        start_time = millis();

        while ((Serial1.readString() != "STM32: OK"))
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 4000)
            {
                Serial1.println("ESP32: ACK");
                Serial.println("Sending ACK again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        // Current
        delay(5);
        Serial1.println("ESP32: SEND current");
        Serial.println("Sending current weather");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND current");
                Serial.println("Sending current weather again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        current_data_to_stm.weather_des = "";
        current_data_to_stm.icon_id = "";
        for (int i = 0; i < 7; i++)
        {
            forecast_data_to_stm[i].date = "";
            forecast_data_to_stm[i].icon_id = "";
        }
        getWeather(selected_city_id);

        delay(5);
        Serial.println("Sending data:");
        Serial1.println(current_data_to_stm.weather_des);
        Serial.println(current_data_to_stm.weather_des);
        delay(20);
        Serial1.println(current_data_to_stm.icon_id);
        Serial.println(current_data_to_stm.icon_id);
        delay(20);
        Serial1.println(current_data_to_stm.temperature);
        Serial.println(current_data_to_stm.temperature);
        delay(20);
        Serial1.println(current_data_to_stm.humidity);
        Serial.println(current_data_to_stm.humidity);
        delay(20);
        Serial1.println(current_data_to_stm.wind_speed);
        Serial.println(current_data_to_stm.wind_speed);
        delay(20);
        Serial1.println(current_data_to_stm.wind_degree);
        Serial.println(current_data_to_stm.wind_degree);
        delay(20);

        uint16_t arr_for_checksum[4];
        for (int i = 0; i < 4; i++)
        {
            arr_for_checksum[i] = (i == 0) ? current_data_to_stm.temperature : ((i == 1) ? current_data_to_stm.humidity : ((i == 2) ? current_data_to_stm.wind_speed : current_data_to_stm.wind_degree));
            check_data(arr_for_checksum, i);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                Serial1.println(current_data_to_stm.weather_des);
                Serial.println(current_data_to_stm.weather_des);
                delay(20);
                Serial1.println(current_data_to_stm.icon_id);
                Serial.println(current_data_to_stm.icon_id);
                delay(20);
                Serial1.println(current_data_to_stm.temperature);
                Serial.println(current_data_to_stm.temperature);
                delay(20);
                Serial1.println(current_data_to_stm.humidity);
                Serial.println(current_data_to_stm.humidity);
                delay(20);
                Serial1.println(current_data_to_stm.wind_speed);
                Serial.println(current_data_to_stm.wind_speed);
                delay(20);
                Serial1.println(current_data_to_stm.wind_degree);
                Serial.println(current_data_to_stm.wind_degree);
                delay(20);
                for (int i = 0; i < 4; i++)
                {
                    arr_for_checksum[i] = (i == 0) ? current_data_to_stm.temperature : ((i == 1) ? current_data_to_stm.humidity : ((i == 2) ? current_data_to_stm.wind_speed : current_data_to_stm.wind_degree));
                    check_data(arr_for_checksum, i);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // Forecast
        delay(5);
        Serial1.println("ESP32: SEND forecast");
        Serial.println("Sending forecast weather");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND forecast");
                Serial.println("Sending forecast weather again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(5);
        Serial.println("Sending data:");
        for (int i = 0; i < 7; i++)
        {
            Serial1.println(forecast_data_to_stm[i].date);
            Serial.println(forecast_data_to_stm[i].date);
            delay(5);
            Serial1.println(forecast_data_to_stm[i].icon_id);
            Serial.println(forecast_data_to_stm[i].icon_id);
            delay(5);
            Serial1.println(forecast_data_to_stm[i].temperature);
            Serial.println(forecast_data_to_stm[i].temperature);
            delay(5);
            Serial1.println(forecast_data_to_stm[i].humidity);
            Serial.println(forecast_data_to_stm[i].humidity);
            delay(5);
            Serial1.println(forecast_data_to_stm[i].wind_speed);
            Serial.println(forecast_data_to_stm[i].wind_speed);
            // for (int i = 0; i < 4; i++) {
            //   arr_for_checksum[i] = (i == 0) ? forecast_data_to_stm[i].temperature : ((i == 1) ? forecast_data_to_stm[i].humidity : ((i == 2) ? forecast_data_to_stm[i].wind_speed : 524));
            //   check_data(arr_for_checksum, i);
            // }
            delay(5);
        }
        Serial1.println(check_data_result);
        Serial.print("Data checksum: ");
        Serial.println(check_data_result);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 100000)
            {
                check_data_result = 0;
                Serial.println("Sending data again:");
                for (int i = 0; i < 7; i++)
                {
                    Serial1.println(forecast_data_to_stm[i].date);
                    Serial.println(forecast_data_to_stm[i].date);
                    delay(5);
                    Serial1.println(forecast_data_to_stm[i].icon_id);
                    Serial.println(forecast_data_to_stm[i].icon_id);
                    delay(5);
                    Serial1.println(forecast_data_to_stm[i].temperature);
                    Serial.println(forecast_data_to_stm[i].temperature);
                    delay(5);
                    Serial1.println(forecast_data_to_stm[i].humidity);
                    Serial.println(forecast_data_to_stm[i].humidity);
                    delay(5);
                    Serial1.println(forecast_data_to_stm[i].wind_speed);
                    Serial.println(forecast_data_to_stm[i].wind_speed);
                    // for (int i = 0; i < 4; i++) {
                    //   arr_for_checksum[i] = (i == 0) ? forecast_data_to_stm[i].temperature : ((i == 1) ? forecast_data_to_stm[i].humidity : ((i == 2) ? forecast_data_to_stm[i].wind_speed : 524));
                    //   check_data(arr_for_checksum, i);
                    // }
                    delay(5);
                }
                Serial1.println(check_data_result);
                Serial.print("Data checksum: ");
                Serial.println(check_data_result);
                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // Ending transaction
        delay(5);
        Serial1.println("ESP32: END");
        Serial.println("Sending end transaction packet");
    }
    else if (received_str == "STM32: Get DAILY")
    {
        delay(5);
        Serial1.println("ESP32: ACK");
        Serial.println("Sending ACK");
        start_time = millis();

        while ((Serial1.readString() != "STM32: OK"))
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 4000)
            {
                Serial1.println("ESP32: ACK");
                Serial.println("Sending ACK again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        delay(5);
        Serial1.println("ESP32: SEND daily");
        Serial.println("Sending daily weather");
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 2000)
            {
                Serial1.println("ESP32: SEND daily");
                Serial.println("Sending daily weather again");
                start_time = millis();
                error_count++;
            }
        }
        error_count = 0;

        daily_data_to_stm = "";
        getDailyWeather();

        delay(5);
        Serial.println("Sending data:");
        Serial1.println(daily_data_to_stm);
        Serial.println(daily_data_to_stm);

        Serial1.println(2025);
        Serial.print("Data checksum: ");
        Serial.println(2025);
        start_time = millis();

        while (Serial1.readString() != "STM32: OK")
        {
            if (error_count == 10)
            {
                error_count = 0;
                return;
            }
            if ((millis() - start_time) > 40000)
            {
                Serial.println("Sending data again:");
                Serial1.println(daily_data_to_stm);
                Serial.println(daily_data_to_stm);

                Serial1.println(2025);
                Serial.print("Data checksum: ");
                Serial.println(2025);

                start_time = millis();
                error_count++;
            }
        }
        check_data_result = 0;
        error_count = 0;

        // Ending transaction
        delay(5);
        Serial1.println("ESP32: END");
        Serial.println("Sending end transaction packet");
    }
}

void setup()
{
    Serial.begin(230400);
    Serial1.begin(230400, SERIAL_8N1, Rx_PIN, Tx_PIN);

    WiFi.disconnect();

    WiFi.begin(ssid, password);
    Serial.println("Connecting to Wifi");

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());

    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("WiFi Disconnected");
    }

    Serial.println("Calling handshaking function");
}

void loop()
{
    handshaking();
}
