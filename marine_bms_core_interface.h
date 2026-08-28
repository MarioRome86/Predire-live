#ifndef MARINE_PROPULSION_INTERFACE_H
#define MARINE_PROPULSION_INTERFACE_H

#include <stdint.h>

/**
 * @brief Tipo opaco (Opaque Pointer) conforme allo standard MISRA C:2012.
 *        Nasconde l'allineamento dei registri parametrici acustici a 288 Byte packed,
 *        l'algoritmo single-pass dell'Entropia di Shannon e la regressione fenotipica.
 *        Garantisce ZERO leak di Proprietà Intellettuale reale (IP).
 */
typedef struct MarinePropulsionEngine_t MarinePropulsionEngine;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Inizializza il modulo prognostico marino in RAM packed (288B) esente da costanti fisse.
 */
void MarinePropulsion_Init(
    MarinePropulsionEngine* e, double design_life_secs, uint32_t calibration_ticks, 
    double max_rpm, double max_volt, double min_volt_floor, double underflow_floor,
    double safety_window, uint32_t init_skip_ticks, double kelvin_zero, double temp_ref,
    double ewma_alpha, uint32_t win_size, double deadband_mult, double collasso_mult,
    double fluid_cp, double fluid_r, double tikhonov_reg
);

/**
 * @brief Monitora in tempo reale l'insorgere della micro-cavitazione sulle pale elica.
 * @return Codice stato Int32 (2=Nominale OK, 3=Allerta Critica Cavitazione).
 */
int32_t MarinePropulsion_MonitoraElica(
    MarinePropulsionEngine* e, double rpm_elica, double idrofono_volt, 
    double* out_entropy, double* out_rul
);

#ifdef __cplusplus
}
#endif

#endif // MARINE_PROPULSION_INTERFACE_H
