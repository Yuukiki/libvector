#include <vector/vector.h>
#define VECTOR_SOURCE_FILE
#include <vector/vector_private.h>

#define VECTOR_CHECK_RETURN_VALUE(x, return_var) \
	if (!x) { \
		return return_var; \
	}

#define VECTOR_CHECK(x) \
	if (!x) { \
		return; \
	}

#define CALC_PTR(base, num, size) ((base) + (num) * (size))

#define VECTOR_TYPE_VALID_CHECK(type_id) \
	(type_id <= VECTOR_TYPE_LAST_ID)

#define CONDITIONAL_FREE(x) \
	if (x) { \
		free(x); \
	}

static void vector_memory_resize(vector *v, size_t new_cap)
{
	VECTOR_CHECK(v);
	void *stack_ptr = v->v_priv->v_ptr;
	size_t type_size = v->v_priv->v_type_size;
	size_t cap = v->v_priv->v_cap;
	size_t size = v->v_priv->v_size;
	if (cap != new_cap)
	{
		void *new_ptr = realloc(stack_ptr, new_cap * type_size);
		if (!new_ptr)
		{
			return;
		}
		if (new_cap < size)
		{
			v->v_priv->v_size = new_cap;
		}
		v->v_priv->v_ptr = new_ptr;
		v->v_priv->v_cap = new_cap;
		return;
	}
}

static int vector_get_value(vector *v, size_t pos, va_list list)
{
	size_t type_size = v->v_priv->v_type_size;
	void *stack_ptr = v->v_priv->v_ptr;
	vector_type_id type = v->v_priv->v_id;
	switch (type) {
		case VECTOR_TYPE_CHAR:
		{
			char *cptr = va_arg(list, char *);
			if (cptr == NULL) {
				va_end(list);
				return -1;
			}
			*cptr = *((char *) CALC_PTR(stack_ptr, pos, type_size));
			break;
		}
		case VECTOR_TYPE_UNSIGNED_CHAR:
		{
			unsigned char *ucptr = va_arg(list, unsigned char *);
			if (ucptr == NULL) {
				va_end(list);
				return -1;
			}
			*ucptr = *((unsigned char *) CALC_PTR(stack_ptr, pos, type_size));
			break;
		}
		case VECTOR_TYPE_SHORT:
                {
                        short *sptr = va_arg(list, short *);
                        if (sptr == NULL) {
                                va_end(list);
                                return -1;
                        }
                        *sptr = *((short *) CALC_PTR(stack_ptr, pos, type_size));
                        break;
                }
		case VECTOR_TYPE_UNSIGNED_SHORT:
                {
                        unsigned short *usptr = va_arg(list, unsigned short *);
                        if (usptr == NULL) {
                                va_end(list);
                                return -1;
                        }
                        *usptr = *((unsigned short *) CALC_PTR(stack_ptr, pos, type_size));
                        break;
                }
		case VECTOR_TYPE_INT:
                {
                        int *iptr = va_arg(list, int *);
                        if (iptr == NULL) {
                                va_end(list);
                                return -1;
                        }
                        *iptr = *((int *) CALC_PTR(stack_ptr, pos, type_size));
                        break;
                }
		case VECTOR_TYPE_UNSIGNED_INT:
		{
                        unsigned int *uiptr = va_arg(list, unsigned int *);
                        if (uiptr == NULL) {
                                va_end(list);
                                return -1;
                        }
                        *uiptr = *((unsigned int *) CALC_PTR(stack_ptr, pos, type_size));
                        break;
                }
		case VECTOR_TYPE_LONG:
                {
                        long *lptr = va_arg(list, long *);
                        if (lptr == NULL) {
                                va_end(list);
                                return -1;
                        }
                        *lptr = *((long *) CALC_PTR(stack_ptr, pos, type_size));
                        break;
                }
		case VECTOR_TYPE_UNSIGNED_LONG:
                {
                        unsigned long *ulptr = va_arg(list, unsigned long *);
                        if (ulptr == NULL) {
                                va_end(list);
                                return -1;
                        }
                        *ulptr = *((unsigned long *) CALC_PTR(stack_ptr, pos, type_size));
                        break;
                }
		case VECTOR_TYPE_FLOAT:
                {
                        float *fptr = va_arg(list, float *);
                        if (fptr == NULL) {
                                va_end(list);
                                return -1;
                        }
                        *fptr = *((float *) CALC_PTR(stack_ptr, pos, type_size));
                        break;
                }
		case VECTOR_TYPE_DOUBLE:
		{
                        double *dptr = va_arg(list, double *);
                        if (dptr == NULL) {
                                va_end(list);
                                return -1;
                        }
                        *dptr = *((double *) CALC_PTR(stack_ptr, pos, type_size));
                        break;
                }
		case VECTOR_TYPE_LONG_INT:
                {
                        long int *liptr = va_arg(list, long int *);
                        if (liptr == NULL) {
                                va_end(list);
                                return -1;
                        }
                        *liptr = *((long int *) CALC_PTR(stack_ptr, pos, type_size));
                        break;
                }
		case VECTOR_TYPE_LONG_LONG:
                {
                        long long *llptr = va_arg(list, long long *);
                        if (llptr == NULL) {
                                va_end(list);
                                return -1;
                        }
                        *llptr = *((long long *) CALC_PTR(stack_ptr, pos, type_size));
                        break;
                }
		case VECTOR_TYPE_LONG_DOUBLE:
                {
                        long double *ldptr = va_arg(list, long double *);
                        if (ldptr == NULL) {
                                va_end(list);
                                return -1;
                        }
                        *ldptr = *((long double *) CALC_PTR(stack_ptr, pos, type_size));
                        break;
                }
		case VECTOR_TYPE_BOOL:
                {
                        bool *bptr = va_arg(list, bool *);
                        if (bptr == NULL) {
                                va_end(list);
                                return -1;
                        }
                        *bptr = *((bool *) CALC_PTR(stack_ptr, pos, type_size));
                        break;
                }
		case VECTOR_TYPE_POINTER:
		{
                        void **vptr = va_arg(list, void **);
                        if (vptr == NULL) {
                                va_end(list);
                                return -1;
                        }
                        *vptr = CALC_PTR(stack_ptr, pos, type_size);
                        break;
                }
		default:
		{
			va_end(list);
			return -1; // Unknown type
		}
	}
	va_end(list);
	return 0;
}

