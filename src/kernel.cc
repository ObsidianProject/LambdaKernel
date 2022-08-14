#include "./io/include/stdio.h"

extern "C" void Main(void) 
{
	
	systd::init_tty(systd::VGA_COLOR_WHITE, systd::VGA_COLOR_BLACK);

	systd::puts("enter your name: ");
	systd::app_terminal_start();
}
