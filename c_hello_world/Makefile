all: hello.wasm

hello.wasm: hello.c
	clang -O2 -c hello.c -o hello.wasm.o --target=wasm32 -nostdlib
	wasm-ld --no-entry --export-all hello.wasm.o -o hello.wasm
