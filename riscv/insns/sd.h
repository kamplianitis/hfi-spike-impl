require((xlen == 64) || p->extension_enabled(EXT_ZILSD));

uint64_t addr = RS1 + insn.s_imm();

if ((STATE.hfi_status->read() & HFI_ENABLED_MASK) && (STATE.prv == PRV_U)) {
  // std::cout << "SD executed - HFI status: " << std::hex << STATE.hfi_status->read() 
  //         << ", prv: " << STATE.prv << ", PRV_U=" << PRV_U << std::dec << std::endl;  
  // std::cout << "Implicit region check for sd" << std::endl;
  // std::cout << "addr: " << std::hex << addr << std::dec << std::endl;
  
  if (
    !(STATE.hfi_permissions->read() & 0b100000) || // not writable
    ((addr & STATE.hfi_implicit_mask_1->read()) != STATE.hfi_implicit_base_1->read()) // out of bound
  ) {
    // std::cout << "HFI implicit region write violation!" << std::endl;
    throw trap_illegal_instruction(insn.bits());
  } else {
    // std::cout << "HFI implicit region write permitted." << std::endl;
  }
}

if (xlen == 32) {
  MMU.store<uint64_t>(RS1 + insn.s_imm(), RS2_PAIR);
} else {
  MMU.store<uint64_t>(RS1 + insn.s_imm(), RS2);
}
