#include <stdlib.h>

#include "gc.h"


gc_t* gc_new() {
    gc_t* gc = malloc(sizeof(gc_t));
    gc->roots_size = 0;
    gc->objects = gc_list_new();
    return gc;
}

void gc_free(gc_t* self) {
    free(self);
}

gc_node_t* 
gc_node_new(value_t* val) {
    gc_node_t* self = malloc(sizeof(gc_node_t));
    self->value = val;
    self->next = NULL;
    return self;
}

// FIXME(TheHydroImpulse): Maybe this should also free the value itself?
void
gc_node_free(gc_node_t* self) {
    free(self);
}

gc_list_t*
gc_list_new() {
    gc_list_t* list = malloc(sizeof(gc_list_t));
    list->first = NULL;
    list->size = 0;
    return list;
}

void
gc_list_free(gc_list_t* self) {
    free(self);
}

void
gc_list_append(gc_list_t* self, value_t* value) {
    gc_node_t* n = gc_node_new(value);

    if (self->first) {
        gc_node_t* node = NULL;
        for (int i = 0; i < self->size; i++) {
            if (!node) {
                node = self->first;
            } else if (node->next != NULL) {
                node = node->next;
            }
        }
    } else {
        self->first = n;
    }

    self->size++;
}

void
gc_mark(gc_t* self) {

}

void
gc_register_roots(gc_t* self, value_t* value) {
    if (self->roots_size == MAX_STACK_SIZE) {
        return;
    }

    self->roots[self->roots_size++] = value;
}