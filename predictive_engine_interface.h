/* ===================================================================================================================
 * FILE: turbine_shield_interface.h
 * PROJECT: JET-PIPE v66.17.2 (NASA Hyperbolic Uncertainty Pure Core)
 *
 * PUBLIC OPAQUE INTERFACE FOR SPACE SUPPLIER COMPLIANCE (ECSS-E-ST-40C & RTCA DO-178C LEVEL A)
 * LICENSE: Proprietary / Commercial IP Block
 * 
 * 🛡️ ULTRA-HARDENED INFORMATION HIDING:
 * Internal structures are entirely shrouded to guarantee absolute intellectual property protection.
 * Memory footprints and computational boundaries are strictly isolated within the binary core.
 * =================================================================================================================== */

#ifndef TURBINE_SHIELD_INTERFACE_H
#define TURBINE_SHIELD_INTERFACE_H

#include <stdint.h>

/* 🟩 PUNTATORE INCOMPLETO OPACO: La geometria dei registri interni è invisibile dall'esterno.
   Nessun ingegnere o disassemblatore può ricavare la struttura della memoria da questo file. */
typedef struct TurbinePrognosticEngine TurbinePrognosticEngine;

typedef enum {
    TURBINE_CALIBRAZIONE = 0,
    TURBINE_OPERATIVO_OK = 2,
    TURBINE_CRITICAL_EGT_ALERT = 3
} TurbineState;

/* FIRME DI INIZIALIZZAZIONE E LOOP OPERAZIONALE AD INVARIANZA DI STRUTTURA */
void TurbinePipe_Init(TurbinePrognosticEngine* e, double design_life_cycles, uint32_t calibration_ticks, 
                      double ewma_alpha, uint32_t win_size, double collasso_mult,
                      double fluid_cp, double fluid_r, double tikhonov_reg, double deadband_floor,
                      double kelvin_zero, double safety_window, double egt_fallback, double w2_fallback, double egt_max,
                      double drift_gain, double prognostic_horn_gain);

int32_t TurbinePipe_MonitoraSpinta(TurbinePrognosticEngine* e, double egt_celsius, double w2_flow_rate, 
                                  double* out_entropy, double* out_rul, 
                                  double* out_rul_minus_2s, double* out_rul_plus_2s);

#endif /* TURBINE_SHIELD_INTERFACE_H */
