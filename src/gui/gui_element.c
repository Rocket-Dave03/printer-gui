#include "gui/gui_element.h"
#include <stdlib.h>
#include <assert.h>

void gui_delete_element(struct GuiElement *elem) {
	if (elem == NULL) {
		return;
	}
	for(int i = 0; i < elem->childCount; i++) {
		gui_delete_element(elem->children[i]);
	}
	free(elem->data);
	elem->data = NULL;
	free(elem);
}

void gui_propogate_update(struct GuiElement *elem, GuiUpdateType type) {
	assert(type != GUI_UPDATE_STATIC);
	
}
