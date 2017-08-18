#include <arch/x86/pic.h>
#include <arch/arch.h>

#define PIC1_REG_COMMAND 0x20
#define PIC1_REG_STATUS  0x20
#define PIC1_REG_DATA    0x21
#define PIC1_REG_IMR     0x21 // Interrupt mask register

#define PIC2_REG_COMMAND 0xA0
#define PIC2_REG_STATUS  0xA0
#define PIC2_REG_DATA    0xA1
#define PIC2_REG_IMR     0xA1

#define PIC_ICW1_MASK_IC4  0x1
#define PIC_ICW1_MASK_SNGL 0x2
#define PIC_ICW1_MASK_ADI  0x4
#define PIC_ICW1_MASK_LTIM 0x8
#define PIC_ICW1_MASK_INIT 0x10

#define PIC_ICW4_MASK_UPM  0x1
#define PIC_ICW4_MASK_AEOI 0x2
#define PIC_ICW4_MASK_MS   0x4
#define PIC_ICW4_MASK_BUF  0x8
#define PIC_ICW4_MASK_SFNM 0x10

#define PIC_ICW1_MASK_IC4_EXPECT          1
#define PIC_ICW1_MASK_IC4_NO              0
#define PIC_ICW1_MASK_SNGL_YES            2
#define PIC_ICW1_MASK_SNGL_NO             0
#define PIC_ICW1_MASK_ADI_CALLINTERVAL4   4
#define PIC_ICW1_MASK_ADI_CALLINTERVAL8   0
#define PIC_ICW1_MASK_LTIM_LEVELTRIGGERED 8
#define PIC_ICW1_MASK_LTIM_EDGETRIGGERED  0
#define PIC_ICW1_MASK_INIT_YES            0x10
#define PIC_ICW1_MASK_INIT_NO             0

#define PIC_ICW4_MASK_UPM_86MODE          1
#define PIC_ICW4_MASK_UPM_MCSMODE         0
#define PIC_ICW4_MASK_AEOI_AUTOAEOI       2
#define PIC_ICW4_MASK_AEOI_NOAUTOAEOI     0
#define PIC_ICW4_MASK_MS_BUFFERMASTER     4
#define PIC_ICW4_MASK_MS_BUFFERSLAVE      0
#define PIC_ICW4_MASK_BUF_MODEYES         8
#define PIC_ICW4_MASK_BUF_MODENO          0
#define PIC_ICW4_MASK_SFNM_NESTEDMODE     0x10
#define PIC_ICW4_MASK_SFNM_NONESTED       0

uint8_t arch_x86_pic_read_data(uint8_t pic_num)
{
    if(pic_num > 1)
        return 0;

    uint8_t reg = (pic_num == 0) ? PIC1_REG_DATA : PIC2_REG_DATA;

    return inportb(reg);
}

void arch_x86_pic_send_data(uint8_t data, uint8_t pic_num)
{
    if(pic_num > 1)
        return;

    uint8_t reg = (pic_num == 0) ? PIC1_REG_DATA : PIC2_REG_DATA;

    outportb(reg, data);
}

void arch_x86_pic_send_command(uint8_t command, uint8_t pic_num)
{
    if(pic_num > 1)
        return;

    uint8_t reg = (pic_num == 0) ? PIC1_REG_COMMAND : PIC2_REG_COMMAND;

    outportb(reg, command);
}

/*
  void arch_x86_pic_mask_interrupt(uint8_t mask, uint8_t pic_num)
  {

  }
*/

void arch_x86_initialize_pic(uint8_t base0, uint8_t base1)
{
    uint8_t icw = 0;

    disable_interrupts();

    icw = (icw & ~PIC_ICW1_MASK_INIT) | PIC_ICW1_MASK_INIT_YES;
    icw = (icw & ~PIC_ICW1_MASK_IC4) | PIC_ICW1_MASK_IC4_EXPECT;

    // Send ICW1 to pic 1 & 2
    arch_x86_pic_send_command(icw, 0);
    arch_x86_pic_send_command(icw, 1);

    // Send ICW2 to pic 1 & 2
    arch_x86_pic_send_data(base0, 0);
    arch_x86_pic_send_data(base1, 1);

    // Send ICW3 to pic 1 & 2
    arch_x86_pic_send_data(0x04, 0);
    arch_x86_pic_send_data(0x02, 1);

    icw = (icw & ~PIC_ICW4_MASK_UPM) | PIC_ICW4_MASK_UPM_86MODE;

    // Send ICW4 to pic 1 & 2
    arch_x86_pic_send_data(icw, 0);
    arch_x86_pic_send_data(icw, 1);
}
