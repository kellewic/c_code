#ifndef S_OBJECT_COMMON_H
#define S_OBJECT_COMMON_H

#include <stdlib.h>
#include <string.h>

#define strlen_l(s) \
   (((void*)s == (void*)0 || s[0] == '\0') ? (size_t)0 : strlen(s))

//////////////// Object Macros ////////////////

#define OBJECT_DECL(object, ...) \
   typedef struct object ## _st { __VA_ARGS__ } object;

#define METHOD_DECL(object, function, returnType, ...) \
   returnType object ##_## function(struct object ##_st *const this, ## __VA_ARGS__)

#define INLINE_METHOD_DECL(object, function, returnType, ...) \
	inline METHOD_DECL(object, function, returnType, ## __VA_ARGS__)

#define STATIC_INLINE_METHOD_DECL(object, function, returnType, ...) \
	static INLINE_METHOD_DECL(object, function, returnType, ## __VA_ARGS__)

#define DTOR_DECL(object) void object ##_dtor(struct object ##_st *this)
#define INLINE_DTOR_DECL(object) inline DTOR_DECL(object)
#define STATIC_INLINE_DTOR_DECL(object) static INLINE_DTOR_DECL(object)

#define NEW(object) calloc(1, sizeof(object))
#define NEW_ARRAY(object, num) calloc(num, sizeof(object))

#define OBJECT_CTOR(object, var) var = NEW(object); object ##_ctor(var)

#define OBJECT_DTOR(object, var) object ##_dtor(var)
#define DELETE(var) {if(var!=(void*)0){free(var); var=(void*)0;}}

#define RESIZE(var, size) var = realloc(var, size)

#define METHOD_CALL(object, method, ...) \
   object ##_## method(__VA_ARGS__)

#define CAST(var, object)	(object*)var

#endif
