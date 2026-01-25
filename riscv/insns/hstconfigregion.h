// hstconfigregion instruction, set base

require(p->extension_enabled(EXT_HFI));

// set the current region to the value in rs1
STATE.hfi_current_region->write(RS1);
