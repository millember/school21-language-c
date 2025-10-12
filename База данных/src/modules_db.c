#include <stdio.h>
#include <stdlib.h>

#include "shared.h"

void show_menu();
void show_table_menu();
void handle_select();
void handle_insert();
void handle_update();
void handle_delete();

int main() {
    int operation = 0;
    int id = 0;
    while (operation != 14) {
        show_menu();
        scanf("%d", &operation);
        switch (operation) {
            case 1:
                handle_select();
                break;
            case 2:
                handle_insert();
                break;
            case 3:
                handle_update();
                break;
            case 4:
                handle_delete();
                break;
            case 5:
                module_status_1();
                break;
            case 6:
                id = 0;
                printf("Enter module ID:\n");
                scanf("%d", &id);
                delete_modul_by_id(id);
                break;
            case 7:
                id = 0;
                printf("Enter level number:\n");
                scanf("%d", &id);
                protect_level_by_id(id);
                break;
            case 8:
                id = 0;
                printf("Enter module ID:\n");
                scanf("%d", &id);
                move_to_new_memory(id);
                break;
            case 9:
                id = 0;
                printf("Enter level number:\n");
                scanf("%d", &id);
                protect_level_by_id(id);
                break;
            case 10:
                disable_ai_system();
                break;
            case 11:
                get_first_level_modules();
                break;
            case 12:
                create_all_indexes();
                break;
            case 13:
                printf("Enter table (1-Modules, 2-Levels): ");
                int table_type;
                scanf("%d", &table_type);
                printf("Enter record count: ");
                int count;
                scanf("%d", &count);
                select_fast(table_type, count);
                break;
            case 14:
                break;
            default:
                printf("Invalid operation\n");
                break;
        }
    }
    return 0;
}

void show_menu() {
    printf("Choose operation:\n");
    printf("1. SELECT\n2. INSERT\n3. UPDATE\n4. DELETE\n");
    printf("5. Get active modules (status 1)\n");
    printf("6. Delete module by ID\n");
    printf("7. Protect level by number\n");
    printf("8. Move module to new memory location\n");
    printf("9. Set protection flag for level\n");
    printf("10. DISABLE AI SYSTEM\n");
    printf("11. Get first level modules\n");
    printf("12. CREATE INDEXES\n");
    printf("13. FAST SELECT with indexes\n");
    printf("14. Exit\n");
}

void show_table_menu() { 
    printf("Choose table:\n1. Modules\n2. Levels\n3. Status events\n"); 
}

void handle_select() {
    int table_type = 0;
    int success = 1;
    show_table_menu();
    scanf("%d", &table_type);
    int record_count = 0;
    printf("Enter number of records or leave empty for all:\n");
    getchar();
    char c = getchar();
    while (c != '\n') {
        record_count = record_count * 10 + c - '0';
        c = getchar();
    }
    if (record_count == 0) {
        record_count = 500;
    }
    success = select(table_type, record_count);
    if (success == 0) {
        printf("Table not found\n");
    }
}

void handle_insert() {
    int table_type = 0;
    int success = 1;
    show_table_menu();
    scanf("%d", &table_type);
    success = insert(table_type);
    if (success == 2) {
        printf("Table not found\n");
    }
}

void handle_update() {
    int table_type = 0;
    int success = 1;
    show_table_menu();
    scanf("%d", &table_type);
    success = update(table_type);
    if (success == 2) {
        printf("Table not found\n");
    } else if (success == 0) {
        printf("Data not found in database\n");
    }
}

void handle_delete() {
    int table_type = 0;
    int success = 1;
    show_table_menu();
    scanf("%d", &table_type);
    success = delete(table_type);
    if (success == 2) {
        printf("Table not found\n");
    } else if (success == 0) {
        printf("Data not found in database\n");
    }
}