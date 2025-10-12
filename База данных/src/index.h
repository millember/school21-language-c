#ifndef INDEX_H
#define INDEX_H

typedef struct {
    int id;
    long offset;
} IndexEntry;

void create_index(const char* data_file, const char* index_file, size_t record_size);
void* select_with_index(const char* data_file, const char* index_file, int id, size_t record_size);
int binary_search_index(FILE* index_file, int id, long* result_offset);

#endif