static int vector_set_value(vector *v, size_t pos, va_list list)
{
	size_t type_size = v->v_priv->v_type_size;
	void *stack_ptr = v->v_priv->v_ptr;
	vector_type_id type = v->v_priv->v_id;
	switch (type) {
		case VECTOR_TYPE_CHAR:
		{
			char data = (char) va_arg(list, int);
			char *cptr = (char*) CALC_PTR(stack_ptr, pos, type_size);
			*cptr = data;
			break;
		}
		case VECTOR_TYPE_UNSIGNED_CHAR:
		{
			unsigned char data = (unsigned char) va_arg(list, int);
			unsigned char *ucptr = (unsigned char*) CALC_PTR(stack_ptr, pos, type_size);
			*ucptr = data;
			break;
		}
		case VECTOR_TYPE_SHORT:
                {
                        short data = (short) va_arg(list, int);
			short *sptr = (short *) CALC_PTR(stack_ptr, pos, type_size);
                        *sptr = data;
                        break;
                }
		case VECTOR_TYPE_UNSIGNED_SHORT:
                {
                        unsigned short data = (unsigned short) va_arg(list, int);
			unsigned short *usptr = (unsigned short *) CALC_PTR(stack_ptr, pos, type_size);
                        *usptr = data;
                        break;
                }
		case VECTOR_TYPE_INT:
                {
                        int data = (int) va_arg(list, int);
			int *iptr = (int *) CALC_PTR(stack_ptr, pos, type_size);
                        *iptr = data;
                        break;
                }
		case VECTOR_TYPE_UNSIGNED_INT:
		{
                        unsigned int data = (unsigned int) va_arg(list, int);
			unsigned int *uiptr = (unsigned int *) CALC_PTR(stack_ptr, pos, type_size);
                        *uiptr = data;
                        break;
                }
		case VECTOR_TYPE_LONG:
                {
                        long data = (long) va_arg(list, long);
			long *lptr = (long *) CALC_PTR(stack_ptr, pos, type_size);
                        *lptr = data;
                        break;
                }
		case VECTOR_TYPE_UNSIGNED_LONG:
                {
                        unsigned long data = va_arg(list, long);
			unsigned long *ulptr = (unsigned long*) CALC_PTR(stack_ptr, pos, type_size);
                        *ulptr = data;
                        break;
                }
		case VECTOR_TYPE_FLOAT:
                {
                        float data = (float) va_arg(list, double);
			float *fptr = (float *) CALC_PTR(stack_ptr, pos, type_size);
                        *fptr = data;
                        break;
                }
		case VECTOR_TYPE_DOUBLE:
		{
                        double data = (double) va_arg(list, double);
			double *dptr = (double *) CALC_PTR(stack_ptr, pos, type_size);
                        *dptr = data;
                        break;
                }
		case VECTOR_TYPE_LONG_INT:
                {
                        long int data = (long int) va_arg(list, long int);
			long int *liptr = (long int *) CALC_PTR(stack_ptr, pos, type_size);
                        *liptr = data;
                        break;
                }
		case VECTOR_TYPE_LONG_LONG:
                {
                        long long data = (long long) va_arg(list, long long);
			long long *llptr = (long long *) CALC_PTR(stack_ptr, pos, type_size);
                        *llptr = data;
                        break;
                }
		case VECTOR_TYPE_LONG_DOUBLE:
                {
                        long double data = (long double) va_arg(list, long double);
			long double *ldptr = (long double *) CALC_PTR(stack_ptr, pos, type_size);
                        *ldptr = data;
                        break;
                }
		case VECTOR_TYPE_BOOL:
                {
                        bool data = (bool) va_arg(list, int);
			bool *bptr = (bool *) CALC_PTR(stack_ptr, pos, type_size);
                        *bptr = data;
                        break;
                }
		case VECTOR_TYPE_POINTER:
		{
                        void *data = (void *) va_arg(list, void *);
			void **vptr = (void **) CALC_PTR(stack_ptr, pos, type_size);
                        *vptr = data;
                        break;
                }
		default:
		{
			va_end(list);
			return -1; // Unknown type
		}
	}
	va_end(list);
	return 0;
}

