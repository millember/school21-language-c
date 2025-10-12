#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "master_levels.h"
#include "master_modules.h"
#include "master_status_events.h"
#include "index.h"

#define PATH_TO_MASTER_MODULES "../materials/master_modules.db"
#define PATH_TO_MASTER_LEVELS "../materials/master_levels.db"
#define PATH_TO_MASTER_STATUS_EVENTS "../materials/master_status_events.db"

#define PATH_TO_MODULES_INDEX "../materials/master_modules.index"
#define PATH_TO_LEVELS_INDEX "../materials/master_levels.index"
#define PATH_TO_EVENTS_INDEX "../materials/master_status_events.index"

int select(int name, int count) {
    int flag = 0;
    if (name == 1) {
        Module* modules;
        int count_modules = 0;
        selectMasterModules(PATH_TO_MASTER_MODULES, &modules, &count_modules);
        printf("id\tname\t\t\tlevel\tcell\tdeleted\n");
        for (int i = 0; i < count_modules && i < count; i++) {
            printf("%d\t%s\t\t%d\t\t%d\t\t%d\n", modules[i].id, modules[i].name, modules[i].level,
                   modules[i].cell, modules[i].deleted);
        }
        flag = 1;
        free(modules);
    } else if (name == 2) {
        Level* levels;
        int count_levels = 0;
        selectMasterLevels(PATH_TO_MASTER_LEVELS, &levels, &count_levels);
        printf("level\tcells\tprotected\n");
        for (int i = 0; i < count_levels && i < count; i++) {
            printf("%d\t%d\t\t%d\n", levels[i].level, levels[i].cells, levels[i].protected);
        }
        flag = 1;
        free(levels);
    } else if (name == 3) {
        StatusEvent* events;
        int count_events = 0;
        selectMasterStatusEvents(PATH_TO_MASTER_STATUS_EVENTS, &events, &count_events);
        printf("eventId\t\tmoduleId\tStatus\t\tdate\t\ttime\n");
        for (int i = 0; i < count_events && i < count; i++) {
            printf("%d\t\t%d\t\t%d\t\t%s\t%s\n", events[i].eventId, events[i].moduleId, events[i].newStatus,
                   events[i].date, events[i].time);
        }
        flag = 1;
        free(events);
    }
    return flag;
}

int insert(int name) {
    if (name == 1) {
        Module* modules = malloc(sizeof(Module));
        Module* modules_all;
        printf("Write:\nid name level cell deleted\n");
        scanf("%d %s %d %d %d", &modules->id, modules->name, &modules->level, &modules->cell,
              &modules->deleted);
        int count_modules = 0;
        selectMasterModules(PATH_TO_MASTER_MODULES, &modules_all, &count_modules);
        for (int i = 0; i < count_modules; i++) {
            if (modules_all[i].id == modules->id) {
                printf("Module with this id already exists\n");
                free(modules);
                free(modules_all);
                return 0;
            }
        }
        insertMasterModules(PATH_TO_MASTER_MODULES, modules);
        free(modules);
        free(modules_all);
    } else if (name == 2) {
        Level* level = malloc(sizeof(Level));
        Level* levels_all;
        printf("Write:\nlevel cells protected\n");
        scanf("%d %d %d", &level->level, &level->cells, &level->protected);
        int count_levels = 0;
        selectMasterLevels(PATH_TO_MASTER_LEVELS, &levels_all, &count_levels);
        for (int i = 0; i < count_levels; i++) {
            if (levels_all[i].level == level->level) {
                printf("Level with this number already exists\n");
                free(level);
                free(levels_all);
                return 0;
            }
        }
        insertMasterLevels(PATH_TO_MASTER_LEVELS, level);
        free(level);
        free(levels_all);
    } else if (name == 3) {
        StatusEvent* event = malloc(sizeof(StatusEvent));
        StatusEvent* events_all;
        printf("Write:\neventId moduleId newStatus date(00.00.0000) time(00:00:00)\n");
        scanf("%d %d %d %s %s", &event->eventId, &event->moduleId, &event->newStatus, event->date,
              event->time);
        int count_events = 0;
        selectMasterStatusEvents(PATH_TO_MASTER_STATUS_EVENTS, &events_all, &count_events);
        for (int i = 0; i < count_events; i++) {
            if (events_all[i].eventId == event->eventId) {
                printf("Event with this id already exists\n");
                free(event);
                free(events_all);
                return 0;
            }
        }
        insertMasterStatusEvents(PATH_TO_MASTER_STATUS_EVENTS, event);
        free(event);
        free(events_all);
    } else {
        return 2;
    }
    return 1;
}

int update(int name) {
    int dooper = 0;
    if (name == 1) {
        dooper = 0;
        updateMasterModules(PATH_TO_MASTER_MODULES, &dooper);
    } else if (name == 2) {
        dooper = 0;
        updateMasterLevels(PATH_TO_MASTER_LEVELS, &dooper);
    } else if (name == 3) {
        dooper = 0;
        updateMasterStatusEvents(PATH_TO_MASTER_STATUS_EVENTS, &dooper);
    } else {
        dooper = 2;
    }
    return dooper;
}

