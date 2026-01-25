require(p->extension_enabled(EXT_HFI));

std::cout << "hsw" << std::endl;

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
  std::cout << std::hex << "hsw: original addr = " << addr << std::endl;
  std::cout << "hsw: base = " << STATE.hfi_explicit_base_1->read() << std::endl;
  addr += STATE.hfi_explicit_base_1->read();
  std::cout << "hsw: new sandboxed addr = " << addr << std::endl;
}

// MMU.store<uint32_t>(addr, RS2);

std::cout << "hsw: About to store to addr=" << std::hex << addr 
          << " value=" << RS2 << std::dec << std::endl;

// Try to check if this address is valid
try {
  MMU.store<uint32_t>(addr, RS2);
  std::cout << "hsw: Store succeeded!" << std::endl;
} catch (...) {
  std::cout << "hsw: Store FAILED at addr=" << std::hex << addr << std::dec << std::endl;
  throw;
}
