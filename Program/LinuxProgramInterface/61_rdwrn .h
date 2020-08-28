#ifndef RDWRN
#define RDWRN

ssize_t readn(int fd, void *buffer, size_t n);
ssize_t writen(int fd, const void *buffer, size_t n);

#endif
