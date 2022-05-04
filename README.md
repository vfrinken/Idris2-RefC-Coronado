# RefC-Coronado
A RefC backend for Idris2, based on the official RefC backend. This backend only creates shared or static libraries.

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

2. Install the RefC-Coronado library generator

`git clone .../refc-coronado`  (this repository)

Compilation
```bash
cd refc-coronado
make
```

## Result
Idris2 with the new backends is now at `./build/exec/idris2-coronado`. The new backends are called
 _refc-coronado-shared_ and  _refc-coronado-static_.

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
