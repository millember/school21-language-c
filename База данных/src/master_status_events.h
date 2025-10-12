#ifndef MASTER_EVENTS_H
#define MASTER_EVENTS_H

typedef struct {
    int eventId;
    int moduleId;
    int newStatus;
    char date[11];
    char time[9];
} StatusEvent;

void selectMasterStatusEvents(const char*, StatusEvent**, int*);
void insertMasterStatusEvents(const char*, StatusEvent*);
void updateMasterStatusEvents(const char*, int*);
void deleteMasterStatusEvents(const char*, int*);

#endif