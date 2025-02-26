#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <irq.h>
#include <libbase/uart.h>
#include <libbase/console.h>
#include <generated/csr.h>

#include "ddr.h"

/*-----------------------------------------------------------------------*/
/* Uart                                                                  */
/*-----------------------------------------------------------------------*/

static char *readstr(void)
{
	char c[2];
	static char s[64];
	static int ptr = 0;

	if(readchar_nonblock()) {
		c[0] = getchar();
		c[1] = 0;
		switch(c[0]) {
			case 0x7f:
			case 0x08:
				if(ptr > 0) {
					ptr--;
					fputs("\x08 \x08", stdout);
				}
				break;
			case 0x07:
				break;
			case '\r':
			case '\n':
				s[ptr] = 0x00;
				fputs("\n", stdout);
				ptr = 0;
				return s;
			default:
				if(ptr >= (sizeof(s) - 1))
					break;
				fputs(c, stdout);
				s[ptr] = c[0];
				ptr++;
				break;
		}
	}

	return NULL;
}

static char *get_token(char **str)
{
	char *c, *d;

	c = (char *)strchr(*str, ' ');
	if(c == NULL) {
		d = *str;
		*str = *str+strlen(*str);
		return d;
	}
	*c = 0;
	d = *str;
	*str = c+1;
	return d;
}

static void prompt(void)
{
	printf("\e[92;1mdance-dance-revolution-app\e[0m> ");
}

/*-----------------------------------------------------------------------*/
/* Help                                                                  */
/*-----------------------------------------------------------------------*/

static void help(void)
{
	puts("\nDance Dance Revolution App built on "__DATE__" "__TIME__"\n");
	puts("Available commands:");
	puts("help               - Show this command");
	puts("reboot             - Reboot CPU");
#ifdef CSR_LEDS_BASE
	puts("led                - Led demo");
#endif
#ifdef CSR_VIDEO_FRAMEBUFFER_BASE
	puts("ddr                - Dance Dance Revolution");
#endif
}

/*-----------------------------------------------------------------------*/
/* Welcome                                                               */
/*-----------------------------------------------------------------------*/

static void welcome(void)
{
    puts("\033[1;35m" // Magenta + Gras
        "    ___                          ___                         __                 _       _   _             \n"
        "   /   \\__ _ _ __   ___ ___     /   \\__ _ _ __   ___ ___    /__\\ _____   _____ | |_   _| |_(_) ___  _ __  \n"
        "  / /\\ / _` | '_ \\ / __/ _ \\   / /\\ / _` | '_ \\ / __/ _ \\  / \\/// _ \\ \\ / / _ \\| | | | | __| |/ _ \\| '_ \\ \n"
        " / /_// (_| | | | | (_|  __/  / /_// (_| | | | | (_|  __/ / _  \\  __/\\ V / (_) | | |_| | |_| | (_) | | | |\n"
        "/___,' \\__,_|_| |_|\\___\\___| /___,' \\__,_|_| |_|\\___\\___| \\/ \\_/\\___| \\_/ \\___/|_|\\__,_|\\__|_|\\___/|_| |_|\n"
        "\033[0m" // Réinitialisation après l'ASCII art
        "\n"
        "----------------------------------------------------------------------------------------------------------\n"
        "\033[1m" // Gras uniquement
        "                         Developed by Antoine Madrelle and Tangi Brandeho\n"
        "\033[0m" // Désactive le gras
        "----------------------------------------------------------------------------------------------------------\n"
    );
}

/*-----------------------------------------------------------------------*/
/* Commands                                                              */
/*-----------------------------------------------------------------------*/

static void reboot_cmd(void)
{
	ctrl_reset_write(1);
}

#ifdef CSR_LEDS_BASE
static void led_cmd(void)
{
	int i;
	printf("Led demo...\n");

	printf("Counter mode...\n");
	for(i=0; i<32; i++) {
		leds_out_write(i);
		busy_wait(100);
	}

	printf("Shift mode...\n");
	for(i=0; i<4; i++) {
		leds_out_write(1<<i);
		busy_wait(200);
	}
	for(i=0; i<4; i++) {
		leds_out_write(1<<(3-i));
		busy_wait(200);
	}

	printf("Dance mode...\n");
	for(i=0; i<4; i++) {
		leds_out_write(0x55);
		busy_wait(200);
		leds_out_write(0xaa);
		busy_wait(200);
	}
}
#endif

static void ddr_cmd(void)
{
	printf("Dance Dance Revolution...\n");
	ddr();
}

/*-----------------------------------------------------------------------*/
/* Console service / Main                                                */
/*-----------------------------------------------------------------------*/

static void console_service(void)
{
	char *str;
	char *token;

	str = readstr();
	if(str == NULL) return;
	token = get_token(&str);
	if(strcmp(token, "help") == 0)
		help();
	else if(strcmp(token, "reboot") == 0)
		reboot_cmd();
#ifdef CSR_LEDS_BASE
	else if(strcmp(token, "led") == 0)
		led_cmd();
#endif
#ifdef CSR_VIDEO_FRAMEBUFFER_BASE
	else if(strcmp(token, "ddr") == 0)
		ddr_cmd();
#endif
	prompt();
}

int main(void)
{
#ifdef CONFIG_CPU_HAS_INTERRUPT
	irq_setmask(0);
	irq_setie(1);
#endif
	uart_init();

	welcome();
	help();
	prompt();

	while(1) {
		console_service();
	}

	return 0;
}
