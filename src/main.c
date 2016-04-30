#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <malloc.h>
#include "dynamic_libs/os_functions.h"
#include "dynamic_libs/fs_functions.h"
#include "dynamic_libs/gx2_functions.h"
#include "dynamic_libs/sys_functions.h"
#include "dynamic_libs/vpad_functions.h"
#include "dynamic_libs/padscore_functions.h"
#include "dynamic_libs/socket_functions.h"
#include "dynamic_libs/ax_functions.h"
#include "fs/fs_utils.h"
#include "fs/sd_fat_devoptab.h"
#include "system/memory.h"
#include "utils/logger.h"
#include "utils/utils.h"
#include "common/common.h"

/* Entry point */
int Menu_Main(void)
{
    //!*******************************************************************
    //!                   Initialize function pointers                   *
    //!*******************************************************************
    //! do OS (for acquire) and sockets first so we got logging
    InitOSFunctionPointers();
    InitSocketFunctionPointers();

    log_init("192.168.178.21");
    log_print("Starting launcher\n");

    InitFSFunctionPointers();
    InitVPadFunctionPointers();

    log_print("Function exports loaded\n");

    // Remove update
    unsigned int nn_ccr_handle;
    OSDynLoad_Acquire("nn_ccr.rpl", &nn_ccr_handle);
    void(*CCRSysDRCFWUpdateForward)();
    OSDynLoad_FindExport(nn_ccr_handle, 0, "CCRSysDRCFWUpdateForward", &CCRSysDRCFWUpdateForward);
    CCRSysDRCFWUpdateForward();

    log_deinit();

    SYSLaunchMenu();
    return EXIT_SUCCESS;
}

