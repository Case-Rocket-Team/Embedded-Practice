/**
 * @file W25Q64FV.hpp 
 * @author Kyler Rosen
 * @brief Header file for the W25Q64 Flash Chip interface library
 * @version 0.1
 * @date 2022-11-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <Arduino.h>
#include <SPI.h>

#ifndef W25Q64FV
#define W25Q64FV

/********** INSTRUCTION SETS **********/
#define W25Q64FV_INSTRUCTION_WRITE_ENABLE                   0x06 
#define W25Q64FV_INSTRUCTION_VOLATILE_SR_WRITE_ENABLE       0x50
#define W25Q64FV_INSTRUCTION_WRITE_DISABLE                  0x04 
#define W25Q64FV_INSTRUCTION_READ_STATUS_REGISTER_1         0x05 
#define W25Q64FV_INSTRUCTION_READ_STATUS_REGISTER_2         0x35 
#define W25Q64FV_INSTRUCTION_WRITE_STATUS_REGISTER          0x01
#define W25Q64FV_INSTRUCTION_PAGE_PROGRAM                   0x02 
#define W25Q64FV_INSTRUCTION_SECTOR_4K_ERASE                0x20 
#define W25Q64FV_INSTRUCTION_BLOCK_32K_ERASE                0x52
#define W25Q64FV_INSTRUCTION_BLOCK_64K_ERASE                0xD8
#define W25Q64FV_INSTRUCTION_CHIP_ERASE                     0xC7 // might also be 0x60
#define W25Q64FV_INSTRUCTION_ERASE_PROGRAM_SUSPEND          0x75
#define W25Q64FV_INSTRUCTION_ERASE_PROGRAM_RESUME           0x7A
#define W25Q64FV_INSTRUCTION_POWER_DOWN                     0xB9
#define W25Q64FV_INSTRUCTION_READ_DATA                      0x03 
#define W25Q64FV_INSTRUCTION_FAST_READ                      0x0B
#define W25Q64FV_INSTRUCTION_RELEASE_POWERDOWN              0xAB
#define W25Q64FV_INSTRUCTION_MANUFACTURER_DEVICE_ID         0x90 
#define W25Q64FV_INSTRUCTION_JEDEC_ID                       0x9F
#define W25Q64FV_INSTRUCTION_READ_UNIQUE_ID                 0x4B 
#define W25Q64FV_INSTRUCTION_READ_SFDP_REGISTER             0x5A 
#define W25Q64FV_INSTRUCTION_ERASE_SECURITY_REGISTERS       0x44
#define W25Q64FV_INSTRUCTION_PROGRAM_SECURITY_REGISTERS     0x42 
#define W25Q64FV_INSTRUCTION_READ_SECURITY_REGISTERS        0x48
#define W25Q64FV_INSTRUCTION_ENABLE_QPI                     0x38
#define W25Q64FV_INSTRUCTION_ENABLE_RESET                   0x66 
#define W25Q64FV_INSTRUCTION_RESET                          0x99
// DUAL IO TABLE 
#define W25Q64FV_INSTRUCTION_FAST_READ_DUAL_OUTPUT          0x3B 
#define W25Q64FV_INSTRUCTION_FAST_READ_DUAL_IO              0xBB
#define W25Q64FV_INSTRUCTION_MANUFACTURER_DEVICE_ID_DUAL_IO 0x92 
// QUAD IO TABLE 
#define W25Q64FV_INSTRUCTION_QUAD_PAGE_PROGRAM              0x32 
#define W25Q64FV_INSTRUCTION_FAST_READ_QUAD_OUTPUT          0x6B 
#define W25Q64FV_INSTRUCTION_FAST_READ_QUAD_IO              0xEB
#define W25Q64FV_INSTRUCTION_WORD_READ_QUADO_IO             0xE7
#define W25Q64FV_INSTRUCTION_OCTAL_WORD_READ_QUAD_IO        0xE3 
#define W25Q64FV_INSTRUCTION_SET_BURST_WRAP                 0x77
#define W25Q64FV_INSTRUCTION_MANUFACTURER_DEVICE_ID_QUAD_IO 0x94     

/********** SETTINGS **********/ 
#define W25Q64FV_SPI_SPEED          20000000 // 104 MHz (104 max)

#define W25Q64FV_DEFAULT_TIMEOUT    5000 // Default timeout for most operations 
#define W25Q64FV_CHIP_ERASE_TIMEOUT 100000 // Chip erase timeout. Per spec, this is typically 20 seconds, at most 100 seconds. 


typedef enum{
    W25Q64FV_OK = 0,                ///< Chip OK
    W25Q64FV_COMMUNICATIONS_FAIL,   ///< Communications Error
    W25Q64FV_BUSY,                  ///< Chip Report Busy
    W25Q64FV_TIMEOUT,               ///< Chip timeout on wait operation
    W25Q64FV_NOT_VALID              ///< Not a valid operation
} W25Q64FV_status_t;


class F25Q64FV {
        public: 

    void select();

    void release();

    void manufacturer();

    void get_registers();

    bool busy();

    void read(byte* read);

    void write_enable();

    void erase(byte one, byte two, byte three);

    void write(byte one, byte two, byte three);

    void write_zero();

    void print_arr(byte A[]);

    void read_test();

    void read_and_write_test();

    void initialize();

    void disable_write_protect();

    void enable_write_protect();

    void write_protect_fix();

    void reset();

    void disable_QPI();

    void waiting(int time);

    void chip_test();
};

#endif