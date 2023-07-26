
#include <time.h>
// Function to get the current time in seconds
double get_current_time()
{
    return (double)clock() / CLOCKS_PER_SEC;
}