/*
 * Copyright (c) 2016-2020, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== main_freertos.c ========
 */
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

/* POSIX Header files */
#include <pthread.h>

/* RTOS header files */
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <semphr.h>
#include "cJSON.h"


#include <ti/drivers/Board.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/I2C.h>
#include <ti/drivers/UART2.h>
#include <ti/drivers/TIMER.h>

/* Driver configuration */
#include "ti_drivers_config.h"

extern void *mainThread(void *arg0);


I2C_Handle i2c;
I2C_Params i2cParams;
I2C_Transaction i2cTransaction = {0};

UART2_Handle uart;
UART2_Params uartParams;




// Déclaration des handlers pour les tâches

TaskHandle_t xTaskSensorReadHandle;
TaskHandle_t xTaskDisplayHandle;
TaskHandle_t xTaskSendDataHandle;

//Déclaration de la queue

QueueHandle_t xQueue;
QueueHandle_t xQueueSerial;


/* Capteur SHT35 */

#define SHT35_I2C_ADDR 0x45

typedef struct{
    float temperature;
    float humidity;
}SensorDataSth35;


/*Grove Multichannel Gas Sensor v2*/

#define GAS_SENSOR 0x55
#define I2C_ADDR 0x08

typedef struct{
    float gasData_No2;
    float gasData_C2H5OH;
    float gasDataVoc;
    float gasDataCo;
}SensorDataGas;


/* Ecran Oled */

