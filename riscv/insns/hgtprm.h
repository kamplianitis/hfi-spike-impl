// hgtprm instruction, get region mask

require(p->extension_enabled(EXT_HFI));

// read current region value to decide which region to set

WRITE_RD(STATE.hfi_permissions->read());