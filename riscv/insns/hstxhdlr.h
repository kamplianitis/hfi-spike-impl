// hstxhdlr instruction, set base

require(p->extension_enabled(EXT_HFI));

// read current region value to decide which region to set
STATE.hfi_exit_handler->write(RS1);
std::cout << "hstxhdlr: set hfi exit handler base to " << std::hex << STATE.hfi_exit_handler->read() << std::endl;
