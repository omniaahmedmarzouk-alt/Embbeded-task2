 // LCD module connections
sbit LCD_RS at RB0_bit;
sbit LCD_EN at RB1_bit;
sbit LCD_D4 at RB2_bit;
sbit LCD_D5 at RB3_bit;
sbit LCD_D6 at RB4_bit;
sbit LCD_D7 at RB5_bit;

// Directions
sbit LCD_RS_Direction at TRISB0_bit;
sbit LCD_EN_Direction at TRISB1_bit;
sbit LCD_D4_Direction at TRISB2_bit;
sbit LCD_D5_Direction at TRISB3_bit;
sbit LCD_D6_Direction at TRISB4_bit;
sbit LCD_D7_Direction at TRISB5_bit;

void ADC_Init(void)
{
    TRISA = 0xFF; // PORTA as input

    ADCON0 = 0xC1; // Internal RC clock, AN0 selected, ADC enabled
    ADCON1 = 0x80; // Right justified, AN0~AN7 analog
}

int ADC_Read(int channel)
{
    ADCON0 &= 0xC7; // Clear channel selection bits
    ADCON0 |= (channel << 3); // Put channel number into CHS2:CHS0

    Delay_us(20); // Acquisition delay

    GO_DONE_bit = 1; // Start conversion
    while(GO_DONE_bit); // Wait until conversion finishes

    return ((ADRESH << 8) | ADRESL); // Return 10-bit ADC result
}

void main()
{
    unsigned int adc_value;
    float voltage;
    float temperature;
    char txt[16];

    ADC_Init();

    Lcd_Init();
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Cmd(_LCD_CURSOR_OFF);

    while(1)
    {
        adc_value = ADC_Read(0);

        // Convert ADC value to voltage
        // Assuming Vref = 5V
        voltage = (adc_value * 5.0) / 1023.0;

        // LM35: 10mV per degree
        temperature = voltage * 100.0;

        // Convert float to string
        FloatToStr(temperature, txt);

        // Display
//        Lcd_Cmd(_LCD_CLEAR);

        Lcd_Out(1,1,"Temp:");

        Lcd_Out(2,1,txt);
        Lcd_Chr_CP(223);           // Degree symbol
        Lcd_Out_CP("C");

        Delay_ms(500);
    }
}