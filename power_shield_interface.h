#ifndef POWER_CONV_INTERFACE_H
#define POWER_CONV_INTERFACE_H

#include <stdint.h>

/**
 * @brief Tipo opaco (Opaque Pointer) conforme allo standard MISRA C:2012.
 *        Nasconde l'allineamento dei registri parametrici a 204 Byte,
 *        la pendenza incrementale a 50 kHz e lo scudo di release.
 *        Garantisce ZERO leak di Proprietà Intellettuale reale (IP).
 */
typedef struct PowerConvPrognosticEngine_t PowerConvPrognosticEngine;

typedef enum {
    POWER_CALIBRAZIONE = 0,
    POWER_OPERATIVO_OK = 2,
    POWER_CRITICAL_LIFTOFF_ALERT = 3
} PowerConvState;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Inizializza il modulo prognostico dell'inverter di potenza SiC in RAM packed (204B).
 */
void PowerConv_Init(PowerConvPrognosticEngine* e, double design_life_hours, uint32_t calibration_ticks, double deadband_mult, double collasso_mult);

/**
 * @brief Monitora in tempo reale la fatica termomeccanica dei bond-wire isolando i transitori.
 * @return Codice stato PowerConvState (2=Nominale OK, 3=Allerta Liftoff Critica).
 */
PowerConvState PowerConv_MonitoraInverter(
    PowerConvPrognosticEngine* e, 
    double temp_giunzione_celsius, 
    double corrente_fase_ampere, 
    double* out_danno_coffin, 
    double* out_rul
);

#ifdef __cplusplus
}
#endif

#endif // POWER_CONV_INTERFACE_H