const unsigned char BasicFont[][8] = {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x5F, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x07, 0x00, 0x07, 0x00, 0x00, 0x00},
    {0x00, 0x14, 0x7F, 0x14, 0x7F, 0x14, 0x00, 0x00},
    {0x00, 0x24, 0x2A, 0x7F, 0x2A, 0x12, 0x00, 0x00},
    {0x00, 0x23, 0x13, 0x08, 0x64, 0x62, 0x00, 0x00},
    {0x00, 0x36, 0x49, 0x55, 0x22, 0x50, 0x00, 0x00},
    {0x00, 0x00, 0x05, 0x03, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x1C, 0x22, 0x41, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x41, 0x22, 0x1C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x08, 0x2A, 0x1C, 0x2A, 0x08, 0x00, 0x00},
    {0x00, 0x08, 0x08, 0x3E, 0x08, 0x08, 0x00, 0x00},
    {0x00, 0xA0, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00},
    {0x00, 0x60, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x20, 0x10, 0x08, 0x04, 0x02, 0x00, 0x00},
    {0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E, 0x00, 0x00},
    {0x00, 0x00, 0x42, 0x7F, 0x40, 0x00, 0x00, 0x00},
    {0x00, 0x62, 0x51, 0x49, 0x49, 0x46, 0x00, 0x00},
    {0x00, 0x22, 0x41, 0x49, 0x49, 0x36, 0x00, 0x00},
    {0x00, 0x18, 0x14, 0x12, 0x7F, 0x10, 0x00, 0x00},
    {0x00, 0x27, 0x45, 0x45, 0x45, 0x39, 0x00, 0x00},
    {0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30, 0x00, 0x00},
    {0x00, 0x01, 0x71, 0x09, 0x05, 0x03, 0x00, 0x00},
    {0x00, 0x36, 0x49, 0x49, 0x49, 0x36, 0x00, 0x00},
    {0x00, 0x06, 0x49, 0x49, 0x29, 0x1E, 0x00, 0x00},
    {0x00, 0x00, 0x36, 0x36, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0xAC, 0x6C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x08, 0x14, 0x22, 0x41, 0x00, 0x00, 0x00},
    {0x00, 0x14, 0x14, 0x14, 0x14, 0x14, 0x00, 0x00},
    {0x00, 0x41, 0x22, 0x14, 0x08, 0x00, 0x00, 0x00},
    {0x00, 0x02, 0x01, 0x51, 0x09, 0x06, 0x00, 0x00},
    {0x00, 0x32, 0x49, 0x79, 0x41, 0x3E, 0x00, 0x00},
    {0x00, 0x7E, 0x09, 0x09, 0x09, 0x7E, 0x00, 0x00},
    {0x00, 0x7F, 0x49, 0x49, 0x49, 0x36, 0x00, 0x00},
    {0x00, 0x3E, 0x41, 0x41, 0x41, 0x22, 0x00, 0x00},
    {0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C, 0x00, 0x00},
    {0x00, 0x7F, 0x49, 0x49, 0x49, 0x41, 0x00, 0x00},
    {0x00, 0x7F, 0x09, 0x09, 0x09, 0x01, 0x00, 0x00},
    {0x00, 0x3E, 0x41, 0x41, 0x51, 0x72, 0x00, 0x00},
    {0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F, 0x00, 0x00},
    {0x00, 0x41, 0x7F, 0x41, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x20, 0x40, 0x41, 0x3F, 0x01, 0x00, 0x00},
    {0x00, 0x7F, 0x08, 0x14, 0x22, 0x41, 0x00, 0x00},
    {0x00, 0x7F, 0x40, 0x40, 0x40, 0x40, 0x00, 0x00},
    {0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F, 0x00, 0x00},
    {0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F, 0x00, 0x00},
    {0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E, 0x00, 0x00},
    {0x00, 0x7F, 0x09, 0x09, 0x09, 0x06, 0x00, 0x00},
    {0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E, 0x00, 0x00},
    {0x00, 0x7F, 0x09, 0x19, 0x29, 0x46, 0x00, 0x00},
    {0x00, 0x26, 0x49, 0x49, 0x49, 0x32, 0x00, 0x00},
    {0x00, 0x01, 0x01, 0x7F, 0x01, 0x01, 0x00, 0x00},
    {0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F, 0x00, 0x00},
    {0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F, 0x00, 0x00},
    {0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F, 0x00, 0x00},
    {0x00, 0x63, 0x14, 0x08, 0x14, 0x63, 0x00, 0x00},
    {0x00, 0x03, 0x04, 0x78, 0x04, 0x03, 0x00, 0x00},
    {0x00, 0x61, 0x51, 0x49, 0x45, 0x43, 0x00, 0x00},
    {0x00, 0x7F, 0x41, 0x41, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x02, 0x04, 0x08, 0x10, 0x20, 0x00, 0x00},
    {0x00, 0x41, 0x41, 0x7F, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x04, 0x02, 0x01, 0x02, 0x04, 0x00, 0x00},
    {0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00},
    {0x00, 0x01, 0x02, 0x04, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x20, 0x54, 0x54, 0x54, 0x78, 0x00, 0x00},
    {0x00, 0x7F, 0x48, 0x44, 0x44, 0x38, 0x00, 0x00},
    {0x00, 0x38, 0x44, 0x44, 0x28, 0x00, 0x00, 0x00},
    {0x00, 0x38, 0x44, 0x44, 0x48, 0x7F, 0x00, 0x00},
    {0x00, 0x38, 0x54, 0x54, 0x54, 0x18, 0x00, 0x00},
    {0x00, 0x08, 0x7E, 0x09, 0x02, 0x00, 0x00, 0x00},
    {0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C, 0x00, 0x00},
    {0x00, 0x7F, 0x08, 0x04, 0x04, 0x78, 0x00, 0x00},
    {0x00, 0x00, 0x7D, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x80, 0x84, 0x7D, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x7F, 0x10, 0x28, 0x44, 0x00, 0x00, 0x00},
    {0x00, 0x41, 0x7F, 0x40, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x7C, 0x04, 0x18, 0x04, 0x78, 0x00, 0x00},
    {0x00, 0x7C, 0x08, 0x04, 0x7C, 0x00, 0x00, 0x00},
    {0x00, 0x38, 0x44, 0x44, 0x38, 0x00, 0x00, 0x00},
    {0x00, 0xFC, 0x24, 0x24, 0x18, 0x00, 0x00, 0x00},
    {0x00, 0x18, 0x24, 0x24, 0xFC, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x7C, 0x08, 0x04, 0x00, 0x00, 0x00},
    {0x00, 0x48, 0x54, 0x54, 0x24, 0x00, 0x00, 0x00},
    {0x00, 0x04, 0x7F, 0x44, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x3C, 0x40, 0x40, 0x7C, 0x00, 0x00, 0x00},
    {0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C, 0x00, 0x00},
    {0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C, 0x00, 0x00},
    {0x00, 0x44, 0x28, 0x10, 0x28, 0x44, 0x00, 0x00},
    {0x00, 0x1C, 0xA0, 0xA0, 0x7C, 0x00, 0x00, 0x00},
    {0x00, 0x44, 0x64, 0x54, 0x4C, 0x44, 0x00, 0x00},
    {0x00, 0x08, 0x36, 0x41, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x41, 0x36, 0x08, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x02, 0x01, 0x01, 0x02, 0x01, 0x00, 0x00},
    {0x00, 0x02, 0x05, 0x05, 0x02, 0x00, 0x00, 0x00}
};

