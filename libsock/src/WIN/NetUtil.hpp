#ifndef NET_UTIL_WIN_H
#define NET_UTIL_WIN_H

const char* inet_ntop(int af, const void* src, char* dst, int cnt);
int init_net();
int cleanup_net();

#endif