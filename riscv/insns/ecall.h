switch (STATE.prv)
{
  case PRV_U: {
    int hfi_allowed = 1;
    if (STATE.hfi_status->read() & HFI_ENABLED_MASK) { // HFI enabled 
      // save exit reason to 1
      STATE.hfi_status->write(STATE.hfi_status->read() | HFI_EXIT_REASON_MASK);
      
      // save exit pc
      uint64_t exit_pc = pc & ~0x3; exit_pc = exit_pc << 1;
      STATE.hfi_status->write((STATE.hfi_status->read() & ~HFI_EXIT_PC_MASK) | (exit_pc & HFI_EXIT_PC_MASK));

      // check if redirect syscall is on
      if (STATE.hfi_options->read() & HFI_OPTION_REDIRECT_ECAL_MASK) {
        // redirect to exit handler
        uint64_t exit_handler_addr = STATE.hfi_exit_handler->read();
        std::cout << "HFI EXIT HANDLER REDIRECT to address: " << std::hex << exit_handler_addr << std::dec << std::endl;
        hfi_allowed = 0;
        set_pc(exit_handler_addr);
      }
    }
    if (hfi_allowed)
      throw trap_user_ecall();
    break;
  }
  case PRV_S:
    if (STATE.v)
      throw trap_virtual_supervisor_ecall();
    else
      throw trap_supervisor_ecall();
  case PRV_M: throw trap_machine_ecall();
  default: abort();
}
