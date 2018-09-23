#ifndef _VECTOR_VECTOR_PRIVATE_H_
#ifndef VECTOR_SOURCE_FILE
#error "Don't include the header in non-source file"
#endif /* VECTOR_SOURCE_FILE */
#define _VECTOR_VECTOR_PRIVATE_H_
#include <math.h>
#include <stdlib.h>
#include <string.h>
struct vector_private {
	vector_type_id v_id;
	size_t v_size;
	size_t v_cap;
	size_t v_type_size;
	void *v_ptr;
};
// Interfaces
static int vector_at(vector *v, size_t pos, ...);
static int vector_set(vector *v, size_t pos, ...);
static int vector_front(vector *v, ...);
static int vector_back(vector *v, ...);
static void* vector_data(vector *v);
static bool vector_empty(vector *v);
static size_t vector_size(vector *v);
static size_t vector_max_size(void);
static void vector_reserve(vector *v, size_t new_cap);
static size_t vector_capacity(vector *v);
static void vector_clear(vector *v);
static int vector_insert(vector *v, size_t pos, ...);
static int vector_remove(vector *v, size_t pos);
static int vector_push_back(vector *v, ...);
static int vector_pop_back(vector *v);
static int vector_resize(vector *v, size_t count, ...);
static void vector_destroy(vector *v);
#endif /* _VECTOR_VECTOR_PRIVATE_H_ */
