#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "fat_standard.h"

typedef struct afatfsFile_t *afatfsFilePtr_t;

typedef enum {
    AFATFS_FILESYSTEM_STATE_UNKNOWN,
    AFATFS_FILESYSTEM_STATE_FATAL,
    AFATFS_FILESYSTEM_STATE_INITIALIZATION,
    AFATFS_FILESYSTEM_STATE_READY,
} afatfsFilesystemState_e;

typedef enum {
    AFATFS_OPERATION_IN_PROGRESS,
    AFATFS_OPERATION_SUCCESS,
    AFATFS_OPERATION_FAILURE,
} afatfsOperationStatus_e;

typedef struct afatfsDirEntryPointer_t {
    uint32_t clusterNumber;
    uint16_t sectorNumber;
    int16_t entryIndex;
} afatfsDirEntryPointer_t;

typedef afatfsDirEntryPointer_t afatfsFinder_t;

typedef enum {
    AFATFS_SEEK_SET,
    AFATFS_SEEK_CUR,
    AFATFS_SEEK_END,
} afatfsSeek_e;

typedef void (*afatfsOperationCallback_t)(bool success);
typedef void (*afatfsFileCallback_t)(afatfsFilePtr_t file);

bool afatfs_fopen(const char *filename, const char *mode, afatfsFileCallback_t complete);
void afatfs_fclose(afatfsFilePtr_t file);

bool afatfs_feof(afatfsFilePtr_t file);
uint32_t afatfs_fwrite(afatfsFilePtr_t file, const uint8_t *buffer, uint32_t len);
uint32_t afatfs_fread(afatfsFilePtr_t file, uint8_t *buffer, uint32_t len);
afatfsOperationStatus_e afatfs_fseek(afatfsFilePtr_t file, int32_t offset, afatfsSeek_e whence);

afatfsFilePtr_t afatfs_mkdir(const char *filename, afatfsFileCallback_t complete);
bool afatfs_chdir(afatfsFilePtr_t dirHandle);

bool afatfs_flush();
void afatfs_init();
bool afatfs_destroy();
void afatfs_poll();

uint32_t afatfs_getContiguousFreeSpace();
bool afatfs_isFull();

afatfsFilesystemState_e afatfs_getFilesystemState();
