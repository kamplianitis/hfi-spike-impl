// hstprm instruction, set permissions

require(p->extension_enabled(EXT_HFI));

// set the permissions to the value in rs1
STATE.hfi_permissions->write(RS1);
std::cout << "hstprm: set HFI permissions to " << std::hex << RS1 << std::dec<< std::endl;