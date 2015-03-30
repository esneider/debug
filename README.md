# Debugging like a sir (in C)

![](http://oi59.tinypic.com/5yw50z.jpg)

```c
#include "debug.h"

int answer(void) {
    return 42;
}

int main(void) {

    int num = 1;
    char *str = "hello";

    debug(num);
    // => num = 1

    debug(num, str, answer());
    // => num = 1
    //    str = hello
    //    answer() = 42

    debug_raw("counting:", 1, -2, 3 + 0.4);
    // => counting: 1 -2 3.4

    debug_raw(str, "world!");
    // => hello world!

    idebug(num);
    // => example.c:26: num = 1

    idebug(num, str);
    // => example.c:29:
    //            num = 1
    //            str = hello

    idebug_raw("The answer is", answer());
    // => example.c:34: The answer is 42

    return 0;
}
```

## Usage

Just include `debug.h` in your file.

## Gotchas

* Requires C11 support (uses `_Generic`). Consider using the flag `-std=c11` when compiling.
* Literal chars have type `int`, so you have to cast them to `char` to print them as actual chars:

```c
debug_raw("Find the", (char)'X'); // => Find the X
```

## Tips

For quick debugging, include the header right where you need it:

```c
void function(void) {
    ...
    #include "debug.h"
    debug(var); // => var = XXX
    ...
}
```

To remove quickly all debugging output, define `NDEBUG` before the header inclusion:

```c
#define NDEBUG
#include "debug.h"
...
debug(var); // Doesn't print anything
...
```