int delete (int name) {
    int dooper = 0;
    if (name == 1) {
        deleteMasterModules(PATH_TO_MASTER_MODULES, &dooper);
    } else if (name == 2) {
        deleteMasterLevels(PATH_TO_MASTER_LEVELS, &dooper);
    } else if (name == 3) {
        deleteMasterStatusEvents(PATH_TO_MASTER_STATUS_EVENTS, &dooper);
    } else {
        dooper = 2;
    }
    return dooper;
}

void module_status_1() {
    StatusEvent* events;
    int count_events = 0;
    selectMasterStatusEvents(PATH_TO_MASTER_STATUS_EVENTS, &events, &count_events);
    printf("eventId\t\tmoduleId\tStatus\t\tdate\t\ttime\n");
    for (int i = 0; i < count_events; i++) {
        if (events[i].newStatus == 1) {
            printf("%d\t\t%d\t\t%d\t\t%s\t%s\n", events[i].eventId, events[i].moduleId, events[i].newStatus,
                   events[i].date, events[i].time);
        }
    }
    free(events);
}

void delete_modul_by_id(int id) {
    Module* modules_new = malloc(sizeof(Module));
    Module* modules;
    int count_modules = 0;
    selectMasterModules(PATH_TO_MASTER_MODULES, &modules, &count_modules);
    int not = 0;
    for (int i = 0; i < count_modules; i++) {
        if (modules[i].id == id) {
            modules_new->id = modules[i].id;
            strcpy(modules_new->name, modules[i].name);
            modules_new->level = modules[i].level;
            modules_new->cell = modules[i].cell;
            modules_new->deleted = 1;
            not = 1;
        }
    }
    if (not == 1) {
        updateMasterModules_by_id(PATH_TO_MASTER_MODULES, modules_new, id);
    }else{
        printf("There is no module with this id\n");
    }
    free(modules);
    free(modules_new);
}

void protect_level_by_id(int id) {
    Level* levels_new = malloc(sizeof(Level));
    Level* levels;
    int count_levels = 0;
    int not = 0;
    selectMasterLevels(PATH_TO_MASTER_LEVELS, &levels, &count_levels);
    for (int i = 0; i < count_levels; i++) {
        if (levels[i].level == id) {
            levels_new->level = levels[i].level;
            levels_new->cells = levels[i].cells;
            levels_new->protected = 1;
            not = 1;
        }
    }
    if (not == 1) {
        protectMasterLevels_by_id(PATH_TO_MASTER_LEVELS, levels_new, id);
    }else{
        printf("There is no level with this level\n");
    }
    
    free(levels);
    free(levels_new);
}

void move_to_new_memory(int id) {
    Module* modules_new = malloc(sizeof(Module));
    Module* modules;
    int count_modules = 0;
    selectMasterModules(PATH_TO_MASTER_MODULES, &modules, &count_modules);
    int not = 0;
    for (int i = 0; i < count_modules; i++) {
        if (modules[i].id == id) {
            modules_new->id = modules[i].id;
            strcpy(modules_new->name, modules[i].name);
            modules_new->level = modules[i].level;
            modules_new->cell = modules[i].cell;
            modules_new->deleted = modules[i].deleted;
            not = 1;
        }
    }
    if (not == 1) {
        printf("New level and cell:\n");
        scanf("%d %d", &modules_new->level, &modules_new->cell);
        updateMasterModules_by_id(PATH_TO_MASTER_MODULES, modules_new, id);
    }else{
        printf("There is no module with this id\n");
    }
    free(modules);
    free(modules_new);
}

void get_first_level_modules() {
    Module* modules;
    int count_modules = 0;
    selectMasterModules(PATH_TO_MASTER_MODULES, &modules, &count_modules);
    printf("Modules on first level:\n");
    printf("ID\tName\t\t\tLevel\tCell\tDeleted\n");
    for (int i = 0; i < count_modules; i++) {
        if (modules[i].level == 1 && modules[i].deleted == 0) {
            printf("%d\t%s\t\t%d\t%d\t%d\n", 
                   modules[i].id, modules[i].name, modules[i].level,
                   modules[i].cell, modules[i].deleted);
        }
    }
    free(modules);
}

