#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "vm.h"
#include "gc.h"

vm_t* 
vm_new() {
    vm_t* self = malloc(sizeof(vm_t));
    self->stack_size = 0;
    self->gc = gc_new();
    return self;
}

void 
vm_free(vm_t* self) {

    // Clear the stack.
    if (self->stack_size > 0) {
        // We only need to free allocated slots.
        for (int i = 0; i < self->stack_size; i++) {
            value_free(self->stack[i]);
        }
    }

    gc_free(self->gc);
    free(self);
}

void
push_stack(vm_t* self, value_t* val) {
    // Stack Overflow
    if (self->stack_size == MAX_STACK_SIZE) {
        printf("The VM experienced a stack overflow. Exiting...");
        exit(-1);
    }

    gc_register_roots(self->gc, val);
    self->stack[self->stack_size++] = val;
}


value_t*
pop_stack(vm_t* self) {
    // Should we crash?
    if (self->stack_size == 0) {
        return NULL;
    }


    value_t* val = self->stack[self->stack_size - 1];
    gc_unregister_roots(self->gc, val);
    self->stack[self->stack_size - 1] = NULL;
    self->stack_size -= 1;

    return val;
}