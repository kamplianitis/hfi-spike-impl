require(p->extension_enabled(EXT_HFI));

// check base and bound
uint64_t addr = RS1 + insn.s_imm();

// for now we only support one data region
// do not check current explicit region for now

// check addr < bound
if (addr < 0) {
  throw trap_illegal_instruction(insn.bits());
}

if (STATE.hfi_status->read() & HFI_ENABLED_MASK) { // if enabled
  // must be writable and in bound
  if (
    !(STATE.hfi_permissions->read() & 0b100) || // not writable. writable bit mask: 0b100
    (addr >= STATE.hfi_explicit_bound_1->read()) // out of bound
  ) {
    throw trap_illegal_instruction(insn.bits());
  }
  addr += STATE.hfi_explicit_base_1->read();
}

MMU.store<uint16_t>(addr, RS2);
