/**
 * Author Teemu Mäntykallio, Henri Starmans
 * Initializes the library 
 * Stepper motors can not be directly pulsed from FPGA
 * In your case drivers are also connected in a ring!
 */
#include <TMCStepper.h>
#include<iostream>

#define CS_PIN           RPI_BPLUS_GPIO_J8_26  // Chip select                         GPIO7
#define SW_MOSI          RPI_BPLUS_GPIO_J8_38  // Software Master Out Slave In (MOSI) GPIO20
#define SW_MISO          RPI_BPLUS_GPIO_J8_35  // Software Master In Slave Out (MISO) GPIO19
#define SW_SCK           RPI_BPLUS_GPIO_J8_40  // Software Slave Clock (SCK)          GPIO21
#define EN_PIN           RPI_BPLUS_GPIO_J8_11  // Enable pin motor gpio 17

#define R_SENSE 0.11f // Match to your driver
                      // SilentStepStick series use 0.11
                      // UltiMachine Einsy and Archim2 boards use 0.2
                      // Panucatt BSD2660 uses 0.1
                      // Watterott TMC5160 uses 0.075


// chain_length is defined in TMCStepper class and has been modified
// by changing original files, note that chain lenght is also changed by passing the one with the largest index
int8_t x_index=1;
int8_t y_index=2;
int8_t z_index=3;
TMC2130Stepper zdriver(CS_PIN, R_SENSE, SW_MOSI, SW_MISO, SW_SCK, z_index);
TMC2130Stepper ydriver(CS_PIN, R_SENSE, SW_MOSI, SW_MISO, SW_SCK, y_index);
TMC2130Stepper xdriver(CS_PIN, R_SENSE, SW_MOSI, SW_MISO, SW_SCK, x_index); // Software SPI
//int8_t xdriver.chain_length = 3;

int main() {
  std::cout << "Starting program\n";
  if(!bcm2835_init())
  {
      std::cout << "Failed bcm2835 init\n";
      return 1;
  }
  bcm2835_gpio_fsel(EN_PIN, BCM2835_GPIO_FSEL_OUTP);
  //pinMode(10, OUTPUT);
  //pinMode(STEP_PIN, OUTPUT);
  //pinMode(DIR_PIN, OUTPUT);
  bcm2835_gpio_write(EN_PIN, LOW);      // Enable driver in hardware

                                  // Enable one according to your setup
  //xdriver.defaults();                    // SPI drivers
//SERIAL_PORT.begin(115200);      // HW UART drivers
//driver.beginSerial(115200);     // SW UART drivers

// x driver
   xdriver.begin();                 //  SPI: Init CS pins and possible SW SPI pins
                                   // UART: Init SW UART (if selected) with default 115200 baudrate
   xdriver.toff(5);                 // Enables driver in software
   xdriver.rms_current(600);        // Set motor RMS current
   xdriver.microsteps(16);          // Set microsteps to 1/16th
   xdriver.en_pwm_mode(true);       // Toggle stealthChop on TMC2130/2160/5130/5160

// y driver
   ydriver.begin();
   ydriver.toff(5); 
   ydriver.rms_current(600); 
   ydriver.microsteps(16);
   ydriver.en_pwm_mode(true);

// z driver
   zdriver.begin();
   zdriver.toff(5); 
   zdriver.rms_current(600); 
   zdriver.microsteps(16);
   zdriver.en_pwm_mode(true);


   uint8_t result = xdriver.test_connection();
   if (result) {
        std::cout << "Failed\n";
        switch(result) {
            case 1: std::cout << "Loose connection\n"; break;
            case 2: std::cout << "No power\n"; break;
        }
    }
    else{
        std::cout << "Connection succeeded\n";
    }
    bcm2835_close();
// //driver.en_spreadCycle(false);   // Toggle spreadCycle on TMC2208/2209/2224
//   driver.pwm_autoscale(true);     // Needed for stealthChop
    return 0;
}

// bool shaft = false;

// void loop() {
//   // Run 5000 steps and switch direction in software
//   //   for (uint16_t i = 5000; i>0; i--) {
//   //     digitalWrite(STEP_PIN, HIGH);
//   //     delayMicroseconds(160);
//   //     digitalWrite(STEP_PIN, LOW);
//   //     delayMicroseconds(160);
//   //   }
//   shaft = !shaft;
//   xdriver.shaft(shaft);
// }