#define SeeedGrayOLED_Address               0x3c
#define SeeedGrayOLED_Command_Mode          0x80
#define SeeedGrayOLED_Data_Mode             0x40

#define SeeedGrayOLED_Display_Off_Cmd       0xAE
#define SeeedGrayOLED_Display_On_Cmd        0xAF

#define SeeedGrayOLED_Normal_Display_Cmd    0xA4
#define SeeedGrayOLED_Normal_Display_Cmd_SH1107G    0xA6
#define SeeedGrayOLED_Inverse_Display_Cmd   0xA7
#define SeeedGrayOLED_Set_ContrastLevel_Cmd 0x81


unsigned char grayH;
unsigned char grayL;



void readDataSht(float *temperature, float *humidity);
void readDataMultiChannel(float *gasData_No2,float *gasData_C2H5OH,float *gasDataVoc, float *gasDataCo);

void init();

void setNormalDisplay();
void setInverseDisplay();

void sendCommand(unsigned char command);
void sendData(unsigned char Data);
void setGrayLevel(unsigned char grayLevel);

void setVerticalMode();
void setHorizontalMode();

void setTextXY(unsigned char Row, unsigned char Column);
void clearDisplay();
void setContrastLevel(unsigned char ContrastLevel);
void putChar(char C);
void putString(const char* String);

unsigned char floatToString(float floatNumber, char* buffer, unsigned char decimal);
unsigned char putFloat(float floatNumber, unsigned char decimal);

char serialiDataJson(SensorDataGas *data);
void sendUartData(char *data);

void TaskSensorRead(void *pvParameters);
void TaskDisplay(void *pvParameters);
void TaskSendData(void *pvParameters);





void readDataSht(float *temperature, float *humidity){

    uint8_t cmdMesure[]= {0x2C, 0x06};

    uint8_t data_SHT[6];

    uint16_t rawtemperature, rawhumidity;

    i2cTransaction.targetAddress = SHT35_I2C_ADDR;
    i2cTransaction.writeBuf = cmdMesure;
    i2cTransaction.writeCount = 2;
    i2cTransaction.readBuf = data_SHT;
    i2cTransaction.readCount = 6;
    I2C_transfer(i2c, &i2cTransaction);

    rawtemperature = (data_SHT[0] << 8) | data_SHT[1];
    rawhumidity = (data_SHT[3] << 8) | data_SHT[4];
    *temperature = -45 + 175 * (rawtemperature / 65535.0);
    *humidity = 100 * (rawhumidity / 65535.0);
}

void readDataMultiChannel(float *gasData_No2,float *gasData_C2H5OH,float *gasDataVoc, float *gasDataCo){

    uint8_t data_GM_102B[2];
    uint8_t data_GM_302B[2];
    uint8_t data_GM_502B[2];
    uint8_t data_GM_702B[2];

    uint16_t rawGasData_No2;
    uint16_t rawGasData_C2H5OH;
    uint16_t rawGasDataVoc;
    uint16_t rawGasDataCo;

    int resolution =1023;

    uint8_t cmd102B [] = {0x01};
    i2cTransaction.targetAddress = I2C_ADDR;
    i2cTransaction.writeBuf =cmd102B;
    i2cTransaction.writeCount = 1;
    i2cTransaction.readBuf = data_GM_102B;
    i2cTransaction.readCount = 2;
    I2C_transfer(i2c, &i2cTransaction);
    rawGasData_No2 = (data_GM_102B[0] << 8) |  data_GM_102B[1];
    *gasData_No2 = (rawGasData_No2 * 5) / (resolution * 1.0);

    uint8_t cmd302B [] = {0x03};
    i2cTransaction.targetAddress = I2C_ADDR;
    i2cTransaction.writeBuf =cmd302B;
    i2cTransaction.writeCount = 1;
    i2cTransaction.readBuf = data_GM_302B;
    i2cTransaction.readCount = 2;
    I2C_transfer(i2c, &i2cTransaction);
    rawGasData_C2H5OH = (data_GM_302B[0] << 8) |  data_GM_302B[1];
    *gasData_C2H5OH = (rawGasData_C2H5OH * 5) / (resolution * 1.0);

    uint8_t cmd502B [] = {0x05};
    i2cTransaction.targetAddress = I2C_ADDR;
    i2cTransaction.writeBuf =cmd502B;
    i2cTransaction.writeCount = 1;
    i2cTransaction.readBuf = data_GM_502B;
    i2cTransaction.readCount = 2;
    I2C_transfer(i2c, &i2cTransaction);
    rawGasDataVoc = (data_GM_502B[0] << 8) |  data_GM_502B[1];
    *gasDataVoc = (rawGasDataVoc * 5) / (resolution * 1.0);

    uint8_t cmd702B [] = {0x07};
    i2cTransaction.targetAddress = I2C_ADDR;
    i2cTransaction.writeBuf =cmd702B;
    i2cTransaction.writeCount = 1;
    i2cTransaction.readBuf = data_GM_702B;
    i2cTransaction.readCount = 2;
    I2C_transfer(i2c, &i2cTransaction);
    rawGasDataCo = (data_GM_702B[0] << 8) |  data_GM_702B[1];
    *gasDataCo = (rawGasDataCo * 5) / (resolution * 1.0);
}

