#ifndef HYDRO_SHIELD_INTERFACE_H
#define HYDRO_SHIELD_INTERFACE_H

#include <stdint.h>

/**
 * @brief Tipo opaco (Opaque Pointer) conforme allo standard MISRA C:2012.
 *        Nasconde l'allineamento dei registri parametrici a 180 Byte,
 *        il passo temporale dinamico e lo stimatore single-pass di Bohrnstedt.
 *        Garantisce ZERO leak di Proprietà Intellettuale reale (IP).
 */
typedef struct HydroFlowEngine_t HydroFlowEngine;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Inizializza il core idraulico parametrizzato in RAM statica packed (180B).
 * @param e Puntatore opaco alla struttura dati privata del firmware.
 * @param calibration_ticks Snapshot stazionari necessari per la caratterizzazione iniziale.
 * @param max_mm Escursione massima di targa fisica del rocchetto servovalvola (mm).
 * @param max_bar Pressione massima di esercizio nominale della pompa di banchina (bar).
 * @param dt_nominal Passo temporale reale di campionamento del bus di bordo (secondi).
 * @param walther_exp Coefficiente di attivazione termica per la viscosità cinematica dell'olio.
 */
void HydroFlow_Init(HydroFlowEngine* e, uint64_t calibration_ticks, double max_mm, double max_bar, double dt_nominal, double walther_exp);

/**
 * @brief Monitora ed isola asimmetricamente i guasti delle servovalvole (SAE ARP4754A).
 * @return Codice intero Int32 offuscato per la Fault Isolation (2=Nominale, 4=Ostruzione, 5=Leakage).
 */
int32_t HydroFlow_ProcessaCanali(
    HydroFlowEngine* e, 
    double spostamento_valvola, 
    double delta_pressione, 
    double temp_celsius,
    double dt_seconds,
    double* out_covarianza, 
    double* out_z_score
);

#ifdef __cplusplus
}
#endif

#endif // HYDRO_SHIELD_INTERFACE_H
