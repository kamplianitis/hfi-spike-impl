#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// The number of linear ranges supported
// This can be different on different machines
// In this machine, it is 1
#define LINEAR_RANGE_COUNT 1
#define IMPLICIT_READABLE 0x1
#define IMPLICIT_WRITABLE 0x2
#define EXPLICIT_READABLE 0x4
#define EXPLICIT_WRITABLE 0x8
#define FULL_PERMISSIONS 0xF

// Metadata for one linear range or "segment" of a sandbox
typedef struct {
    // Permissions for this range
    char readable;
    char writable;
    char executable;
    // A constant base whose value is added to all loads and stores performed in the sandbox
    uint64_t base_address;
    // The lower bound of this segment's allowed range
    uint64_t lower_bound;
    // The upper bound of this segment's allowed range
    uint64_t upper_bound;
} hfi_linear_range;

// The metadata required for a "hardware sandbox"
struct hfi_sandbox {
    // Each segment specifies an address range and its associated permissions
    hfi_linear_range ranges[LINEAR_RANGE_COUNT];
};


/* 
** hfi_get_version()
** Get the version of HFI implemented in hardware.
** Return value: the version of the hfi
*/
uint64_t hfi_get_version();

/*
** hfi_get_linear_range_count()
** Get the number of linear ranges supported by the HFI.
** Return value: the number of linear ranges
*/
uint64_t hfi_get_linear_range_count();

/*
** hfi_enter_sandbox(hfi_sandbox* param_hfi_curr_sandbox_data);
** Loads CPU regs with bound checking info
** Params: pointer to the current sandbox data
*/
void hfi_enter(uint64_t options);

/*
** hfi_exit_sandbox()
** Restores CPU regs to their previous state
*/
void hfi_exit();

/*
** hfi_set_base(uint64_t base);
** Sets the base address for the current sandbox
** Params: the base address
*/
void hfi_set_base(uint64_t base);

/**
 * uint64_t hfi_get_base();
 * Gets the base address for the current sandbox
 * Return value: the base address
 */
uint64_t hfi_get_base();

/*
** hfi_set_bound(uint64_t lower, uint64_t upper);
** Sets the bounds for the current sandbox
** Params: the lower and upper bounds
*/
void hfi_set_bound(uint64_t bound);


/**
 * uint64_t hfi_get_bound();
 * Gets the bounds for the current sandbox
 * Return value: the bounds 
 */
uint64_t hfi_get_bound();

/*
** hfi_set_permissions(uint64_t permissions);
** Sets the permissions for the current sandbox
** Params: the permissions (bitmask)
*/
void hfi_set_permissions(uint64_t permissions);

uint64_t hfi_get_permissions();

/*
** hfi_inspect(uint64_t option);
** Inspects the current sandbox configuration
** Params: option to specify what to inspect
*/
uint64_t hfi_inspect(uint64_t option);

/*
** void hfi_set_exit_handler(void *handler);
*/
void hfi_set_exit_handler(uint64_t handler);

/*
** uint64_t hfi_get_exit_handler();
*/
uint64_t hfi_get_exit_handler();

/*
** hfi_load_store_test(void* load_addr, void* store_addr);
** Tests load and store operations within the sandbox
** Params: addresses to load from and store to
*/
void hfi_load_store_test(uint64_t options, void* load_addr, void* store_addr);

/*
** int64_t hfi_explicit_load_test(uint64_t options, void* load_addr);
** Tests explicit load operation within the sandbox
** Params: options and address to load from
*/
int64_t hfi_explicit_load_test(uint64_t options, void* load_addr);

/*
** void hfi_explicit_store_test(uint64_t options, void* store_addr, int value);
** Tests explicit store operation within the sandbox
** Params: options, address to store to, and value to store
*/
void hfi_explicit_store_test(uint64_t options, void* store_addr, int value);

/*
** uint64_t hfi_imp_load_perm_test(uint64_t options, void* load_addr);
** Tests implicit load operation permissions within the sandbox
** Params: options and address to load from
*/
void hfi_imp_load_perm_test(uint64_t options, void* load_addr);

/*
** uint64_t hfi_get_exit_reason();
** Gets the reason for the last sandbox exit
*/
uint64_t hfi_get_exit_reason();

/*
** uint64_t hfi_get_exit_pc();
** Gets the program counter at the time of the last sandbox exit
*/
uint64_t hfi_get_exit_pc();

/**
 * void hfi_select_region_to_config(uint64_t region_number);
 */
void hfi_select_region_to_config(uint64_t region_number);

/**
 * void hfi_set_region_to_access(uint64_t region_number);
 */
void hfi_set_region_to_access(uint64_t region_number);

/*
** void hfi_exit_handler_test();
** void hfi_test_exit_location();
** Tests the exit handler functionality; enter and exit, and mark the exit location
*/
void hfi_exit_handler_test();
void hfi_test_exit_location();

/*
** void noop_func();
** A no-operation function for testing purposes
*/
void noop_func();

/*
** 
*/

#ifdef __cplusplus
}
#endif