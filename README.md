## fatlang

a minimalist programming language written in C++. not for real world applications — just a demonstration of building a language from scratch.

## project structure

- `src/` — entry point (main.cpp)
- `lib/src/` — lexer, parser, interpreter, AST
- `lib/test/` — tests
- `example_programs/` — .fatlang examples

## build

```
cmake -B build
cmake --build build
```

requires CMake 3.21+ and a C++20 compiler.

## run

```
./build/fatlang example_programs/main.fatlang
```

## test

```
./build/lib/fatlang_test
```

## example

```
let a = 10;
let b = 20;
if (a == 10) print(a + b);

let op = "+";
if (op == "+") print(100);
```
