#ifndef S_ERROR_H
#define S_ERROR_H

#include "sobject_common.h"
#include <stdio.h>

#define FUNCTION_MAX 256

OBJECT_DECL(Error,
	int errno;
	char *string;
	int string_len;
	char file[FILENAME_MAX];
	char function[FUNCTION_MAX];
	int line;
)

#define SET_ERROR(object, var, message) \
	METHOD_CALL(object, setError, var, message, __FILE__, __LINE__, __func__)


//////////////// Prototypes ////////////////
STATIC_INLINE_METHOD_DECL(Error, clear, void);


//////////////// Error Methods ////////////////
STATIC_INLINE_METHOD_DECL(Error, ctor, void)
{
	this->string_len = 256;
	this->errno = 0;
	this->string = NEW_ARRAY(char, this->string_len);
	METHOD_CALL(Error, clear, this);
}

STATIC_INLINE_DTOR_DECL(Error)
{
	DELETE(this->string);
	DELETE(this);
}

STATIC_INLINE_METHOD_DECL(Error, isSet, int)
{
	return strlen_l(this->string);
}

STATIC_INLINE_METHOD_DECL(Error, set, void, const char *string,
	const char *file, const int line, const char *function)
{
	// Check bounds of string
	int len=0;
	if ((len = strlen_l(string)) > this->string_len){
		RESIZE(this->string, len+1);
		this->string_len = len+1;
	}

	// We've already checked the bounds above
	strcpy(this->string, string);

	// Make sure it's nul terminated
	(this->string)[this->string_len] = 0;

	strncpy(this->file, file, FILENAME_MAX);
	(this->file)[FILENAME_MAX-1] = 0;

	this->line = line;

	strncpy(this->function, function, FUNCTION_MAX);
	(this->function)[FUNCTION_MAX-1] = 0;
}

STATIC_INLINE_METHOD_DECL(Error, clear, void)
{
	if (this->string != (void*)0){
		this->string[0] = 0;
	}
	this->file[0]     = 0;
	this->line        = 0;
	this->errno			= 0;
	this->function[0] = 0;
}

#endif

