#ifndef BASE_MACROS_H_
#define BASE_MACROS_H_

// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class
//
// For disallowing only assign or copy, write the code directly, but declare
// the intend in a comment, for example:
// void operator=(const TypeName&);  // DISALLOW_ASSIGN
// Note, that most uses of DISALLOW_ASSIGN and DISALLOW_COPY are broken
// semantically, one should either use disallow both or neither. Try to
// avoid these in new code.
#ifndef DISALLOW_COPY_AND_ASSIGN
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&) = delete;      \
  void operator=(const TypeName&) = delete
#endif

// Macro that allows definition of a variable appended with the current line
// number in the source file. Typically for use by other macros to allow the
// user to declare multiple variables with the same "base" name inside the same
// lexical block.
#define VARNAME_LINENUM(varname) VARNAME_LINENUM_INTERNAL(varname ## _L, __LINE__)
#define VARNAME_LINENUM_INTERNAL(v, line) VARNAME_LINENUM_INTERNAL2(v, line)
#define VARNAME_LINENUM_INTERNAL2(v, line) v ## line

#endif  // BASE_MACROS_H_