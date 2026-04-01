#include <stdint.h>

__attribute__((import_module("sys"), import_name("call"))) int __syscall(int, int, int, int, int, int);

static inline int32_t exit(int32_t code) {
	return __syscall(1, code, 0, 0, 0, 0);
}

static inline int32_t read(int32_t fd, void *dst, uint32_t sz) {
	return __syscall(2, fd, (intptr_t)dst, sz, 0, 0);
}

static inline int32_t write(int32_t fd, const void *src, uint32_t sz) {
	return __syscall(3, fd, (intptr_t)src, sz, 0, 0);
}

static inline int32_t open(const char *path, uint32_t flags) {
	return __syscall(4, (intptr_t)path, flags, 0, 0, 0);
}

static inline int32_t close(int fd) {
	return __syscall(5, fd, 0, 0, 0, 0);
}

int main(void) {
	write(1, "Hello world!\n", 13);

	return 0;
}
