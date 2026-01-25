// hentertarg instruction

require(p->extension_enabled(EXT_HFI));

if (STATE.hfi_status->read() & HFI_ENABLED_MASK) {
    // HFI already enabled - trigger an exception
    // Using illegal instruction exception as this represents an invalid operation
    throw trap_illegal_instruction(insn.bits());
} else {
    STATE.hfi_status->write(STATE.hfi_status->read() | HFI_ENABLED_MASK);
    STATE.hfi_options->write(RS1);
    std::cout << "HFI ENTERED - status now: " << std::hex << STATE.hfi_status->read() 
              << ", prv=" << STATE.prv << std::dec << std::endl;

    // take rs2 and jump to target
    set_pc(RS2);
}
