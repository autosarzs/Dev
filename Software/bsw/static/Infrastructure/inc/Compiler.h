/** See CopmpilerAbstraction.pdf **/
#ifndef COMPILER_H
#define COMPILER_H

#define AUTOMATIC
#define TYPEDEF typedef
#define STATIC 	static
#define NULL_PTR	((void *)0)

#define INLINE __inline__

#define FUNC(rettype,memclass) rettype

#define FUNC_P2VAR(rettype, ptrclass, memclass) rettype *(memclass)

#define FUNC_P2CONST(rettype, ptrclass, memclass)const rettype *(memclass)

#define P2VAR(ptrtype, memclass, ptrclass) ptrtype *

#define P2CONST(ptrtype, memclass, ptrclass) const ptrtype *

#define CONSTP2VAR(ptrtype,memclass,ptrclass) ptrtype * const

#define CONSTP2CONST(ptrtype, memclass, ptrclass) const ptrtype * const

#define P2FUNC(rettype,ptrclass,fctname) rettype (*fctname)

#ifndef CONST
#define CONST(consttype,memclass) const consttype
#endif

#define VAR(vartype,memclass) vartype


#endif /* COMPILER_H */
