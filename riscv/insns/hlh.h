require(p->extension_enabled(EXT_HFI));

// check base and bound
int64_t addr = RS1 + insn.i_imm();

// for now we only support one data region
// do not check current explicit region for now

// check addr < bound
if (addr < 0) {
  throw trap_illegal_instruction(insn.bits());
}

if (STATE.hfi_status->read() & HFI_ENABLED_MASK) { // if enabled
  // must be readable and in bound
  if (
    !(STATE.hfi_permissions->read() & 0b10) || // not readable. readable bit mask: 0b10
    (addr >= STATE.hfi_explicit_bound_1->read()) // out of bound
  ) {
    throw trap_illegal_instruction(insn.bits());
  }
  addr += STATE.hfi_explicit_base_1->read();
}

WRITE_RD(MMU.load<int16_t>(addr));
