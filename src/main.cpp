#include <ModbusRTU.h>
#include <Arduino.h>
#include <MCP3208.h>
#include <SPI.h>

// Firmware FOR BOARD 16IN_16OUT
// Using Uart2 for RS_485
//#define SLAVE_ID 1
// Define for board 16IN_16OUT
int input[] = {A8, A9, A10, A11, A12, A13, A14, A15,
               A3, A2, A1, A0, A4, A5, A6, A7};
int output[] = {37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22};
#pragma region Define_ID_Pin_Baurate_Pin
#pragma endregion Define_ID_Pin_Baurate_Pin

#define REGN 10
int SLAVE_ID = 1;
long ModbusBaurate;
ModbusRTU mbslv;
void setup()
{
    // initialize serial
    Serial.begin(9600);
    // 16Input
    for (int i = 0; i < 16; i++)
    {
        pinMode(input[i], INPUT_PULLUP);
    }
    // 16Output
    for (int i = 0; i < 16; i++)
    {
        pinMode(output[i], OUTPUT);
    }
    Serial.begin(9600, SERIAL_8N1);

    mbslv.begin(&Serial);
    mbslv.setBaudrate(9600);
    mbslv.slave(SLAVE_ID);
    mbslv.addHreg(REGN);
    mbslv.Hreg(REGN, 100);

    /*
    mbslv.addCoil(0, 0, 16); //  Thêm 100 Coils
    mbslv.addHreg(0, 0, 16); //  Thêm thanh ghi hoding register với địa chỉ bắt đầu = 0 và độ dài thanh ghi =100
    mbslv.addIsts(0, 0, 16); //  Thêm thanh ghi discrete với địa chỉ bắt đầu = 0, giá trị set ban đầu = false và độ dài thanh ghi = 100
    mbslv.addIreg(0, 0, 16); //  Thêm thanh ghi discrete với địa chỉ bắt đầu = 0, giá trị set ban đầu = false và độ dài thanh ghi = 100
    mb.slave(SLAVE_ID);
    mb.addHreg(REGN);
    mb.Hreg(REGN, 100);
    */
}
void loop()
{
    //Đọc input & gán vào thanh ghi
    /*
    for (int i = 0; i < 16; i++)
    {
        mbslv.Ists(i, digitalRead(input[i]));
    }
    // DO
    for (int i = 0; i < 16; i++)
    {
        digitalWrite(output[i], mbslv.Coil(i));
    }*/
    mbslv.task();
    yield();
}