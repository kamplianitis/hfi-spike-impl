// hgtbd instruction, get base

require(p->extension_enabled(EXT_HFI));

// read current region value to decide which region to set

if (STATE.hfi_current_region->read() == 0) {
    WRITE_RD(STATE.hfi_explicit_bound_1->read());
} else if (STATE.hfi_current_region->read() == 1) {
    WRITE_RD(STATE.hfi_implicit_mask_1->read());
} else if (STATE.hfi_current_region->read() == 2) {
    WRITE_RD(STATE.hfi_code_mask->read());
} else {
    throw trap_illegal_instruction(insn.bits());
}
