#include "font.h"

#include "buffer.h"

#include <stdio.h>
#include <linux/limits.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


FT_Library freetype;
FT_Face font;

char *get_font_file() {
	FILE *command = popen("fc-match monospace file", "r");
	if (command == NULL) {
		fprintf(stderr, "Failed to execute fc-match");
		return NULL;
	}
	int remove_size = sizeof(":file=");
	char line[PATH_MAX + remove_size]; // PATH_MAX + other output
	char *path = malloc(PATH_MAX);
	if (path == NULL) {
		perror("path malloc");
	}
	memset(path, 0, PATH_MAX);
	if (fgets(line, sizeof(line), command) != NULL) {
		memcpy(path, line + remove_size - 1, strlen(line) - remove_size);
		path[strlen(line) - remove_size] = 0;
		// printf("path: \"%s\"\n", path);
	}
	pclose(command);
	return path;
}

void init_freetype() {
	FT_Error err = FT_Init_FreeType(&freetype);
	if (err != FT_Err_Ok) {
		fprintf(stderr, "Failed to init freetype: %s", FT_Error_String(err));
		exit(EXIT_FAILURE);
	}
}

void load_font(const char *filename) {
	FT_Error err = FT_New_Face(freetype, filename, 0, &font);
	if (err == FT_Err_Unknown_File_Format) {
		fprintf(stderr, "Unrecognized font format: \"%s\"\n", filename);
		FT_Done_FreeType(freetype);
		exit(EXIT_FAILURE);
	}

	printf("Succesfuly loaded font: \"%s\"\n", font->family_name);
}

void write_glyph_to_buffer(char character, struct Buffer *buf) {
	if (buf == NULL) {
		fprintf(stderr, "Unable to write glyph to NULL Buffer\n.");
	}

	FT_Set_Pixel_Sizes(font, 0, FONT_SIZE);
	FT_UInt glyph_index = FT_Get_Char_Index(font, character);
	FT_Load_Glyph(font, glyph_index, FT_LOAD_DEFAULT);
	FT_Render_Glyph(font->glyph, FT_RENDER_MODE_NORMAL);

	fill_buffer(buf, (struct Pixel){0, 0, 0, 0});
	assert(font->glyph->bitmap.pixel_mode == FT_PIXEL_MODE_GRAY);
	FT_Bitmap bitmap = font->glyph->bitmap;
	for (int x = 0; x < font->glyph->bitmap.width; x++) {
		for (int y = 0; y < font->glyph->bitmap.rows; y++) {
			char value = bitmap.buffer[y * bitmap.pitch + x];
			if (value == 0) {
				write_pixel_to_buffer(buf, x, y, (struct Pixel){0, 0, 0, 0});
			} else {
				write_pixel_to_buffer(buf, x, y, (struct Pixel){value, value, value, 255});
			}
		}
	}
}
