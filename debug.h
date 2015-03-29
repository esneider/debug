#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <stdio.h>

#define __eval_2(...) __VA_ARGS__
#define __eval_1(...) __eval_2(__eval_2(__eval_2(__eval_2(__VA_ARGS__))))
#define __eval_0(...) __eval_1(__eval_1(__eval_1(__eval_1(__VA_ARGS__))))

#define __nargs_1(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, ...) q
#define __nargs_0(...) __nargs_1(__VA_ARGS__, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0)

#define __format(arg) \
    _Generic(((void)0, (arg)), \
                          char: "%c", \
                   signed char: "%hhd", \
                 unsigned char: "%hhu", \
                  signed short: "%hd", \
                unsigned short: "%hu", \
                    signed int: "%d", \
                  unsigned int: "%u", \
                      long int: "%ld", \
             unsigned long int: "%lu", \
                 long long int: "%lld", \
        unsigned long long int: "%llu", \
                         float: "%g", \
                        double: "%g", \
                   long double: "%Lg", \
                        char *: "%s", \
                        void *: "%p", \
                       default: "<unknown>" \
    )

#define __empty()
#define __loop() printf(" "), __print_1

#define __arg_1(arg) printf(__format(arg), arg)
#define __arg_2(arg, ...) __arg_1(arg), __loop __empty() () (__VA_ARGS__)

#define __print_3(num, ...) __arg_ ## num (__VA_ARGS__)
#define __print_2(num, ...) __print_3(num, __VA_ARGS__)
#define __print_1(...) __print_2(__nargs_0(__VA_ARGS__), __VA_ARGS__)
#define __print_0(...) __eval_0(__print_1(__VA_ARGS__))

#define debug(...) (__print_0(__VA_ARGS__, "\n"))
#define idebug(...) (printf("%s:%d: ", __FILE__, __LINE__), debug(__VA_ARGS__))

#define debugexpr(expr) debug(#expr " =", expr)
#define idebugexpr(expr) idebug(#expr " =", expr)

#endif /* __DEBUG_H__ */