void init(){

    sendCommand(0xae);
    sendCommand(0xd5);
    sendCommand(0x50);
    sendCommand(0x20);
    sendCommand(0x81);
    sendCommand(0x80);
    sendCommand(0xa0);
    sendCommand(0xa4);
    sendCommand(0xa6);
    sendCommand(0xad);
    sendCommand(0x80);
    sendCommand(0xc0);
    sendCommand(0xd9);
    sendCommand(0x1f);
    sendCommand(0xdb);
    sendCommand(0x27);
    sendCommand(0xaf);
    sendCommand(0xb0);
    sendCommand(0x00);
    sendCommand(0x11);
}

void sendCommand(unsigned char command){
    uint8_t data_oled[2] = {SeeedGrayOLED_Command_Mode, command};
    i2cTransaction.targetAddress = SeeedGrayOLED_Address;
    i2cTransaction.writeBuf = data_oled;
    i2cTransaction.writeCount = 2;
    I2C_transfer(i2c, &i2cTransaction);
}


void setContrastLevel(unsigned char ContrastLevel) {
    sendCommand(SeeedGrayOLED_Set_ContrastLevel_Cmd);
    sendCommand(ContrastLevel);
}


void setHorizontalMode() {
        sendCommand(0xA0);
        sendCommand(0xC8);
}


void setVerticalMode() {
        sendCommand(0xA0);
        sendCommand(0xC0);
}


void setTextXY(unsigned char Row, unsigned char Column) {

   sendCommand(0xb0 + (Row & 0x0F));
   sendCommand(0x10 + ((Column >> 4) & 0x07));
   sendCommand(Column & 0x0F);
}


void clearDisplay() {
    unsigned char i, j;
        for (i = 0; i < 16; i++) {
            sendCommand(0xb0 + i);
            sendCommand(0x00);
            sendCommand(0x10);
            for (j = 0; j < 128; j++) {
                sendData(0x00);
            }
        }
}


void sendData(unsigned char Data){
    uint8_t data_ol[2] = {SeeedGrayOLED_Data_Mode,Data};
    i2cTransaction.targetAddress = SeeedGrayOLED_Address;
    i2cTransaction.writeBuf = data_ol;
    i2cTransaction.writeCount = 2;
    I2C_transfer(i2c, &i2cTransaction);
}


void setGrayLevel(unsigned char grayLevel) {
    grayH = (grayLevel << 4) & 0xF0;
    grayL =  grayLevel & 0x0F;
}


void putChar(char C) {
    if (C < 32 || C > 127) {
        C = ' ';
    }

    for (int i = 0; i < 8; i++) {

        sendData(BasicFont[C - 32][i]);
    }
}


void putString(const char* String) {
    unsigned char i = 0;
    while (String[i]) {
        putChar(String[i]);
        i++;
    }
}


unsigned char floatToString(float floatNumber, char* buffer, unsigned char decimal) {
    int intPart = (int)floatNumber;
    float decimalPart = floatNumber - intPart;


    sprintf(buffer, "%d.", intPart);

    int decimalMultiplier = 1;
    for (unsigned char i = 0; i < decimal; i++) {
        decimalMultiplier *= 10;
    }
    int decimalInt = (int)(decimalPart * decimalMultiplier);
    sprintf(buffer + strlen(buffer), "%0*d", decimal, decimalInt);

    return strlen(buffer);
}


unsigned char putFloat(float floatNumber, unsigned char decimal) {
    char buffer[20];
    unsigned char len = floatToString(floatNumber, buffer, decimal);
    for (unsigned char i = 0; i < len; i++) {
        putChar(buffer[i]);
    }
    return len;
}

void setNormalDisplay(){

    sendCommand(SeeedGrayOLED_Normal_Display_Cmd_SH1107G);
}

