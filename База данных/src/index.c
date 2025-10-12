#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "index.h"

void create_index(const char* data_file, const char* index_file, size_t record_size) {
    FILE* data_fp = fopen(data_file, "rb");
    FILE* index_fp = fopen(index_file, "wb");
    
    if (!data_fp || !index_fp) {
        if (data_fp) fclose(data_fp);
        if (index_fp) fclose(index_fp);
        return;
    }
    
    IndexEntry entry;
    long offset = 0;
    void* record = malloc(record_size);
    
    while (fread(record, record_size, 1, data_fp)) {
        int current_id = *((int*)record);
        entry.id = current_id;
        entry.offset = offset;
        fwrite(&entry, sizeof(IndexEntry), 1, index_fp);
        offset += record_size;
    }
    
    free(record);
    fclose(data_fp);
    fclose(index_fp);
}

int binary_search_index(FILE* index_file, int id, long* result_offset) {
    fseek(index_file, 0, SEEK_END);
    long file_size = ftell(index_file);
    int record_count = file_size / sizeof(IndexEntry);
    
    int left = 0;
    int right = record_count - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        fseek(index_file, mid * sizeof(IndexEntry), SEEK_SET);
        
        IndexEntry entry;
        fread(&entry, sizeof(IndexEntry), 1, index_file);
        
        if (entry.id == id) {
            *result_offset = entry.offset;
            return 1;
        } else if (entry.id < id) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return 0;
}

void* select_with_index(const char* data_file, const char* index_file, int id, size_t record_size) {
    FILE* index_fp = fopen(index_file, "rb");
    if (!index_fp) return NULL;
    
    long data_offset;
    int found = binary_search_index(index_fp, id, &data_offset);
    fclose(index_fp);
    
    if (!found) return NULL;
    
    FILE* data_fp = fopen(data_file, "rb");
    if (!data_fp) return NULL;
    
    void* record = malloc(record_size);
    fseek(data_fp, data_offset, SEEK_SET);
    
    if (fread(record, record_size, 1, data_fp)) {
        fclose(data_fp);
        return record;
    }
    
    fclose(data_fp);
    free(record);
    return NULL;
}