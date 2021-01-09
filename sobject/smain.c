#include "sobject_common.h"
#include "sobject.h"

int main(){
	Object *obj;
	const Error *error;

	OBJECT_CTOR(Object, obj);
	SET_ERROR(Object, obj, "Test");

	if ((error = METHOD_CALL(Object, getError, obj))){
		printf("Error string: %s\n", error->string);
		printf("Error errno: %d\n", error->errno);
		printf("Error file: %s\n", error->file);
		printf("Error function: %s\n", error->function);
		printf("Error line: %d\n", error->line);
	}

	OBJECT_DTOR(Object, obj);
}