void setInverseDisplay(){
    sendCommand(SeeedGrayOLED_Inverse_Display_Cmd);
}


char serialiDataJson(SensorDataGas *data){

    //char unit[6]={"ppm"};
    //cJSON_AddStringToObject(serialData, "unite",unite);

    cJSON *serialData = cJSON_CreateObject();
    cJSON_AddNumberToObject(serialData, "dioxyde_azote", data->gasData_No2);
    //cJSON_AddStringToObject(serialData, "unite",unit);
    cJSON_AddNumberToObject(serialData, "alcool_ethylique", data->gasData_C2H5OH);
    cJSON_AddNumberToObject(serialData, "composes_organiques", data->gasDataVoc);
    cJSON_AddNumberToObject(serialData, "monoxyde_de_carbone", data->gasDataCo);

    char *jsonString = cJSON_PrintUnformatted(serialData);

    //cJSON_Delete(serialData);
    return jsonString;
}


void sendUartData(char *data){

    size_t bytesWritten;
    UART2_write(uart, data,strlen(data), &bytesWritten);
}




void TaskSensorRead(void *pvParameters){

    //Variable pour stocker le dernier temps de réveil
    TickType_t xLastWakeTime;

    //Fréquence de la tache en ticks
    const TickType_t xFrequency = pdMS_TO_TICKS(2000);

    //Initialisation de la variable avec le temps actuel
    xLastWakeTime = xTaskGetTickCount();

    SensorDataSth35 sensorData;

    SensorDataGas sensorGasData;


    while(1){

        //readDataSht(&sensorData.temperature, &sensorData.humidity);

        readDataMultiChannel(&sensorGasData.gasData_No2,&sensorGasData.gasData_C2H5OH,&sensorGasData.gasDataVoc,&sensorGasData.gasDataCo);


        xQueueSend(xQueue, &sensorData, 10);

        xQueueSend(xQueueSerial, &sensorGasData, 10);



        vTaskDelayUntil(&xLastWakeTime, xFrequency);

        //vTaskDelay(pdMS_TO_TICKS(2000));
    }
}


void TaskDisplay(void *pvParameters) {

    SensorDataSth35 sensorDataSth;

    //SensorDataGas sensorGasDataFil;

    init();
    //clearDisplay();
    setNormalDisplay();
    setVerticalMode();

    while(1){

        xQueueReceive( xQueue, &sensorDataSth, 10);

        clearDisplay();

        setTextXY(0, 0);
        setGrayLevel(2);
        putString("Temp: ");
        //putFloat(sensorGasDataFil.gasData_No2,2);

        setTextXY(2, 0);
        setGrayLevel(2);
        putFloat(sensorDataSth.temperature,1);

        vTaskDelay(pdMS_TO_TICKS(2000));
    }


}


void TaskSendData(void *pvParameters){

    //SensorDataSth35 sensorDataSthSerial;

    SensorDataGas sensorGasDataSerial;

    while(1){
        xQueueReceive( xQueueSerial, &sensorGasDataSerial, 10);

        char* jsonData = serialiDataJson(&sensorGasDataSerial);


        sendUartData(jsonData);

        //free(jsonData);

        vTaskDelay(pdMS_TO_TICKS(2000));
    }

}

/*
 *  ======== main ========
 */
int main(void)
{
    GPIO_init();
    I2C_init();

    /*Configuration uart2*/
    UART2_Params_init(&uartParams);
    uartParams.baudRate = 115200;
    uart = UART2_open(CONFIG_UART2_0, &uartParams);


    /*Configuration i2c*/
    I2C_Params_init(&i2cParams);
    i2cParams.bitRate = I2C_400kHz;
    i2c = I2C_open(CONFIG_I2C_0, &i2cParams);

    xQueue = xQueueCreate( 10, sizeof( SensorDataSth35 ) );

    xQueueSerial = xQueueCreate( 10, sizeof( SensorDataGas ) );


    // Création tache
    xTaskCreate(TaskSensorRead, "SensorRead", 256 ,NULL,tskIDLE_PRIORITY + 4 , &xTaskSensorReadHandle);

    xTaskCreate(TaskDisplay, "Display", 256 ,NULL,tskIDLE_PRIORITY + 4 , &xTaskDisplayHandle);

    xTaskCreate(TaskSendData, "SendData", 256 ,NULL,tskIDLE_PRIORITY + 4, &xTaskSendDataHandle);

    /* Start the FreeRTOS scheduler */
    vTaskStartScheduler();

    return (0);
}


