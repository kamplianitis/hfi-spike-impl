.text

.globl hfi_get_version
.type hfi_get_version,@function
.align 16
hfi_get_version:
_hfi_get_version:
    # set rd to the return register: x10; 0000450B
    # .byte   0x0B, 0x45, 0x00, 0x00
    .word 0x0000450B
    ret

.global hfi_get_linear_range_count
.type hfi_get_linear_range_count,@function
.align 16
hfi_get_linear_range_count:
_hfi_get_linear_range_count:
    # set rd to the return register: x10; 0000450B
    # .byte   0x0B, 0x45, 0x00, 0x00
    .word 0x0200450B
    ret

.global hfi_enter
.type hfi_enter,@function
.align 16
hfi_enter:
_hfi_enter:
    # the pointer is already in a0, use directly
    # funct 7: 0, funct 3: 0, rs1 = x10
    .word 0x0005000B
    ret

.global hfi_enter_target
.type hfi_enter_target, @function
.align 16
hfi_enter_target:
_hfi_enter_target:
    # the pointer is already in a0, use directly
    # funct 7: 0, funct 3: 1, rs1 =x10, rs2 = x11
    .word 

.global hfi_exit
.type hfi_exit,@function
.align 16
hfi_exit:
_hfi_exit:
    # the pointer is already in a0, use directly
    # funct 7: 1, funct 3: 0, rs1 = x10
    .word 0x0205000B
    ret

.global hfi_set_base
.type hfi_set_base,@function
.align 16
hfi_set_base:
_hfi_set_base:
    # the base address is already in a0, use directly
    .word 0x0205200B
    ret

.global hfi_get_base
.type hfi_get_base,@function
.align 16
hfi_get_base:
_hfi_get_base:
    # the base address is already in a0, use directly
    .word 0x400250b
    ret

.global hfi_set_bound
.type hfi_set_bound,@function
.align 16
hfi_set_bound:
_hfi_set_bound:
    # the bound address is already in a0, use directly
    .word 0x0A05200B
    ret

.global hfi_get_bound
.type hfi_get_bound,@function
.align 16
hfi_get_bound:
_hfi_get_bound:
    # the bound address is already in a0, use directly
    .word 0xc00250b
    ret

.global hfi_set_permissions
.type hfi_set_permissions,@function
.align 16
hfi_set_permissions:
_hfi_set_permissions:
    # the permissions (bitmask) is already in a0, use directly
    .word 0x605250b
    ret

.global hfi_get_permissions
.type hfi_get_permissions,@function
.align 16
hfi_get_permissions:
_hfi_get_permissions:
    # the permissions (bitmask) is already in a0, use directly
    .word 0x805250b
    ret

.global hfi_set_region_type
.type hfi_set_region_type,@function
.align 16
hfi_set_region_type:
_hfi_set_region_type:
    # the region type is already in a0, use directly
    .word 0xe05250b
    ret

.global hfi_inspect
.type hfi_inspect,@function
.align 16
hfi_inspect:
_hfi_inspect:
    # the option is already in a0, use directly
    # .word 0x1005250B
    .word 0x1205250b
    ret

.global hfi_get_exit_reason
.type hfi_get_exit_reason,@function
.align 16
hfi_get_exit_reason:
_hfi_get_exit_reason:
    # set rd to the return register: x10; 
    .word 0x600150b
    ret

.global hfi_get_exit_pc
.type hfi_get_exit_pc,@function
.align 16
hfi_get_exit_pc:
_hfi_get_exit_pc:
    # set rd to the return register: x10; 
    .word 0x400150b
    ret

.global hfi_set_exit_handler
.type hfi_set_exit_handler,@function
.align 16
hfi_set_exit_handler:
_hfi_set_exit_handler:
    .word 0x5150b
    ret

.global hfi_get_exit_handler
.type hfi_get_exit_handler,@function
.align 16
hfi_get_exit_handler:
_hfi_get_exit_handler:
    .word 0x200150b
    ret

.global hfi_load_store_test
.type hfi_load_store_test,@function
.align 16
hfi_load_store_test:
_hfi_load_store_test:
    # enter the sandbox, perform load and store, then exit
    # param 0: enter option
    # param 1: load address
    # param 2: store address
    
    .word 0x0005000B      # a0 : x10
    .word 0x0005B503      # ld a0, 0(a1)          # load word from address in a1
    .word 0x00A63023      # sd a0, 0(a2)          # store word to address in a2
    .word 0x0205000B
    ret

.global hfi_explicit_load_test
.type hfi_explicit_load_test,@function
.align 16
hfi_explicit_load_test:
_hfi_explicit_load_test:
    # enter the sandbox, perform explicit load, then exit
    # param 0 (a0, x10): enter option
    # param 1 (a1, x11): load address
    .word 0x0005000B      # instruction takes x10 as input
    # explicit load
    .word 0x0005B56B      # hld a0, 0(a1) # a1 gets replaced with the base. now only accessing offset 0
    # exit
    .word 0x0205000B    
    ret

.global hfi_explicit_store_test
.type hfi_explicit_store_test,@function
.align 16
hfi_explicit_store_test:
_hfi_explicit_store_test:
    # enter the sandbox, perform explicit store, then exit
    # param 0 (a0, x10): enter option
    # param 1 (a1, x11): store address
    # param 2 (a2, x12): value to store
    .word 0x0005000B      # instruction takes x10 as input
    # explicit store
    .word 0xc5b02b      # hsd a2, 0(a1)
    # exit
    .word 0x0205000B    
    ret

.global hfi_select_region_to_config
.type hfi_select_region_to_config,@function
.align 16
hfi_select_region_to_config:
_hfi_select_region_to_config:
    # the region number is already in a0, use directly
    .word 0x5250b
    ret

.global hfi_set_region_to_access
.type hfi_set_region_to_access,@function
.align 16
hfi_set_region_to_access:
_hfi_set_region_to_access:
    # the region number is already in a0, use directly
    .word 0x5350b
    ret

.global hfi_imp_load_perm_test
.type hfi_imp_load_perm_test,@function
.align 16
hfi_imp_load_perm_test:
_hfi_imp_load_perm_test:
    # enter the sandbox, perform load and store, then exit
    # param 0: enter option
    # param 1: load address
    # param 2: store address
    
    .word 0x0005000B      # a0 : x10
    lw a0, 0(a1)          # load word from address in a1
    # sw a0, 0(a2)          # store word to address in a2
    .word 0x0205000B
    ret

.globl noop_func
.type noop_func,@function
.align 16
noop_func:
_noop_func:
    ret

.globl hfi_exit_handler_test
.type hfi_exit_handler_test,@function
.align 16
hfi_exit_handler_test:
_hfi_exit_handler_test:
    # rdi: param 1 is the sandbox params
    # enter the sandbox, then exit. The exit would invoke the exit handler which will directly return
    # set x10 to the param 0b100 (redirect exits)
    li a0, 0b100          # set options to redirect exits
    .word 0x0005000B      # enter sandbox

.globl hfi_test_exit_location
.type hfi_test_exit_location,@function
hfi_test_exit_location:
    .word 0x0205000B      # exit sandbox
    unimp # should not reach here