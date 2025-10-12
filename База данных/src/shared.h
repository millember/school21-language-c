#ifndef SHARED_H
#define SHARED_H

int select(int, int);
int insert(int);
int update(int);
int delete (int);
void module_status_1();
void delete_modul_by_id(int);
void protect_level_by_id(int);
void move_to_new_memory(int);
void disable_ai_system();
void get_first_level_modules();

void create_all_indexes();
void* select_module_with_index(int id);
void* select_level_with_index(int level);
void* select_event_with_index(int event_id);
int select_fast(int table_type, int record_count);

#endif