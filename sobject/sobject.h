#ifndef S_OBJECT_H
#define S_OBJECT_H

#include "sobject_common.h"
#include "serror.h"
#include <stdio.h>

OBJECT_DECL(Object,
	Error *error;
	Error *_error;
)

//////////////// Object Prototypes ////////////////
STATIC_INLINE_METHOD_DECL(Object, setError, void, const char *string,
   const char *file, const int line, const char *function);
STATIC_INLINE_METHOD_DECL(Object, getError, const Error*);

//////////////// Object Methods ////////////////
STATIC_INLINE_METHOD_DECL(Object, ctor, void)
{
	this->error = NEW(Error);
	this->_error = NEW(Error);

	METHOD_CALL(Error, ctor, this->error);
	METHOD_CALL(Error, ctor, this->_error);
}

STATIC_INLINE_DTOR_DECL(Object)
{
	OBJECT_DTOR(Error, this->error);
	OBJECT_DTOR(Error, this->_error);
	DELETE(this);
}

STATIC_INLINE_METHOD_DECL(Object, setError, void, const char *string, 
	const char *file, const int line, const char *function)
{
	METHOD_CALL(Error, set, this->_error, string, file, line, function);
}

STATIC_INLINE_METHOD_DECL(Object, getError, const Error *)
{
	if (METHOD_CALL(Error, isSet, this->_error)){
		METHOD_CALL(Error, set, this->error, this->_error->string, this->_error->file,
			this->_error->line, this->_error->function);
		METHOD_CALL(Error, clear, this->_error);

		return (const Error*)this->error;
	}

	return (const Error*)0;
}

#endif

