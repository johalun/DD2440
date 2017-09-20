# Uniform vs No-Majority

## Short Summarize

### Comparing 20 random values
- By using pre-generated random numbers instead of calling rand() on every iteration we almost double the performance. Why? Probably due to *cache locality*.

### Custom randomize algorithm
- The builtin rand() is slow. By using a faster, less 'secure' algorithm we get almost 10x performance. 

### Compare the first 20 elements 
- If the array is unordered we might as well just compare the first 20 elements (comment if this is wrong!). This gives double the performance of customized rand().

## Typical Output

```shell
johannes@jd:~/kth/dd2440/uniform-vs-no-majority % make run
> lecture (all) example took 1033817 ns
> lecture (rand) example took 1341 ns
> pre-generated random numbers example took 782 ns
> optimized rand example took 133 ns
> first 20 example took 65 ns
Result was 1 (print so that it is not optimized away)
```
