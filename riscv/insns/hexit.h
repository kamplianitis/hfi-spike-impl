// hexit instruction

require(p->extension_enabled(EXT_HFI));

if (!(STATE.hfi_status->read() & HFI_ENABLED_MASK)) {
    // HFI not enabled - trigger an exception
    // Using illegal instruction exception as this represents an invalid operation
    throw trap_illegal_instruction(insn.bits());
} else {
    std::cout << "HFI EXITING - status before: " << std::hex << STATE.hfi_status->read() << std::dec << std::endl;
    STATE.hfi_status->write(STATE.hfi_status->read() & ~HFI_ENABLED_MASK);
    std::cout << "HFI EXITED - status now: " << std::hex << STATE.hfi_status->read() << std::dec << std::endl;

    // set exit reason to 0
    STATE.hfi_status->write(STATE.hfi_status->read() & ~HFI_EXIT_REASON_MASK);
    
    // save exit pc, set last 2 bits of the pc to 0 and shift left by 1
    uint64_t exit_pc = pc & ~0x3; exit_pc = exit_pc << 1;
    STATE.hfi_status->write((STATE.hfi_status->read() & ~HFI_EXIT_PC_MASK) | (exit_pc & HFI_EXIT_PC_MASK));

    // check if redirect to exit_handler is turned on
    if (STATE.hfi_options->read() & HFI_OPTION_REDIRECT_EXIT_MASK) {
        // redirect to exit handler
        uint64_t exit_handler_addr = STATE.hfi_exit_handler->read();
        std::cout << "HFI EXIT HANDLER REDIRECT to address: " << std::hex << exit_handler_addr << std::dec << std::endl;
        set_pc(exit_handler_addr);
    }

}
