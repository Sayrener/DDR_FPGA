#include <generated/csr.h>
#include "delay.h"

#define SYS_CLOCK_HZ 100000000  // Remplacer par la fréquence de votre horloge (100 MHz par exemple)

// Fonction de délai en millisecondes

void delay_ms(unsigned int ms) {
    // Calculer la valeur à charger dans le timer
    unsigned int load_value = SYS_CLOCK_HZ/1000*ms;

    timer0_en_write(0);
    timer0_reload_write(0);          // Définir la valeur de rechargement (pour un timer continu)
    timer0_load_write(load_value);            // Charger la valeur dans le timer   
    timer0_en_write(1);                       // Activer le timer
    timer0_update_value_write(1);
    // Attendre que le timer expire
    while(timer0_value_read())
    {
    	timer0_update_value_write(1);
    }
    ;  // Vérifier si le timer a expiré (bit 0 de la valeur)

    // Désactiver le timer après utilisation
    timer0_en_write(0);
}

// Fonction de délai en millisecondes
void delay_us(unsigned int us) {
    // Calculer la valeur à charger dans le timer
    unsigned int load_value = SYS_CLOCK_HZ/1000000*us;

    timer0_en_write(0);
    timer0_reload_write(0);          // Définir la valeur de rechargement (pour un timer continu)
    timer0_load_write(load_value);            // Charger la valeur dans le timer   
    timer0_en_write(1);                       // Activer le timer
    timer0_update_value_write(1);
    // Attendre que le timer expire
    while(timer0_value_read())
    {
    	timer0_update_value_write(1);
    }
    ;  // Vérifier si le timer a expiré (bit 0 de la valeur)

    // Désactiver le timer après utilisation
    timer0_en_write(0);
}