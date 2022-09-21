#pragma once

#include <stdint.h>

#define FRAMEBUFFER_RED             0XFFAA0000
#define FRAMEBUFFER_GREEN           0XFF00AA00
#define FRAMEBUFFER_BLUE            0XFF0000AA
#define FRAMEBUFFER_CYAN            0XFF00AAAA
#define FRAMEBUFFER_PURPLE          0XFFAA00AA
#define FRAMEBUFFER_YELLOW          0XFFAAAA00
#define FRAMEBUFFER_GREY            0XFF444444
#define FRAMEBUFFER_WHITE           0XFFAAAAAA

#define FRAMEBUFFER_BLACK           0XFF000000

#define FRAMEBUFFER_BRIGHT_RED      0XFFFF0000
#define FRAMEBUFFER_BRIGHT_GREEN    0XFF00FF00
#define FRAMEBUFFER_BRIGHT_BLUE     0XFF0000FF
#define FRAMEBUFFER_BRIGHT_CYAN     0XFF00FFFF
#define FRAMEBUFFER_BRIGHT_PURPLE   0XFFFF00FF
#define FRAMEBUFFER_BRIGHT_YELLOW   0XFFFFFF00
#define FRAMEBUFFER_BRIGHT_GREY     0XFF888888
#define FRAMEBUFFER_BRIGHT_WHITE    0XFFFFFFFF

// Colours are in aarrggbb format
void framebuffer_init(uint32_t* fb, uint16_t width, uint16_t height, uint16_t pixelsPerRow, uint32_t backgroundColour, uint32_t foregroundColour);
void framebuffer_set_background_colour(uint32_t colour);
void framebuffer_set_Background_Colour(uint32_t colour);

uint16_t framebuffer_get_width();
uint16_t framebuffer_get_height();

void framebuffer_clear();
void framebuffer_scroll(uint16_t pixels);

void framebuffer_print_char_bmp(uint8_t bitmap[120], uint16_t screenStartX, uint16_t screenStartY);

void framebuffer_put_char(char c);