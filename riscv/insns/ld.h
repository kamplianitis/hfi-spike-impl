require((xlen == 64) || p->extension_enabled(EXT_ZILSD));

int64_t addr = RS1 + insn.i_imm();

// Debug output
if ((STATE.hfi_status->read() & HFI_ENABLED_MASK) && (STATE.prv == PRV_U)) {
  // std::cout << "LD executed - HFI status: " << std::hex << STATE.hfi_status->read() 
  //         << ", prv: " << STATE.prv << ", PRV_U=" << PRV_U << std::dec << std::endl;
  // std::cout << "Implicit region check for ld" << std::endl;
  // std::cout << "addr: " << std::hex << addr << std::dec << std::endl;
  // std::cout << "permissions: " << std::hex << STATE.hfi_permissions->read() << std::dec << std::endl;
  // std::cout << "implicit_mask: " << std::hex << STATE.hfi_implicit_mask_1->read() << std::dec << std::endl;
  // std::cout << "implicit_base: " << std::hex << STATE.hfi_implicit_base_1->read() << std::dec << std::endl;
  
  // Fix precedence bug
  if (
    !(STATE.hfi_permissions->read() & 0b010000) || // not readable
    ((addr & STATE.hfi_implicit_mask_1->read()) != STATE.hfi_implicit_base_1->read()) // out of bound
  ) {
    std::cout << "HFI implicit region violation!" << std::endl;
    throw trap_illegal_instruction(insn.bits());
  } else {
    // std::cout << "HFI implicit region check passed." << std::endl;
  }
}

if (xlen == 32) {
  WRITE_RD_PAIR(MMU.load<int64_t>(RS1 + insn.i_imm()));
} else {
  WRITE_RD(MMU.load<int64_t>(RS1 + insn.i_imm()));
}

