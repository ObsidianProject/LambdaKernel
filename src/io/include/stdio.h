#ifndef IO_H
#define IO_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "./common.h"

namespace systd
{
#define VGA_ADDRESS 0xB8000
#define BUFSIZE 2200

	void clear_row(size_t row);
	void clear_col(size_t column);
	void print_clear();
	void print_newline();
	void putc(char character);
	void puts(const char *str);
	void init_tty(uint8_t fg, uint8_t bg);
	void print_int(int num);
	void print_set_color(uint8_t foreground, uint8_t background);
	void app_terminal_start();
	string get_input(int length);

#define NUM_COLS 80
#define NUM_ROWS 25

	enum 
	{
		VGA_COLOR_BLACK = 0,
		VGA_COLOR_BLUE = 1,
		VGA_COLOR_GREEN = 2,
		VGA_COLOR_CYAN = 3,
		VGA_COLOR_RED = 4,
		VGA_COLOR_MAGENTA = 5,
		VGA_COLOR_BROWN = 6,
		VGA_COLOR_LIGHT_GRAY = 7,
		VGA_COLOR_DARK_GRAY = 8,
		VGA_COLOR_LIGHT_BLUE = 9,
		VGA_COLOR_LIGHT_GREEN = 10,
		VGA_COLOR_LIGHT_CYAN = 11,
		VGA_COLOR_LIGHT_RED = 12,
		VGA_COLOR_PINK = 13,
		VGA_COLOR_YELLOW = 14,
		VGA_COLOR_WHITE = 15,
	};

}
#endif