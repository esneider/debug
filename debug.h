/* The MIT License (MIT)
 *
 * Copyright (c) 2015 Dario Sneidermanis <dariosn@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#undef __eval_2
#undef __eval_1
#undef __eval_0
#undef __nargs_1
#undef __nargs_0
#undef __format
#undef __empty
#undef __loop
#undef __arg_1
#undef __arg_2
#undef __print_3
#undef __print_2
#undef __print_1
#undef __print_0
#undef debug
#undef idebug
#undef debugexpr
#undef idebugexpr

#ifdef NDEBUG

#define debug(...) ((void)0)
#define idebug(...) ((void)0)
#define debugexpr(expr) ((void)0)
#define idebugexpr(expr) ((void)0)

#else

#if !defined(_STDIO_H_) && !defined(_STDIO_H)
int printf(const char *restrict format, ...);
#endif

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
                         _Bool: "%d", \
               _Complex double: "%g + %gi", \
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

#define debug(...) (__print_0(__VA_ARGS__), printf("\n"))
#define idebug(...) (printf("%s:%d: ", __FILE__, __LINE__), debug(__VA_ARGS__))

#define debugexpr(expr) debug(#expr " =", expr)
#define idebugexpr(expr) idebug(#expr " =", expr)

#endif /* NDEBUG */
