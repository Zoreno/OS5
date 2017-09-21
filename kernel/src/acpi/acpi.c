// ACPI Test file

#include <stdint.h>
#include <string.h>
#include <stdio.h>

//==============================================================================
// Generic Address Structure
//==============================================================================

/**
 * @brief Generic Address Structure
 *
 * Provides a robust means to describe register locations.
 */
typedef struct
{
    /**
     * Address Space where the data structure or register exists.
     */
    uint8_t AddressSpaceID;

    /**
     * Size in bits of given register.
     */
    uint8_t RegisterBitWidth;

    /**
     * Bit offset of given register at given address.
     */
    uint8_t RegisterBitOffset;

    /**
     * Specifies access size.
     */
    uint8_t AccessSize;

    /**
     * Address of data structure or register in address space.
     */
    uint64_t Address;

} __attribute__((packed)) GenericAddressStructure;

//==============================================================================
// RSDP
// ==============================================================================

/**
 * Root System Description Pointer
 */
typedef struct
{
    /**
     * Must be "RSD PTR ".
     */
    char Signature[8];

    /**
     * Checksum for the first 20 bytes of the table.
     */
    uint8_t Checksum;

    /**
     * String that identifies the OEM.
     */
    char OEMID[6];

    /**
     * Revision of this structure.
     */
    uint8_t Revision;

    /**
     * 32 bit physical address of the RSDT.
     */
    uint32_t RsdtAddress;

    /**
     * Length of this table.
     */
    uint32_t Length;

    /**
     * 64-bit physical address of the XSDT.
     */
    uint64_t XsdtAddress;

    /**
     * Checksum for the full table.
     */
    uint8_t ExtendedChecksum;

    /**
     * Reserved
     */
    uint8_t reserved[3];
} __attribute__((packed)) RSDPDescriptor;

void* acpi_find_rsdp();
void acpi_debug_dump_rsdp_desc_contents(RSDPDescriptor* rsdp);
int acpi_rsdp_calc_checksum(RSDPDescriptor* rsdp);

void* acpi_find_rsdp()
{
    char *sig = "RSD PTR ";

    for(char *ptr = 0xC00E0000; ptr < 0xC00FFFFF; ptr += 16)
    {
        if(memcmp(ptr, sig, 8) == 0)
        {
            return (void*)ptr;
        }
    }

    int ebda = *((short*) 0xC000040E);
    ebda = ebda*0x10 & 0x000FFFFF;
    ebda += 0xC0000000;

    for(char *ptr = ebda; ptr < ebda + 1024; ptr += 16)
    {
        if(memcmp(ptr, sig, 8) == 0)
        {
            return (void*)ptr;
        }
    }

    return (void*) NULL;
}

void acpi_debug_dump_rsdp_desc_contents(RSDPDescriptor* rsdp)
{
    if(!rsdp)
        return;

    char sig[9] = {0};
    char oem[7] = {0};

    memcpy(sig, rsdp->Signature, 8);
    memcpy(oem, rsdp->OEMID, 6);

    printf("Signature: %s\n", sig);
    printf("Checksum: %i\n", rsdp->Checksum);
    printf("OEMID: %s\n", oem);
    printf("Revision: %i\n", rsdp->Revision);
    printf("RsdtAddress: %#010x\n", rsdp->RsdtAddress);
    printf("Length: %i\n", rsdp->Length);
    printf("XsdtAddress: %#010x\n", rsdp->XsdtAddress);
    printf("ExtendedChecksum: %i\n", rsdp->ExtendedChecksum);
}

int acpi_rsdp_calc_checksum(RSDPDescriptor* rsdp)
{
    uint8_t* rsdp_byte = (uint8_t*)rsdp;

    // Start by calculating original checksum.
    // This means that the first 20 bytes should sum to 0 mod 256.

    uint8_t sum = 0;

    for(int i = 0; i < 20; ++i)
    {
        sum += rsdp_byte[i];
    }

    if(sum != 0)
    {
        return 0;
    }

    // Check the extended checksum
    // The length of the table is in Length field.
    sum = 0;

    for(int i = 0; i < rsdp->Length; ++i)
    {
        sum += rsdp_byte[i];
    }

    if(sum != 0)
    {
        return 0;
    }

    return 1;

}

//==============================================================================
// System Description Table Header
//==============================================================================

/**
 * All system description tables starts with this structure.
 */
typedef struct
{
    /**
     * Signature of the table.
     */
    char Signature[4];

    /**
     * Length in bytes of table.
     */
    uint32_t Length;

    /**
     * Revision of the structure.
     */
    uint8_t Revision;

    /**
     * Checksum for the entire table.
     */
    uint8_t Checksum;

    /**
     * String identifying the OEM.
     */
    char OEMID[6];

    /**
     * OEM-supplied string to identify a particular data table.
     */
    char OEMTableID[8];

    /**
     * OEM-supplied revision number.
     */
    uint32_t OEMRevision;

    /**
     * Vendor ID of the utility that created the table.
     */
    uint32_t CreatorID;

    /**
     * Revision of utility that created the table.
     */
    uint32_t CreatorRevision;
    
} __attribute__((packed)) ACPISystemTableHeader;

//==============================================================================
// RSDT
//==============================================================================

/**
 * Root System Descriptor Table
 */
typedef struct
{
    /**
     * Standard ACPI header
     */
    ACPISystemTableHeader header;

    /**
     * First table entry
     */
    uint32_t first_entry;
    
} __attribute__((packed)) RSDT;

//==============================================================================
// XSDT
//==============================================================================

/**
 * Extended System Descriptor Table
 */
typedef struct
{
    /**
     * Standard ACPI header
     */
    ACPISystemTableHeader header;

    /**
     * First table entry.
     */
    uint64_t first_entry;
    
} __attribute__((packed)) XSDT;

//==============================================================================
// ACPI
//==============================================================================

int acpi_calc_checksum(ACPISystemTableHeader* header);

int acpi_calc_checksum(ACPISystemTableHeader* header)
{
    uint8_t sum = 0;

    uint8_t* table_bytes = (uint8_t*) header;

    for(uint32_t i = 0; i < header->Length; ++i)
    {
        sum += table_bytes[i];
    }

    return (sum == 0) ? 1 : 0;
}

void acpi_initialize()
{
    RSDPDescriptor* rsdp = acpi_find_rsdp();

    if(!rsdp)
    {
        printf("Could not find RSDP. Aborting ACPI initiation.\n");
    }

    if(acpi_rsdp_calc_checksum(rsdp))
    {
        printf("RSDP checksum valid\n");
    }

    acpi_debug_dump_rsdp_desc_contents(rsdp);

    RSDT* rsdt = rsdp->RsdtAddress;

    if(acpi_calc_checksum((ACPISystemTableHeader*)rsdt))
    {
        printf("RSDT Valid!\n");
    }

}
