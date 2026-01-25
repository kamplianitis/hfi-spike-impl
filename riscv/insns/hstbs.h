// hstbs instruction, set base

require(p->extension_enabled(EXT_HFI));

// read current region value to decide which region to set

if (STATE.hfi_current_region->read() == 0) {
    STATE.hfi_explicit_base_1->write(RS1);
} else if (STATE.hfi_current_region->read() == 1) {
    STATE.hfi_implicit_base_1->write(RS1);
} else if (STATE.hfi_current_region->read() == 2) {
    STATE.hfi_code_base->write(RS1);
} else {
    throw trap_illegal_instruction(insn.bits());
}
