#include <stdbool.h>
#include "Studtype.h"
#include <string.h>

bool cmp(Studtype a, Studtype b) {
    return strcmp(a.name.LName, b.name.LName) == 0 &&
        strcmp(a.name.FName, b.name.FName) == 0 &&
        a.name.Mi == b.name.Mi;
}