#include "display.h"
#include <generated/csr.h>

void display(char motifs[8]) {
	display_dig_0_write(motifs[7]);
	display_dig_1_write(motifs[6]);
	display_dig_2_write(motifs[5]);
	display_dig_3_write(motifs[4]);
	display_dig_4_write(motifs[3]);
	display_dig_5_write(motifs[2]);
	display_dig_6_write(motifs[1]);
	display_dig_7_write(motifs[0]);
}

void display_score(int score) {
    char motifs[8] = {0}; // Initialize the array with zeros
    int digits[8] = {0};  // Array to store individual digits of the score
    int tempScore = score;
    int index = 7;

    // Extract each digit of the score
    while (tempScore > 0 && index >= 0) {
        digits[index] = tempScore % 10;
        tempScore /= 10;
        index--;
    }

    // Map digits to 7-segment display patterns
    for (int i = 0; i < 8; i++) {
        switch (digits[i]) {
            case 0: motifs[i] = display_0; break;
            case 1: motifs[i] = display_1; break;
            case 2: motifs[i] = display_2; break;
            case 3: motifs[i] = display_3; break;
            case 4: motifs[i] = display_4; break;
            case 5: motifs[i] = display_5; break;
            case 6: motifs[i] = display_6; break;
            case 7: motifs[i] = display_7; break;
            case 8: motifs[i] = display_8; break;
            case 9: motifs[i] = display_9; break;
            default: motifs[i] = 0; break;
        }
    }

    // Update the display with the score
    display(motifs);
}