// henter instruction

require(p->extension_enabled(EXT_HFI));

if (STATE.hfi_status->read() & HFI_ENABLED_MASK) {
    // HFI already enabled - trigger an exception
    // Using illegal instruction exception as this represents an invalid operation
    throw trap_illegal_instruction(insn.bits());
} else {
    STATE.hfi_status->write(STATE.hfi_status->read() | HFI_ENABLED_MASK);
    STATE.hfi_options->write(RS1);
    std::cout << "HFI ENTERED - status now: " << std::hex << STATE.hfi_status->read() 
              << ", perm=" << STATE.hfi_permissions->read() << std::dec << std::endl;
}
serialize(); // force simulator to break out of current execution loop and restart, reevaluating slow_path() with the new hfi state
