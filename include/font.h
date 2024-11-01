#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include "buffer.h"
#include <stdint.h>

typedef struct {
	uint32_t width;
	uint32_t height;
} FontSize;

void init_freetype();
char *get_font_file();
void load_font(const char *filename);
FontSize get_font_size();
void write_glyph_to_buffer(char character, struct Buffer *buf);
