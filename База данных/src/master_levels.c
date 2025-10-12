#include "master_levels.h"

#include <stdio.h>
#include <stdlib.h>

void selectMasterLevels(const char* filename, Level** levels, int* count) {
    FILE* file = fopen(filename, "rb");
    if (file != NULL) {
        fseek(file, 0, SEEK_END);
        *count = ftell(file) / sizeof(Level);
        rewind(file);

        *levels = (Level*)malloc(*count * sizeof(Level));
        fread(*levels, sizeof(Level), *count, file);

        fclose(file);
    } else {
        printf("Unable to open file: %s\n", filename);
    }
}

void insertMasterLevels(const char* filename, Level* levels) {
    FILE* file = fopen(filename, "ab");
    if (file != NULL) {
        fwrite(levels, sizeof(Level), 1, file);
        fclose(file);
    } else {
        printf("Unable to open file: %s\n", filename);
    }
}

void updateMasterLevels(const char* filename, int* dooper) {
    *dooper = 0;
    FILE* file = fopen(filename, "rb");
    Level* levels_all;
    int count_levels = 0;
    Level* level = malloc(sizeof(Level));
    Level* level_new = malloc(sizeof(Level));
    printf("Write:\nlevel cells protected\n");
    scanf("%d %d %d", &level->level, &level->cells, &level->protected);
    selectMasterLevels(filename, &levels_all, &count_levels);
    fclose(file);
    file = fopen(filename, "w+b");
    for (int i = 0; i < count_levels; i++) {
        if (levels_all[i].level == level->level) {
            printf("Write new:\nlevel cells protected\n");
            scanf("%d %d %d", &level_new->level, &level_new->cells, &level_new->protected);
            fwrite(level_new, sizeof(Level), 1, file);
            *dooper = 1;
        } else {
            fwrite(&levels_all[i], sizeof(Level), 1, file);
        }
    }
    fclose(file);
    free(level);
    free(levels_all);
    free(level_new);
}

void deleteMasterLevels(const char* filename, int* dooper) {
    *dooper = 0;
    FILE* file = fopen(filename, "rb");
    Level* levels_all;
    int count_levels = 0;
    Level* level = malloc(sizeof(Level));
    printf("Write:\nlevel cells protected\n");
    scanf("%d %d %d", &level->level, &level->cells, &level->protected);
    selectMasterLevels(filename, &levels_all, &count_levels);
    fclose(file);
    file = fopen(filename, "w+b");
    for (int i = 0; i < count_levels; i++) {
        if (levels_all[i].level == level->level) {
            *dooper = 1;
        } else {
            fwrite(&levels_all[i], sizeof(Level), 1, file);
        }
    }
    fclose(file);
    free(level);
    free(levels_all);
}

void protectMasterLevels_by_id(const char* filename, Level* levels, int id) {
    FILE* file = fopen(filename, "rb");
    Level* levels_all;
    int count_levels = 0;
    selectMasterLevels(filename, &levels_all, &count_levels);
    fclose(file);
    file = fopen(filename, "wb");
    for (int i = 0; i < count_levels; i++) {
        if (levels_all[i].level == id) {
            fwrite(levels, sizeof(Level), 1, file);
        } else {
            fwrite(&levels_all[i], sizeof(Level), 1, file);
        }
    }
    fclose(file);
    free(levels_all);
}