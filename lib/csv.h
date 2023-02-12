#ifndef CSV_H
#define CSV_H

#include <stddef.h>
#include <stdbool.h>

typedef struct csv csv_t;
typedef struct csv_iter csv_iter_t;
typedef struct {
    size_t row;
    size_t col;
    const char* start;
    const char* end;
} csv_element_t;

typedef struct {
    bool (*filter_callback)(void* ctx, csv_element_t* elem);
    void* ctx;
} csv_filter_t;

csv_t* csv_new(const char* path);

void csv_del(csv_t* csv);

csv_iter_t* csv_iter_new(csv_t* csv);

void csv_iter_del(csv_iter_t* iter);

csv_element_t csv_next(csv_iter_t* iter, csv_filter_t* filter);

void csv_strcpy(csv_element_t* element, char* buf, size_t max_sz);

char* csv_strdup(csv_element_t* element);

void csv_print(csv_element_t* element);

csv_filter_t csv_row_filter(int* row);

csv_filter_t csv_col_filter(int* col);

struct csv_row_col{
    int row;
    int col;
};

csv_filter_t csv_row_col_filter(struct csv_row_col* row_col);

csv_element_t csv_element(csv_t* csv, int row, int col);

#endif // CSV_H