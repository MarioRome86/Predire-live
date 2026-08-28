#ifndef ACTUATOR_SHIELD_INTERFACE_H
#define ACTUATOR_SHIELD_INTERFACE_H

#include <stdint.h>

/**
 * @brief Tipo opaco (Opaque Pointer) conforme allo standard MISRA C:2012.
 *        Nasconde l'allineamento dei registri parametrici a 92 Byte reali packed,
 *        la regressione lineare di coda e lo scudo di tolleranza anti-raffica.
 *        Garantisce ZERO leak di Proprietà Intellettuale reale (IP).
 */
typedef struct ActuatorPrognosticStruct_t ActuatorPrognosticStruct;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Inizializza il core attuatori dei flap in RAM packed (92B) parametrica.
 * @param e Puntatore opaco alla struttura dati privata del firmware.
 * @param design_life_cycles Cicli operativi nominali di progetto dell'attuatore.
 * @param calibration_ticks Snapshot stazionari necessari per la caratterizzazione iniziale.
 * @param collasso_mult Moltiplicatore asintotico di proiezione del collasso di coda per la RUL.
 */
void ActuatorShield_Init(ActuatorPrognosticStruct* e, float design_life_cycles, uint32_t calibration_ticks, float collasso_mult);

/**
 * @brief Monitora l'efficienza energetica del flap isolando le raffiche aerodinamiche.
 * @return Codice stato Int32 (2=Nominale OK, 3=Allerta Critica Manutenzione EMA).
 */
int32_t ActuatorShield_MonitoraFlap(
    ActuatorPrognosticStruct* e, 
    float corrente_ampere, 
    float velocita_deg_sec, 
    float* deviazione_out, 
    float* rul_out
);

#ifdef __cplusplus
}
#endif

#endif // ACTUATOR_SHIELD_INTERFACE_H