void disable_ai_system() {
    printf("=== Starting AI Disable Procedure ===\n");
    
    printf("1. Disabling additional modules...\n");
    Module* modules;
    int module_count = 0;
    selectMasterModules(PATH_TO_MASTER_MODULES, &modules, &module_count);
    
    for (int i = 0; i < module_count; i++) {
        if (modules[i].id != 0 && modules[i].deleted == 0) {
            StatusEvent event;
            event.eventId = 9999 + i;
            event.moduleId = modules[i].id;
            event.newStatus = 0;
            strcpy(event.date, "01.01.2024");
            strcpy(event.time, "00:00:00");
            
            insertMasterStatusEvents(PATH_TO_MASTER_STATUS_EVENTS, &event);
        }
    }
    
    printf("2. Deleting additional modules...\n");
    for (int i = 0; i < module_count; i++) {
        if (modules[i].id != 0 && modules[i].deleted == 0) {
            Module deleted_module = modules[i];
            deleted_module.deleted = 1;
            updateMasterModules_by_id(PATH_TO_MASTER_MODULES, &deleted_module, modules[i].id);
        }
    }
    
    printf("3. Securing main module...\n");
    int status_sequence[] = {0, 1, 20};
    for (int i = 0; i < 3; i++) {
        StatusEvent event;
        event.eventId = 10000 + i;
        event.moduleId = 0;
        event.newStatus = status_sequence[i];
        strcpy(event.date, "01.01.2024");
        strcpy(event.time, "00:00:00");
        
        insertMasterStatusEvents(PATH_TO_MASTER_STATUS_EVENTS, &event);
    }
    
    printf("4. Moving main module to first level...\n");
    Module main_module;
    main_module.id = 0;
    strcpy(main_module.name, "Main module");
    main_module.level = 1;
    main_module.cell = 1;
    main_module.deleted = 0;
    
    updateMasterModules_by_id(PATH_TO_MASTER_MODULES, &main_module, 0);
    
    printf("5. Protecting first level...\n");
    Level protected_level;
    protected_level.level = 1;
    protected_level.cells = 4;
    protected_level.protected = 1;
    protectMasterLevels_by_id(PATH_TO_MASTER_LEVELS, &protected_level, 1);
    
    printf("6. Verification...\n");
    
    Module* final_modules;
    int final_count = 0;
    selectMasterModules(PATH_TO_MASTER_MODULES, &final_modules, &final_count);
    
    Module* main_module_final = NULL;
    int other_modules_on_first_level = 0;
    
    for (int i = 0; i < final_count; i++) {
        if (final_modules[i].id == 0 && final_modules[i].level == 1 && final_modules[i].cell == 1) {
            main_module_final = &final_modules[i];
        } else if (final_modules[i].level == 1 && final_modules[i].deleted == 0) {
            other_modules_on_first_level++;
        }
    }
    
    if (main_module_final && other_modules_on_first_level == 0) {
        printf("SUCCESS: Only main AI module in first level, first cell!\n");
    } else {
        printf("ERROR: Main module not properly isolated!\n");
        printf("Other modules on first level: %d\n", other_modules_on_first_level);
    }
    
    free(modules);
    free(final_modules);
    printf("=== AI Disable Procedure Complete ===\n");
}

void create_all_indexes() {
    printf("Creating indexes...\n");
    create_index(PATH_TO_MASTER_MODULES, PATH_TO_MODULES_INDEX, sizeof(Module));
    create_index(PATH_TO_MASTER_LEVELS, PATH_TO_LEVELS_INDEX, sizeof(Level));
    create_index(PATH_TO_MASTER_STATUS_EVENTS, PATH_TO_EVENTS_INDEX, sizeof(StatusEvent));
    printf("Indexes created successfully!\n");
}

void* select_module_with_index(int id) {
    return select_with_index(PATH_TO_MASTER_MODULES, PATH_TO_MODULES_INDEX, id, sizeof(Module));
}

void* select_level_with_index(int level) {
    return select_with_index(PATH_TO_MASTER_LEVELS, PATH_TO_LEVELS_INDEX, level, sizeof(Level));
}

void* select_event_with_index(int event_id) {
    return select_with_index(PATH_TO_MASTER_STATUS_EVENTS, PATH_TO_EVENTS_INDEX, event_id, sizeof(StatusEvent));
}

int select_fast(int table_type, int record_count) {
    int success = 0;
    
    if (table_type == 1) {
        Module* modules;
        int module_count = 0;
        selectMasterModules(PATH_TO_MASTER_MODULES, &modules, &module_count);
        printf("ID\tName\t\t\tLevel\tCell\tDeleted\n");
        for (int i = 0; i < module_count && i < record_count; i++) {
            Module* fast_module = (Module*)select_module_with_index(modules[i].id);
            if (fast_module) {
                printf("%d\t%s\t\t%d\t%d\t%d [INDEX]\n", 
                       fast_module->id, fast_module->name, fast_module->level,
                       fast_module->cell, fast_module->deleted);
                free(fast_module);
            }
        }
        success = 1;
        free(modules);
    } else if (table_type == 2) {
        Level* levels;
        int level_count = 0;
        selectMasterLevels(PATH_TO_MASTER_LEVELS, &levels, &level_count);
        printf("Level\tCells\tProtected\n");
        for (int i = 0; i < level_count && i < record_count; i++) {
            Level* fast_level = (Level*)select_level_with_index(levels[i].level);
            if (fast_level) {
                printf("%d\t%d\t%d [INDEX]\n", 
                       fast_level->level, fast_level->cells, fast_level->protected);
                free(fast_level);
            }
        }
        success = 1;
        free(levels);
    }
    return success;
}