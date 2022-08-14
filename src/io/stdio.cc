#include "./include/stdio.h"
#include "./include/keyboard.h"

namespace systd
{
    struct Char
    {
        uint8_t character;
        uint8_t color;
    };

    struct Char *buffer = (struct Char *)0xb8000;
    uint8_t color = VGA_COLOR_WHITE | VGA_COLOR_BLACK << 4;
    char *char_mem;
    size_t col = 0;
    size_t row = 0;
    size_t input_pos = 0;
    size_t block_del_pos = 0;
    void clear_row(size_t row)
    {
        struct Char empty = (struct Char){
            character : ' ',
            color : color,
        };

        for (size_t col = 0; col < NUM_COLS; col++)
        {
            buffer[col + NUM_COLS * row] = empty;
        }
    }
    void clear_col(size_t column)
    {
        column--;
        if (input_pos <= block_del_pos)
        {
        }
        else
        {
            col--;
            struct Char empty = (struct Char){
                character : ' ',
                color : color,
            };
            buffer[column + NUM_COLS * row] = empty;
            input_pos--;
        }
    }

    void init_tty(uint8_t fg, uint8_t bg)
    {
        print_set_color(fg, bg);
        print_clear();
    }

    void print_clear()
    {
        for (size_t i = 0; i < NUM_ROWS; i++)
        {
            clear_row(i);
        }
    }

    void print_newline()
    {
        col = 0;

        if (row < NUM_ROWS)
        {
            row++;
            return;
        }

        for (size_t row = 0; row < NUM_ROWS; row++)
        {
            for (size_t col = 0; col < NUM_COLS; col++)
            {
                struct Char character = buffer[col + NUM_COLS * row];
                buffer[col + NUM_COLS * (row - 1)] = character;
            }
        }

        clear_row(NUM_COLS - 1);
    }

    void putc(char character)
    {
        if (character == '\n')
        {
            print_newline();
            return;
        }

        if (col > NUM_COLS)
        {
            print_newline();
        }

        buffer[col + NUM_COLS * row] = (struct Char){
            character : (uint8_t)character,
            color : color,
        };
        input_pos = col + NUM_COLS * row;
        col++;
    }

    void puts(const char *str)
    {
        for (size_t i = 0; 1; i++)
        {
            *(char_mem + 1) = *str;
            char character = (uint8_t)str[i];

            if (character == '\0')
            {
                return;
            }
            putc(character);
        }
    }

    void print_int(int num)
    {
        char str_num[digit_count(num) + 1];
        itoa(num, str_num);
        puts(str_num);
    }

    bool capslock = false;
    bool shift = false;
    bool alt = false;
    bool ctrl = false;
    bool numlock = true;
    bool scrolllock = false;

    void wait_for_io(uint32 timer_count)
    {
        while (1)
        {
            asm volatile("nop");
            timer_count--;
            if (timer_count <= 0)
                break;
        }
    }
    void sleep(uint32 timer_count)
    {
        wait_for_io(timer_count);
    }

    void print_set_color(uint8_t foreground, uint8_t background)
    {
        color = foreground + (background << 4);
    }

    void app_terminal_start()
    {
        char ch = 0;
        char keycode = 0;
        do
        {
            keycode = get_input_keycode();
            if (keycode == KEY_ENTER)
            {
                print_newline();
            }
            else if (keycode == KEY_BACKSPACE)
            {
                clear_col(col);
            }
            else if (keycode == KEY_LEFT_ALT_PRESS)
            {
                alt = true;
            }
            else if (keycode == KEY_LEFT_SHIFT_PRESS)
            {
                shift = true;
            }
            else if (keycode == KEY_LEFT_CTRL_PRESS)
            {
                ctrl = true;
            }
            else if (keycode == KEY_LEFT_ALT_RELEASE)
            {
                alt = false;
            }
            else if (keycode == KEY_LEFT_SHIFT_RELEASE)
            {
                shift = false;
            }
            else if (keycode == KEY_LEFT_CTRL_RELEASE)
            {
                ctrl = false;
            }
            else if (keycode == KEY_CAPS_LOCK_PRESS)
            {
                // print_str("CAPS LOCK");
                capslock = !capslock;
                puts((char *)capslock);
            }
            else
            {
                if (capslock || shift)
                {
                    // we're capitalized
                    ch = get_ascii_char(keycode);
                }
                else
                {
                    ch = get_ascii_char_lower(keycode);
                }

                putc(ch);
            }
            sleep(0x02faf080);
        } while (ch > 0);
    }
}