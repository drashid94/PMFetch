#define SUCCESS 0
#define EXIT_POINT EXIT_POINT:
#define EXIT_FUNCTION(ret, err) ret = err; \
                                goto EXIT_POINT

// struct for positions - x and y variables