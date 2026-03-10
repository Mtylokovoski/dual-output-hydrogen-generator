#include "config.h"
#include "sensors.h"
#include "logic.h"
#include "display.h"
#include <EEPROM.h>

float currentStorage = 0.0;
bool electrolysisEnabled = false;
unsigned long lastCalculationTime = 0;

void setup() {
    Serial.begin(9600);
    pinMode(PIN_RELAY, OUTPUT);
    digitalWrite(PIN_RELAY, LOW);
    
    // Load previously stored hydrogen volume
    EEPROM.get(EEPROM_ADDR_H2_STORAGE, currentStorage);
    if (isnan(currentStorage) || currentStorage < 0) {
        currentStorage = 0.0;
    }

    Serial.println(F("Hydrogen DIY System Initialized (2A Scale)"));
    Serial.print(F("Loaded Stored H2: ")); Serial.print(currentStorage); Serial.println(F(" L"));


    initDisplay();
}

void loop() {
    // Sensor values
    float I_elec = readCurrent(PIN_IELEC, ACS712_SENSITIVITY);
    float V_pem = readVoltage(PIN_VPEM, VPEM_DIVIDER_RATIO);
    float I_load = readCurrent(PIN_ILOAD, ACS712_SENSITIVITY);
    float V_load = readVoltage(PIN_VLOAD, VLOAD_DIVIDER_RATIO);
    float P_load = V_load * I_load; 

    // Logic update
    if (millis() - lastCalculationTime >= CALCULATION_INTERVAL) {
        float dt = CALCULATION_INTERVAL / 1000.0;
        
        float production = calculateH2Production(I_elec, dt);
        float consumption = calculateH2Consumption(P_load, dt);
        
        Serial.println("Current Storage: "+String(currentStorage));
        Serial.println("Production: "+String(consumption));
        Serial.println("Consumption: "+String(consumption));

        float oldStorage = currentStorage;
        updateStorage(currentStorage, production, consumption);
        
        // Persist to EEPROM if storage changed significantly or at regular intervals
        // Using a simple check to save on every calculation for now as it's 1s interval
        if (abs(currentStorage - oldStorage) > 0.001) {
            EEPROM.put(EEPROM_ADDR_H2_STORAGE, currentStorage);
        }

        bool nextState = calculateRelayState(currentStorage, electrolysisEnabled);
        if (nextState != electrolysisEnabled) {
            electrolysisEnabled = nextState;
            digitalWrite(PIN_RELAY, electrolysisEnabled ? HIGH : LOW);
            Serial.print(F("*** Relay switched: "));
            Serial.println(electrolysisEnabled ? F("ON") : F("OFF"));
        }

        printData(I_elec, V_pem, I_load, V_load, P_load);
        updateDisplay(I_elec, V_pem, currentStorage, electrolysisEnabled);
        lastCalculationTime = millis();
    }
    delay(100);
}

void printData(float I_elec, float V_pem, float I_load, float V_load, float P_load) {
    Serial.print(millis() / 1000); Serial.print(F(" | "));
    Serial.print(I_elec, 2); Serial.print(F("A | "));
    Serial.print(V_pem, 2); Serial.print(F("V | "));
    Serial.print(I_load, 2); Serial.print(F("A | "));
    Serial.print(V_load, 2); Serial.print(F("V | "));
    Serial.print(currentStorage, 2); Serial.print(F("L | "));
    Serial.println(electrolysisEnabled ? F("ON") : F("OFF"));
}
