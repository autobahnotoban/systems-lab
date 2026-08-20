Implementations of two different hashing methods for detecting hash collision:

### Chaining:

    --> chaining.c is my implementation.
    --> chaining_clean.c is llm output for comparison.
    
    to remember:
        --> use '\0' when iterating strings
        --> check for end of line when doing strncpy
        --> do not init a variable just to assign it next line
        --> do not forget to free
        --> check for scanf errors and use %xs for valid input processing, check for out of range errors(row)

### Open addressing: Linear probing,quadratic probing,double hashing