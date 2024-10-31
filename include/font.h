#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include <stdint.h>
#include "buffer.h"

#define FONT_SIZE 32

void init_freetype();
char *get_font_file();
void load_font(const char *filename);
void write_glyph_to_buffer(char character, struct Buffer *buf);
