#pragma once

#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <ModbusRTU.h>
#include <HardwareSerial.h>


// =============================================================================================
// MCP 
// =============================================================================================
void writeRegister(uint8_t reg, uint8_t value, uint8_t MCP_addr, uint8_t csPin, SPIClass& spi);
uint8_t readRegister(uint8_t reg, uint8_t MCP_addr, uint8_t csPin, SPIClass& spi);
// =============================================================================================
// ECRAN
// =============================================================================================
void initEcran(Adafruit_ST7789& tft, uint16_t* counter,uint16_t* temps);
void printFormattedCounter(Adafruit_ST7789& tft, uint16_t* number, int x, int y);
void printFormattedTime(Adafruit_ST7789& tft, uint16_t* number, int x, int y);
void updateFormattedCounter(Adafruit_ST7789& tft, uint16_t* oldNumber, uint16_t* newNumber, int x, int y);
void updateFormattedTime(Adafruit_ST7789& tft, uint16_t* oldNumber, uint16_t* newNumber, int x, int y);
// =============================================================================================
// COMMUNICATION GUI 
// =============================================================================================
void parseStringFromSecondChar(const char* input, void* values, uint8_t* count, int isFloat);
uint16_t extractValues(char* start, uint16_t values[], char delimiter);
uint8_t combineBits(void* bitValues, uint8_t numBits, uint8_t valueType);
void float_to_hex_array(float float_value, uint8_t byte_array[4]);

// =============================================================================================
// INITIALISATION PERIPHERIQUES
// =============================================================================================
void Configuration_GPIO_EXP(SPIClass& spi,uint8_t clkPin,uint8_t misoPin,uint8_t mosiPin,uint8_t cs3Pin,uint8_t ethRst,uint8_t MCPaddr);
void Configuration_COM_Modbus(HardwareSerial& ModBus_Uart, ModbusRTU& mb);
// =============================================================================================
// Extraction 
// =============================================================================================