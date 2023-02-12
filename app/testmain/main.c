#include "stdio.h"
#include "assert.h"

#include "ezc.h"

int main() {
    const char* file = "/home/brandon/projects/ezc/test.csv";
    csv_t* csv = csv_new(file);
    csv_element_t elem = csv_element(csv, 3, 12);
    csv_print(&elem);
    csv_del(csv);
    return 0;
}