static size_t vector_sizeof_type(vector_type_id type)
{
	switch (type) {
		case VECTOR_TYPE_CHAR: // Fallback
		case VECTOR_TYPE_UNSIGNED_CHAR :
		{
			return sizeof(char);
		}
		case VECTOR_TYPE_SHORT: // Fallback
		case VECTOR_TYPE_UNSIGNED_SHORT:
		{
			return sizeof(short);
		}
		case VECTOR_TYPE_INT: // Fallback
		case VECTOR_TYPE_UNSIGNED_INT:
		{
			return sizeof(int);
		}
		case VECTOR_TYPE_LONG: // Fallback
		case VECTOR_TYPE_UNSIGNED_LONG:
		{
			return sizeof(long);
		}
		case VECTOR_TYPE_FLOAT:
		{
			return sizeof(float);
		}
		case VECTOR_TYPE_DOUBLE:
		{
			return sizeof(double);
		}
		case VECTOR_TYPE_LONG_INT:
		{
			return sizeof(long int);
		}
		case VECTOR_TYPE_LONG_LONG:
		{
			return sizeof(long long);
		}
		case VECTOR_TYPE_LONG_DOUBLE:
		{
			return sizeof(long double);
		}
		case VECTOR_TYPE_BOOL:
		{
			return sizeof(bool);
		}
		case VECTOR_TYPE_POINTER:
		{
			return sizeof(void *);
		}
		default: return 0; // Unknown type
	}
}


