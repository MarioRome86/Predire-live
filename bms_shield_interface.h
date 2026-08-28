#ifndef BMS_SHIELD_INTERFACE_H
#define BMS_SHIELD_INTERFACE_H

#include <stdint.h>

/**
 * @brief Tipo opaco (Opaque Pointer) conforme allo standard MISRA C:2012.
 *        Nasconde interamente l'allineamento dei registri hardware a 188 Byte,
 *        lo sblocco asimmetrico della persistenza e l'algebra di Arrhenius.
 *        Garantisce ZERO leak di Proprietà Intellettuale (IP).
 */
typedef struct BmsPrognosticEngine_t BmsPrognosticEngine;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Inizializza il modulo prognostico dell'accumulo (BMS) in RAM statica pre-allocata.
 */
void BmsShield_Init(BmsPrognosticEngine* engine, float design_life_cycles, uint32_t calibration_ticks);

/**
 * @brief Monitora in tempo reale l'invecchiamento elettrochimico dell'UAV ad RMSE depurato.
 * @return Codice intero Int32 offuscato per la Fault Isolation (2=Nominale, 3=Allerta Critica).
 */
int32_t BmsShield_MonitoraBatteria(
    BmsPrognosticEngine* engine, 
    float v_volt, 
    float i_ampere, 
    float temp_celsius, 
    float* out_degrade, 
    float* out_rul
);

#ifdef __cplusplus
}
#endif

#endif // BMS_SHIELD_INTERFACE_H
