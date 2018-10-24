#include <stdio.h>
#include <vector/vector.h>

int main(void)
{
	vector *v = vector_create(VECTOR_TYPE_INT, 10);
	if (!v)
	{
		printf("Failed to create a vector\n");
		return -1;
	}
#ifdef _WIN64
	printf("The capacity of the vector is %I64u\n", v->capacity(v));
#else
	printf("The capacity of the vector is %I32u\n", v->capacity(v));
#endif
	int y = 10;
	v->push_back(v, y);
	int a = 0;
	v->at(v, 0, &a);
	printf("The value in 0 pos is %d\n", a);
	v->pop_back(v);
	v->destroy(v);
	return 0;
}
