#include <assert.h>
#include <iostream>
#include <cstdint>
#include <limits>
#include "hfi.h"

int main(int argc, char* argv[])
{   
    std::cout << "--- HFI Sandbox Test ---" << std::endl;
    assert(hfi_get_version() == 1);
    std::cout << "HFI Version: " << hfi_get_version() << std::endl; 

    hfi_enter(0);   
    hfi_exit();

    uint64_t FULL_PERM = 0b111; // full perm for explicit data region 1

    uint64_t array[] = {1, 2, 3, 4, 5, 6, 7, 8};
    uint64_t options = 0;

    std::cout << "array address: " << (uint64_t)&array[0] << std::endl;

    hfi_select_region_to_config(0);
    std::cout << "region selected" << std::endl;
    hfi_set_base((uint64_t)&array[0]);
    std::cout << "base set" << std::endl;
    hfi_set_bound(sizeof(array)/2);
    std::cout << "bound set " << std::hex << sizeof(array)/2 << std::dec << std::endl;
    hfi_set_permissions(FULL_PERM);
    std::cout << "permissions set" << std::endl;

    // implicit region check
    hfi_select_region_to_config(1);
    hfi_set_permissions(0b111111); // no read perm for implicit region 1
    uint64_t perm = hfi_get_permissions();
    std::cout << "permissions set " << std::hex << perm << std::dec << std::endl;
    
    for (int i = 0; i < 8; i++) {
        std::cout << "array[" << i << "] = ";
        hfi_load_store_test(options, &array[i], &array[i]);
        std::cout << array[i] << std::endl;
    }

    // // access the array
    // for (int i = 0; i < 8; i++) {
    //     std::cout << "Accessing " << i << "-th element" << std::endl;
    //     // int64_t result = hfi_explicit_load_test(options, (void*)&array[i]);
    //     // std::cout << "Explicit load result: " << result << std::endl;
    //     uint64_t offset = (uint64_t)&array[i] - (uint64_t)&array[0];
    //     int64_t res = hfi_explicit_load_test(options, (void*)offset);
    //     std::cout << "Implicit load result: " << res << std::endl;

    //     hfi_explicit_store_test(options, (void*)offset, 0x2324);
    //     std::cout << "After explicit store, array["<< i << "] = " << array[i] << std::endl;
    // }

    // // make implicit data regions run smoothly
    // hfi_select_region_to_config(4);
    // hfi_set_base(0);
    // hfi_set_bound(0);
    // hfi_set_permissions(0b11);

    // hfi_select_region_to_config(0);

    // // Check entry and exit, should pass
    // hfi_set_permissions(0b11); // grant all permissions
    // std::cout << "Check entry and exit, should pass" << std::endl;
    // assert(display(0) == false);
    
    // /*************************************************** */
    // hfi_enter(options);

    // assert(display(0) == true);
    // display(1);

    // for (int i = 0; i < 8; i++) {
    //     std::cout << "array[" << i << "] = " << array[i] << std::endl;
    //     array[i] = i + 10;
    // }

    // assert(display(0) == true);
    

    // hfi_exit();
    // /**************************************************** */

    // assert(display(0) == false);
    std::cout << "Test 2 passed" << std::endl;
}