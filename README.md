# Interrupt-Driven 8-Button Piano & Music Box

#### Contributing Members:
- Andrew Cleary
- Jake Wolf
- Celine Malawi
- Dennis Dumont

## Abstract
The principal goal of our project was to design and build an 8-button piano & music player – two different implementations of the same circuit. As a piano, our circuit utilizes the attached buzzer to generate tones C6 through C7; this was achieved through the use and development of an interrupt driven system. As a music player we utilized the same buttons, with each representing a different, pre-programmed song. Both programs for our circuit were written and debugged in the C programming language within Atmel Studio 7.0. Furthermore, we continued to use the Xplained Mini ATMega328P microcontroller from the previous labs in our final project implementation. We faced several setbacks when implementing our planned design including, but not limited to, configuring the GPIO pins to accept an input from the buttons, eliminating the rotary switch, and generating a tone from the connected buzzer. Nevertheless, we were able to overcome these hurdles and implement our design as intended with only small modifications to the circuit and code.

## Design
When coming up with the design of the piano, we wanted to be able to cover one octave of naturals, the white keys on a piano, and be able to change the octave that is being played, as a standard piano has seven. As such, we would need eight pushbuttons to serve as our keys and either a seven or eight position rotary switch to be able to change the octave. LEDs were also implemented after the switches to show the user which tone is played from the buzzer.<br />

The switch and LED series was created by putting 5V on one leg of the switch and a 220Ω resistor on the opposite corner. This resistor is then in series with the anode of the LED and a wire connecting to the ATMega328P board. Another 220Ω resistor is placed between the cathode of the LED and connected to ground. The configuration of the LED is key as current can only flow from the anode to the cathode of a diode. In the initial design, there was not a resistor between the cathode and ground. The LED would light up, but a sound would not consistently come from the buzzer. Placing the second resistor resulted in a tone being played every time the button was pressed. The LED also served to let us know when the tone would be played. The signal that the board receives from pressing the button is a square wave with either a value of 1 or 0. The LED is on when the value is 1 and off when it is 0, the speaker plays the tone during the falling edge of the wave. In other words, when the wave drops from 1 to 0, the proper tone is played. These are all plugged into the pins PD0-PD7.<br />

The rotary switch was placed on a separate board from the buttons due to a lack of space and included the buzzer. The original intention of the switch was to be able to vary the octave so that any natural between C notes could be played. The first position would cover the first octave, starting at C1 and ending at C2. The second would cover C2 to C3, and so on up to the final octave covering C7 to C8. Due to the limitations of the buzzer a frequency of 31Hz or lower could not be made, C1 is 32.7 Hz meaning that it would be the lowest tone we could possibly generate. The rotary switch had each position connected to a different value resistor to generate different voltage drops. We would then create a resistor ladder with the output going into an analog pin. However, due to limitations in our tone output, we were unable to incorporate this system into our final project. The buzzer simply has the positive end connected to the output from our board and the negative end to ground.

## Calculations
To generate the specific note based off their given frequency, certain calculations were needed to find their respected macro value. Starting with their frequency (f), the wavelength (w) can be found by w = (1/f)*1000. Next, the half period is found by dividing the wavelength by 2. Finally, the half period is truncated to its fourth decimal place resulting in the needed macro value.

## Implementation
In the development of the 8-button piano, there were three main areas of developmental concern: port configuration, utilizing interrupt driven inputs, and generating the desired tone.

#### Port Configuration
The first step in configuring the program to work with the constructed circuit was to identify which pins would need to be configured as inputs and which would need to be configured as outputs. For the 8 buttons making up the piano, each was wired into one of the 8 pins of PORTD, PD0 through PD7 respectively. As a result of this, each was configured as an input within the init_io() function which was called in main immediately after starting the timer. Macros defined at the beginning of the source code were used to designate the direction, ports, and pins for the buttons. This significantly increased the modularity of the code, allowing input wires to be easily switched to different pins on the board.<br />

The buzzer was configured similar to the buttons, with the exception of being designated as an output rather than an input. Nevertheless, while macros were used to identify the ports and pins of the buzzer, they were not used to configure the buzzer at the same time as the buttons, but were rather configured within the functions called to generate each tone. This construction will be further expounded upon in “Tone Generation”.

#### Interrupt-Driven Inputs
One of the key design features of the 8-button piano is that it is driven by an interrupt system that polls every 8 milliseconds. Rather than sitting in an infinite loop continuously checking each pin, an interrupt was generated every time a button was pressed. This significantly improved the performance of the 8-button piano and decreased the number of idle clock cycles.<br />

Building off of the in-class button handling example, the code for the 8-button piano utilizes a modified version interface with all 8 pins of PORTD. Two of the most important methods in achieving the interrupt driven interface were the init_timer() and get_key_press() methods. The function that initializes the timer does so by first clearing the global interrupt flag, then sets bit 0 (CS10) of TC1 Control Register B to 1, which enables the clock with no prescaling. It is important to note that the microcontroller is using normal waveform generation mode rather than a variant of pulse width modulation. After enabling the clock, the function makes a further modification to the TC1 Interrupt Mask Register by setting bit 0 (TOIE) to 1, which enables overflow interrupt. Because of this, every time there is overflow, an interrupt vector is generated. When executed, the interrupt handler checks the status of each of the pins to indicate whether or not each pin received an input from the press of a button. After enabling the interrupt, the global interrupt flag is set through the use of the sei() function, the init_timer() function returns to main.<br />

Within main, an infinite while loop has a series of if statements that call the get_key_press() function for each button. If a button has been pressed, then the corresponding interrupt vector would make a note of such, therefore causing the get_key_press() function to return true for that button. At this point in the code, the respective tone generation method is called.

#### Tone Generation
One of the most difficult initial hurdles was programming the attached buzzer to generate a tone, and from there, be able to adjust this tone to produce a full octave of pitches. The desired range of pitches for the 8-button piano was C6 through C7, inclusive.
The tone generation functions within the 8-button piano program take only one parameter, a float variable denoting the duration of time for that note to be played. Within the function, the buzzer direction, port, and pin are configured appropriately for signal output. After calculating the number of cycles for the for loop by dividing the provided duration by the wavelength of 1.25, two delays of variable time were implemented to control the pitch. Using predefined macro values for each note (as discussed above in "Calculations") we were able to generate each pitch from C6 to C7. The syntax for this adjustment is shown below: 
```c
_delay_ms(C6); 
BUZZER_PORT |= (1 << BUZZER_PIN); 
_delay_ms(C6); 
BUZZER_PORT &= ~(1 << BUZZER_PIN);
```

## Results
Although we were unable to build the piano to be what we had envisioned due to a few limitations, the end result retained the core of the original plan. The piano covered one octave of naturals and would light up an LED when the button was pressed and turn off when the button was released. The LED also showed the user when the tone will be played since the tone is not played until the falling edge of the square wave generated by pressing and releasing the button. This resulted in a piano that could be used to teach a young person or beginner the basics of music.<br />

Additionally, the piano also serves as a music box. A song can be programmed to each button and play upon release of that button. For example, "Happy Birthday" is played upon pressing the second button from the left. Any song that stays within one octave can be played, due to the limitations of the code, but they must be programmed into the board. As seen in the code below, this is done by putting the notes on consecutive lines and placing delays where needed. Anybody with a basic understanding of music who knows how to read a treble clef will have no problem making songs for the music box to play.
