# Idris2-RefC-Coronado
A RefC backend for Idris2, based on the official RefC backend. This backend can create an executable, a shared or a static library. This is still work in progress


## Changes over the Idris2 RefC Backend
1. There is no structural difference between a pointer and a garbage collected pointer. Each struct Value_Pointer has a pointer to a freeing function (closure) which is initialized to NULL. Upon registering the pointer with the GC, the freeing function is set. This prevents certain segmentation faults, but makes it impossible to have several freeing functions associated with a pointer.
2. Fixes to issue [2455](https://github.com/idris-lang/Idris2/issues/2455) of the Idris2 repo. The way this is done is my introducing 2 functions,
`Value_String *makeString(char *s);` and `Value_String *useString(char *s);`. The former makes a copy of the input string to create a new string object (needed for calls such as `Value* var = (Value*)makeString(":");` whereas the latter one frees the input strings, which is used to deal with return values of FFI calls. Furthermore, all char* returning FFI calls now create a copy.
3. Since this backend was tested by using the Idris2 code itself, placeholder Scheme evaluation functions are added in `support/refc/scheme_support.c`. 
4. Packing and unpacking of CFTypes `CFForeignObj` and `CFInteger` are added.

## Known Issues
1. The way how to deal with `CFInteger` is probably wrong. Currently and those are mapped to `Value_Int64` structs.
2. There is still a memory leak originating in the `idris2_currentDirectory` function. It returns a pointer (Ptr String), not a char*/String, thus the pointer is untouched and given to `prim__getString`, which creates a copy. Same with `idris2_readLine`.

## Installation
1. Install Idris2 from git
`git clone https://github.com/idris-lang/Idris2.git`

Follow the installation instructions given in the README.md. For most cases, build and make Idris with
```
make bootstrap SCHEME=chez
make install
```

For Mac M1, the following set of instructions has been reported as successful
```
export IDRIS2_CG=racket
make bootstrap-racket
make install
```

Afterwards, install api, (copies all compiled Idris2 .ttc files to the installation directory)

`make install-api`

2. Install this repo

`git clone git@github.com:vfrinken/Idris2-RefC-Coronado.git`

Compilation is done with `make` which assumes `idris2` to exist 

## Result
Idris2 with the new backends is now at `./build/exec/idris2-coronado`. The new backends are called
 _refc-coronado_,  _refc-coronado-shared_, and _refc-coronado-static_.

## Tests
The shared library generation can be checked using the test in `tests/refc_shared001`, the static library in with
the test in  `tests/refc_static001`
```
cd tests/refc_shared001
sh run ../../build/exec/idris2-coronado
```
resp.
```
cd tests/refc_static001
sh run ../../build/exec/idris2-coronado
```

In both cases, the output should be
```
execFunction test
c = 128
d = 7
e = 135
```
The first one is the execution of a function in the IO monad, the second one a gmp-based addition.


## Writing code for libraries
1. Functions to be exported need a tag in the form of
`%export RefC:addTwoNumbers`
where `%export` indicates that the following function is to be marked for export using the name `addTwoNumbers`.

2. main function
Currently, Idris requires a main function, even though this is a library. The main function need to reference all functions
to be exported, otherwise they would be pruned away in the compilation step. An easy way to do this is to create an array
of functions and print the length. The main function will not be compiled into any C code, so the details of the
`main : IO ()` function do not matter as long as the references to the functions are not erased, hence a putStrLn side effect.

```Idris
data ExportedFunction : Type where
    MkExportedFunction : {t:Type} -> (fct:t) -> ExportedFunction


main : IO ()
main = do
    let a = [ MkExportedFunction execFunction
            , MkExportedFunction addTwoNumbers]
    putStrLn $ show $ length a

```

## Usage
Very similar to how it was with Idris1:

- There are `void init_Idris2VM()` and `void cleanup_idris2VM()` functions, but they are only needed to set up and clean up the global *IORef storage*.
In particular init only sets a global pointer that might be uninitialized to NULL.

- Exported functions take and return `(Value *)` pointer. This is accompanied by make and extract functions, such as
`Value *makeNat(uint64_t n)`
or
`uint64_t extractNat(Value* v)`
together with a way for the user to identify the type of the value
```C
enum ValueType {Bits8, Bits16, Bits32, Bits64, Int8, Int16, Int32, Int64, Integer, Double, Char, String, Closure, Pointer, IdrisInternal};
enum ValueType getTypeOfValue(Value *);
```
