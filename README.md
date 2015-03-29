![](http://oi61.tinypic.com/34illzt.jpg)

```c
#include "debug.h"

int answer(void) {
    return 42;
}

int main(void) {

    int num = 1;
    char *str = "hello";

    debug(num);
    // => 1
    debug("counting:", -1, 1 + 1, 3.0);
    // => counting: -1 2 3.0
    debug(num, str, "world!");
    // => 1 hello world!
    debug("answer() =", answer());
    // => answer() = 42
    debugexpr(answer());
    // => answer() = 42
    idebug("answer() = ", answer());
    // => example.c:22: answer() = 42
    idebugexpr(num);
    // => example.c:24: num = 1

    return 0;
}
```

## Usage

Just include `debug.h` in your file.

## Gotchas

* Requires C11 support (uses `_Generic`), consider using the flag `-std=c11`
* The functions (`debug`, ...) are preprocessor macros, not real functions.
* Literal chars have type `int`, so you have to cast them to `char` to be printed as a characters:

```c
debug("Find the", (char)'X'); // => Find the X
```

## Tips

For quick debugging, include the header right where you need it:

```c
void function(void) {
    ...
    #include "debug.h"
    debugexpr(var); // => var = XXX
    ...
}
