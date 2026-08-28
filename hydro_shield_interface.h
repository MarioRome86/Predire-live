#ifndef HYDRO_SHIELD_INTERFACE_H
#define HYDRO_SHIELD_INTERFACE_H

#include <stdint.h>

/**
 * @brief Tipo opaco (Opaque Pointer) conforme alle linee guida MISRA C:2012.
 *        Nasconde interamente la geometria della RAM (144 Byte) ed i registri
 *        di accumulo dei Momenti Centrali Superiori, bloccando il reverse-engineering.
 */
typedef struct HydroPrognosticEngine_t HydroPrognosticEngine;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Inizializza il core prognostico fluidodinamico in RAM statica pre-allocata.
 * @param engine Puntatore opaco alla struttura dati privata del firmware.
 * @param design_life_hours Cicli di vita target o ore di esercizio targa dell'asset.
 * @param calibration_ticks Numero di impulsi stazionari per la calibrazione asintotica.
 */
void HydroShield_Init(HydroPrognosticEngine* engine, float design_life_hours, uint32_t calibration_ticks);

/**
 * @brief Monitora a scatola chiusa la stabilità idrodinamica e l'innesco della cavitazione.
 *        Esegue il test d'ipotesi sequenziale online basato su Z-Score asintotico.
 * @param engine Puntatore opaco alla struttura dati privata del firmware.
 * @param press_differenziale Lettura istantanea filtrata della pressione (Bar).
 * @param portata_litri_min Lettura istantanea della portata di esercizio (L/min).
 * @param out_z_score Puntatore alla variabile di uscita per lo Z-Score standardizzato di Pearson.
 * @param out_rul Puntatore alla variabile di uscita per la stima dinamica della RUL (ore).
 * @return Codice intero Int32 offuscato numericamente per la mappa degli stati residenti a terra.
 */
int32_t HydroShield_MonitoraPompa(
    HydroPrognosticEngine* engine, 
    float press_differenziale, 
    float portata_litri_min, 
    float* out_z_score, 
    float* out_rul
);

#ifdef __cplusplus
}
#endif

#endif // HYDRO_SHIELD_INTERFACE_H