vector *vector_create(vector_type_id type, size_t size)
{
	if (!VECTOR_TYPE_VALID_CHECK(type))
	{
		return NULL;
	}
	if (!size)
	{
		return NULL;
	}
	vector *v = (vector *) calloc(1, sizeof(vector));
	vector_private *v_priv = (vector_private *) calloc(1, sizeof(vector_private));
	void *ptr = calloc(size, vector_sizeof_type(type));
	if (!v || !v_priv)
	{
		CONDITIONAL_FREE(v);
		CONDITIONAL_FREE(v_priv);
		CONDITIONAL_FREE(ptr);
		return NULL;
	}
	// Init internal data
	v_priv->v_id = type;
	v_priv->v_type_size = vector_sizeof_type(type);
	v_priv->v_size = 0;
	v_priv->v_cap = size;
	v_priv->v_ptr = ptr;
	v->v_priv = v_priv;
	// Init function pointers
	v->at = vector_at;
	v->set = vector_set;
	v->front = vector_front;
	v->back = vector_back;
	v->data = vector_data;
	v->empty = vector_empty;
	v->size = vector_size;
	v->max_size = vector_max_size;
	v->reserve = vector_reserve;
	v->capacity = vector_capacity;
	v->clear = vector_clear;
	v->insert = vector_insert;
	v->remove = vector_remove;
	v->push_back = vector_push_back;
	v->pop_back = vector_pop_back;
	v->resize = vector_resize;
	v->destroy = vector_destroy;
	return v;
}

static int vector_at(vector *v, size_t pos, ...)
{
	VECTOR_CHECK_RETURN_VALUE(v, -1);
	size_t size = v->v_priv->v_size;
	if (vector_empty(v)) {
		return -1;
	}
	if (pos >= size) {
		return -1;
	}
	va_list list;
	va_start (list, pos);
	return vector_get_value(v, pos, list);
}

static int vector_set(vector *v, size_t pos, ...)
{
        VECTOR_CHECK_RETURN_VALUE(v, -1);
        size_t size = v->v_priv->v_size;
        if (vector_empty(v)) {
                return -1;
        }
        if (pos >= size) {
                return -1;
        }
        va_list list;
        va_start (list, pos);
        return vector_set_value(v, pos, list);
}

static int vector_front(vector *v, ...)
{
	VECTOR_CHECK_RETURN_VALUE(v, -1);
	if (vector_empty(v)) {
		return  -1;
	}
	va_list list;
	va_start(list, v);
	// Get the first value of the vector
	return vector_get_value(v, 0, list);
}

static int vector_back(vector *v, ...)
{
	VECTOR_CHECK_RETURN_VALUE(v, -1);
	if (vector_empty(v)) {
		return -1;
	}
	size_t last_index = v->v_priv->v_size - 1;
	va_list list;
	va_start(list, v);
	return vector_get_value(v, last_index, list);
}

static void *vector_data(vector *v)
{
	VECTOR_CHECK_RETURN_VALUE(v, NULL);
	return v->v_priv->v_ptr;
}

static bool vector_empty(vector *v)
{
	// A invalid vector pointer is taken as a empty vector pointer
	VECTOR_CHECK_RETURN_VALUE(v, true);
	return v->v_priv->v_size ? false : true;
}

static size_t vector_size(vector *v)
{
	VECTOR_CHECK_RETURN_VALUE(v, 0);
	return v->v_priv->v_size;
}

static size_t vector_max_size(void)
{
	return ((size_t) (-1));
}

static void vector_reserve(vector *v, size_t new_cap)
{
	VECTOR_CHECK(v);
	size_t old_cap = v->v_priv->v_cap;
	if (new_cap <= old_cap)
	{
		return;
	}
	size_t type_size = v->v_priv->v_type_size;
	void *old_ptr = vector_data(v);
	void *new_ptr = realloc(old_ptr, new_cap * type_size);
	if (!new_ptr) {
	       return;
	}
	// Initial memory which are not being used
	void *new_ptr_end = CALC_PTR(new_ptr, v->v_priv->v_size, type_size);
	memset(new_ptr_end, 0x00, (new_cap - old_cap) * type_size);
	v->v_priv->v_ptr = new_ptr;
	v->v_priv->v_cap = new_cap;
}

