# fa21-proj1-starter

Please add a description about what you created! Also add lessons you learned or bugs you encountered. 

## Bugs

### realloc error

```
Fatal glibc error: malloc assertion failure in sysmalloc: (old_top == initial_top (av) && old_size == 0) || ((unsigned long) (old_size) >= MINSIZE && prev_inuse (old_top) && ((unsigned long) old_end & (pagesize - 1)) == 0)
make: *** [Makefile:166: test_long_word_input] Error 134
```

I enlarge the allocated memory by 2 times larger than the previous capacity.

When I set the original capacity to 60, it causes error in large input. But when I change it to 64, the error magically disappears.

I still can't figure out why.
