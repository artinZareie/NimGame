#include "Utils.h"
#include <stdbool.h>

int max_int(int a, int b) { return a > b ? a : b; }
int min_int(int a, int b) { return a > b ? b : a; }
bool is_newline(char c) { return c == '\n' || c == '\r' || c == (char)13; }