static size_t vector_capacity(vector *v)
{
	VECTOR_CHECK_RETURN_VALUE(v, 0);
	return v->v_priv->v_cap;
}

static void vector_clear(vector *v)
{
	VECTOR_CHECK(v);
	if (vector_empty(v))
	{
		return;
	}
	void *stack_ptr = v->v_priv->v_ptr;
	size_t size = v->v_priv->v_size;
	size_t type_size = v->v_priv->v_type_size;
	memset(stack_ptr, 0x00, size * type_size);
	v->v_priv->v_size = 0;
}

static int vector_insert(vector *v, size_t pos, ...)
{
	VECTOR_CHECK_RETURN_VALUE(v, -1);
        size_t size = v->v_priv->v_size;
	size_t cap = v->v_priv->v_cap;
	void *stack_ptr = v->v_priv->v_ptr;
	size_t type_size = v->v_priv->v_type_size;
	va_list list;
	va_start(list, pos);
	if (cap < size + 1)
	{
		vector_memory_resize(v, cap + 1);
	}
	void *dest = CALC_PTR(stack_ptr, pos+1, type_size);
	void *src = CALC_PTR(stack_ptr, pos, type_size);
	memmove(dest, src, (size - pos) * type_size);
	vector_set_value(v, pos, list);
	v->v_priv->v_size += 1;
	return 0;
}

static int vector_remove(vector *v, size_t pos)
{
	VECTOR_CHECK_RETURN_VALUE(v, -1);
	if (vector_empty(v))
	{
		return -1;
	}
	void *stack_ptr = vector_data(v);
	size_t type_size = v->v_priv->v_type_size;
	size_t size = v->v_priv->v_size;
	if (pos >= size)
	{
		return -1;
	}
	if (pos == size-1)
	{
		memset(CALC_PTR(stack_ptr, size-1, type_size), 0x00, type_size);
		v->v_priv->v_size -= 1;
		return 0;
	}
	void *dest = CALC_PTR(stack_ptr, pos, type_size);
	void *src = CALC_PTR(stack_ptr, pos+1, type_size);
	memmove(dest, src, (size -1 - pos) * type_size);
	void *end_ptr = CALC_PTR(stack_ptr, size - 1, type_size);
	memset(end_ptr, 0x00, type_size);
	v->v_priv->v_size -= 1;
	return 0;
}

static int vector_push_back(vector *v, ...)
{
	VECTOR_CHECK_RETURN_VALUE(v, -1);
	va_list list;
	va_start(list, v);
	size_t cap = v->v_priv->v_cap;
	size_t size = v->v_priv->v_size;
	if (cap < size + 1)
	{
		vector_memory_resize(v, cap + 1);
	}
	v->v_priv->v_size += 1;
	vector_set_value(v, size, list);
	return 0;
}

static int vector_pop_back(vector *v)
{
	VECTOR_CHECK_RETURN_VALUE(v, -1);
	if (vector_empty(v))
	{
		return -1;

	}
	vector_remove(v, v->v_priv->v_size - 1);
	return 0;
}

static int vector_resize(vector *v, size_t count, ...)
{
	VECTOR_CHECK_RETURN_VALUE(v, -1);
	size_t size = v->v_priv->v_size;
	size_t cap = v->v_priv->v_cap;
	va_list list;
	va_start(list, count);
	if (count > cap)
	{
		vector_memory_resize(v, count);
	}
	if (count == 0)
	{
		vector_clear(v);
		va_end(list);
		return 0;
	}
	if (count > size)
	{
		for(size_t i=size+1;i<=count;i++)
		{
			vector_set_value(v, i-1, list);
		}
	}
	else
	{
		if (count == size)
		{
			va_end(list);
			return 0;
		}
		for (size_t i=count;i<size;i++)
		{
			vector_remove(v, i);
		}
	}
	va_end(list);
	return 0;
}

static void vector_destroy(vector *v)
{
	VECTOR_CHECK(v);
	CONDITIONAL_FREE(v->v_priv->v_ptr);
	CONDITIONAL_FREE(v->v_priv);
	CONDITIONAL_FREE(v);
}
