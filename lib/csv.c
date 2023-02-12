#include "csv.h"

#include "ezfile.h"
#include "vec.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct csv {
    char* csv_data;
};

struct csv_iter {
    csv_t* csv;
    size_t i;
    size_t row;
    size_t col;
};

static bool found_stop_char(char c)
{
    return c == '\0' || c == ',' || c == '\r' || c == '\n';
}

csv_t* csv_new(const char* path)
{
    struct csv* csv = malloc(sizeof *csv);
    assert(csv);

    *csv = (struct csv) {
        .csv_data = ezfile_read(path)
    };
    return csv;
}

void csv_del(csv_t* csv)
{
    if (csv) {
        vec_del(csv->csv_data);
        free(csv);
    }
}

csv_iter_t* csv_iter_new(csv_t* csv)
{
    struct csv_iter *iter = malloc(sizeof *iter);
    assert(iter);

    *iter = (struct csv_iter) {
        .csv = csv
    };
    return iter;
}

void csv_iter_del(csv_iter_t* iter)
{
    if(iter) free(iter);
}

static csv_element_t csv_next_internal(csv_iter_t* iter)
{
    if (iter->csv->csv_data[iter->i] == '\0'){
        return (csv_element_t){
          .start = NULL,
          .end = NULL,
          .row = 0,
          .col = 0
        };
    }

    const char* start = &iter->csv->csv_data[iter->i];
    while (!found_stop_char(iter->csv->csv_data[iter->i])){
        iter->i++;
    }

    const char* end = &iter->csv->csv_data[iter->i];

    csv_element_t elem = {
        .start = start,
        .end = end,
        .row = iter->row,
        .col = iter->col
    };

    char c = iter->csv->csv_data[iter->i];
    if (c == ','){
        iter->i++;
        iter->col++;
    } else if (c == '\r' || c == '\n') {
        iter->i++;
        iter->row++;
        iter->col = 0;
        if(iter->csv->csv_data[iter->i] == '\n')
            iter->i++;
    }
    return elem;
}

csv_element_t csv_next(csv_iter_t* iter, csv_filter_t* filter)
{
    csv_element_t elem;
    do {
        elem = csv_next_internal(iter);
    } while (elem.start != NULL && filter && !filter->filter_callback(filter->ctx, &elem));
    return elem;
}

void csv_strcpy(csv_element_t* element, char* buf, size_t max_sz)
{
    memset(buf, 0, max_sz);
    size_t actual_size = element->end-element->start;
    if(actual_size >= max_sz)
        actual_size = max_sz-1;
    strncpy(buf, element->start, actual_size);
}

char* csv_strdup(csv_element_t* element)
{
    size_t actual_size = element->end-element->start;
    char* str = malloc(actual_size+1);
    csv_strcpy(element, str, actual_size+1);
    return str;
}

void csv_print(csv_element_t* element)
{
    char* str = csv_strdup(element);
    printf("%lu %lu %s\n", element->row, element->col, str);
    free(str);
}

static bool row_filter_callback(void* ctx, csv_element_t* elem)
{
    int r = *((int*)ctx);
    return r == elem->row;
}

static bool col_filter_callback(void* ctx, csv_element_t* elem)
{
    int c = *((int*)ctx);
    return c == elem->col;
}

static bool row_col_filter_callback(void* ctx, csv_element_t* elem)
{
    struct csv_row_col c = *((struct csv_row_col*)ctx);
    return c.row == elem->row && c.col == elem->col;
}

csv_filter_t csv_row_filter(int* row)
{
    return (csv_filter_t){
        .filter_callback = row_filter_callback,
        .ctx = row
    };
}

csv_filter_t csv_col_filter(int* col)
{
    return (csv_filter_t){
        .filter_callback = col_filter_callback,
        .ctx = col
    };
}

csv_filter_t csv_row_col_filter(struct csv_row_col* row_col)
{
    return (csv_filter_t){
        .filter_callback = row_col_filter_callback,
        .ctx = row_col
    };
}

csv_element_t csv_element(csv_t* csv, int row, int col)
{
    csv_iter_t* iter = csv_iter_new(csv);
    struct csv_row_col row_col = {.row=row, .col=col};
    csv_filter_t filter = csv_row_col_filter(&row_col);
    csv_element_t elem = csv_next(iter, &filter);
    csv_iter_del(iter);
    return elem;
}