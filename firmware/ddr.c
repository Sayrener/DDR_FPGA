#include <stdio.h>
#include <generated/csr.h>
#include <irq.h>

#include "delay.h"
#include "ddr.h"
#include "drawings.h"
#include "display.h"
#include "music.h"

#define SYS_CLOCK_HZ 100000000

int cpt_cs;
int cpt_frame;

int* ptr_cpt_cs = &cpt_cs; // Centième de seconde
int* ptr_cpt_frame = &cpt_frame;

void timer0_isr(void)
{
    unsigned int stat;

    stat = timer0_ev_pending_read();

    if(stat)
    {
        // Effacer le flag d'interruption
        timer0_ev_pending_write((uint32_t)1);

        // Incrémenter le compteur de centièmes de seconde
        *ptr_cpt_cs += 1;
    }
}

void timer0_init(void)
{
    // Effacer les interruptions en attente
    timer0_ev_pending_write(timer0_ev_pending_read());

    // Activer les interruptions du timer
    timer0_ev_enable_write(1);

    // Attacher l'interruption du timer à la fonction timer0_isr
    if (irq_attach)
        irq_attach(TIMER0_INTERRUPT, timer0_isr);

    // Activer le masque d'interruption pour le timer
    irq_setmask(irq_getmask() | (1 << TIMER0_INTERRUPT));
}

void setup_timer0(void)
{
    unsigned int load_value = SYS_CLOCK_HZ / 100;

    // Désactiver le timer
    timer0_en_write(0);

    // Charger la valeur dans le timer
    timer0_load_write(load_value);

    // Définir la valeur de rechargement
    timer0_reload_write(load_value);

    // Activer le timer
    timer0_en_write(1);
}

void ddr(void)
{
    cpt_cs = 0;
    cpt_frame = 0;
    int score = 0;
    int direction_arrow = 0;

    unsigned char* framebuffer = (unsigned char*)video_framebuffer_dma_base_read();

    char txt[8];

    sprintf(txt, "%c%c%c%c%c%c%c%c", display_G, display_A, display_M, display_E, 0, display_O, display_N, 0);
    display(txt);
    delay_ms(1000);

    clear_screen(framebuffer);

    timer0_init();
    setup_timer0();

    // Tableau pour stocker les flèches en cours d'affichage
    ActiveArrow activeArrows[50];
    int arrowCount = 0;
    int eventIndex = 0;

    int totalEvents = numEvents();

    // Boucle de jeu
    while (buttons_in_read() != BUTTON_ALL)
    {
        // Dessiner les carrés cibles
        draw_square(framebuffer, 104, 40, 0xFF);
        draw_square(framebuffer, 304, 40, 0xFF);
        draw_square(framebuffer, 504, 40, 0xFF);
        draw_square(framebuffer, 712, 40, 0xFF);

        // Vérifier les boutons pressés
        int buttons = buttons_in_read();
        if (buttons != 0)
        {
            // Parcourir toutes les flèches actives
            for (int i = 0; i < arrowCount; i++)
            {
                ActiveArrow arrow = activeArrows[i];

                // Déterminer la position X du carré cible en fonction de la direction de la flèche
                switch (arrow.direction)
                {
                    case UP:
                        direction_arrow = BUTTON_UP;
                        break;
                    case DOWN:
                        direction_arrow = BUTTON_DOWN;
                        break;
                    case LEFT:
                        direction_arrow = BUTTON_LEFT;
                        break;
                    case RIGHT:
                        direction_arrow = BUTTON_RIGHT;
                        break;
                    default:
                        break;
                }

                // Vérifier si la flèche est dans le carré cible
                if (direction_arrow == buttons && arrow.y >= 40 - 20 && arrow.y <= 40 + 20)
                {
                    score += 20;
                    // Remove the arrow from the list
                    for (int j = i; j < arrowCount - 1; j++)
                    {
                        activeArrows[j] = activeArrows[j + 1];
                    }
                    arrowCount--;
                    i--; // Check the current index again after removal
                }

                else if (direction_arrow == buttons && arrow.y >= 40 - 30 && arrow.y <= 40 + 30)
                {
                    score += 10;
                    // Remove the arrow from the lists
                    for (int j = i; j < arrowCount - 1; j++)
                    {
                        activeArrows[j] = activeArrows[j + 1];
                    }
                    arrowCount--;
                    i--; // Check the current index again after removal
                }

                else if (direction_arrow == buttons && arrow.y >= 40 - 40 && arrow.y <= 40 + 40)
                {
                    score += 5;
                    // Remove the arrow from the list
                    for (int j = i; j < arrowCount - 1; j++)
                    {
                        activeArrows[j] = activeArrows[j + 1];
                    }
                    arrowCount--;
                    i--; // Check the current index again after removal
                }
            }
        }

        // Vérifier si une nouvelle flèche doit apparaître
        if (eventIndex < totalEvents && *ptr_cpt_cs >= (int)(arrowEvents[eventIndex].time * 100))
        {
            if (arrowCount < 50) // Pour éviter de dépasser la mémoire
            {
                activeArrows[arrowCount].direction = arrowEvents[eventIndex].direction;
                activeArrows[arrowCount].y = SCREEN_HEIGHT;  // Commence en haut de l'écran

                // Définir la position X en fonction de la direction
                switch (arrowEvents[eventIndex].direction) 
                {
                    case UP:
                        activeArrows[arrowCount].x = 500;
                        break;
                    case DOWN:
                        activeArrows[arrowCount].x = 300;
                        break;
                    case LEFT:
                        activeArrows[arrowCount].x = 100;
                        break;
                    case RIGHT:
                        activeArrows[arrowCount].x = 700;
                        break;
                    default:
                        // Gérer un cas par défaut ou loguer une erreur
                        break;
                }

                arrowCount++; // Ajouter la flèche au tableau
                eventIndex++; // Passer à l'événement suivant
            }
        }

        if ((*ptr_cpt_cs % 1) == 0)  // Rafraîchir toutes les 10 millisecondes
        {
            clear_screen(framebuffer);

            // **2. Mettre à jour les flèches existantes**
            for (int i = 0; i < arrowCount; i++)
            {
                activeArrows[i].y -= 7;  // Faire descendre la flèche

                // Dessiner la flèche
                draw_arrow(framebuffer, activeArrows[i].x, activeArrows[i].y, 0x5E, activeArrows[i].direction);
            }
        }

        // Supprimer les flèches qui sortent de l'écran
        int newCount = 0;
        for (int i = 0; i < arrowCount; i++)
        {
            if (activeArrows[i].y > 0)  // Si la flèche est toujours visible
            {
                activeArrows[newCount] = activeArrows[i]; // Garder la flèche
                newCount++;
            }
        }
        arrowCount = newCount;  // Mettre à jour le nombre de flèches actives

        // Mettre à jour le score
        display_score(score);
        
    }

    sprintf(txt, "%c%c%c%c%c%c%c%c", display_G, display_A, display_M, display_E, display_O, display_V, display_E, display_R);
    display(txt);

    irq_detach(TIMER0_INTERRUPT);
    delay_ms(1000);
}
