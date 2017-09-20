# uniform vs no-majority

## Short summarize

### Comparing 20 random values
- By using pre-generated random numbers instead of calling rand() on every iteration we almost double the performance. Why? Probably due to *cache locality*.

### Custom randomize algorithm
- The builtin rand() is slow. By using a faster, less 'secure' algorithm we get almost 10x performance. 

### Compare the first 20 elements 
- If the array is unordered we might as well just compare the first 20 elements (comment if this is wrong!). This gives double the performance of customized rand().
