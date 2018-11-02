#ifndef _VECTOR_VECTOR_H_
#define _VECTOR_VECTOR_H_
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <vector/vector_type.h>
typedef uint8_t vector_type_id;
typedef struct vector vector;
typedef struct vector_private vector_private;
struct vector {
	vector_private *v_priv;
	int (*at) (vector *v, size_t pos, ...);
	int (*set) (vector *v, size_t pos, ...);
	int (*front) (vector *v, ...);
	int (*back) (vector *v, ...);
	void* (*data) (vector *v);
	bool (*empty) (vector *v);
	size_t (*size) (vector *v);
	size_t (*max_size) (void);
	void (*reserve) (vector *v, size_t new_cap);
	size_t (*capacity) (vector *v);
	void (*clear) (vector *v);
	int (*insert) (vector *v, size_t pos, ...);
	int (*remove) (vector *v, size_t pos);
	int (*push_back) (vector *v, ...);
	int (*pop_back) (vector *v);
	int (*resize) (vector *v, size_t count, ...);
	void (*destroy) (vector *v);
	void (*shrink_to_fit) (vector *v);
};
vector *vector_create(vector_type_id type, size_t size);
#endif /* _VECTOR_VECTOR_H_ */
