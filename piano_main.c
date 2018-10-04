//JMP CONCLUSIONS
//FINAL PROJECT - PIANO

//Constants
#define F_CPU 16000000UL

//Libraries
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//Buzzer Configurations
#define BUZZER_DDR  	DDRB
#define BUZZER_PORT		PORTB
#define BUZZER_PIN		3

//Button Configurations
#define BUTTON_DDR		DDRD
#define BUTTON_PORT		PORTD
#define BUTTON_PIN		PIND
#define BUTTON_1		0
#define BUTTON_2		1
#define BUTTON_3		2
#define BUTTON_4		3
#define BUTTON_5		4
#define BUTTON_6		5
#define BUTTON_7		6
#define BUTTON_8		7

//Music Note Configurations
#define C6	0.4775
#define D6	0.4255
#define E6	0.3790
#define F6	0.3579
#define G6	0.3152
#define A6	0.2840
#define Bb6 0.2680
#define B6	0.2530
#define C7	0.2388

//Function Prototypes
unsigned char get_key_press( unsigned char key_mask );
void init_timers(void);
void init_io(void);
void Note_C6(float duration);
void Note_D6(float duration);
void Note_E6(float duration);
void Note_F6(float duration);
void Note_G6(float duration);
void Note_A6(float duration);
void Note_Bb6(float duration);
void Note_B6(float duration);
void Note_C7(float duration);

//Global Debounce Variables
unsigned char debounce_cnt = 0;
volatile unsigned char key_press;
unsigned char key_state;


int main(void)
{
	//Start System Timer
	init_timers();
	//Initialize Button Inputs
	init_io();       
	
	while(1){
		
		if( get_key_press( 1<<BUTTON_1 ))
		{
			Note_C6(400);
		}
		
		if( get_key_press( 1<<BUTTON_2 ))
		{
			Note_D6(400);
		}
		
		if( get_key_press( 1<<BUTTON_3 ))
		{
			Note_E6(400);
		}
		
		if( get_key_press( 1<<BUTTON_4 ))
		{
			Note_F6(400);
		}
		
		if( get_key_press( 1<<BUTTON_5 ))
		{
			Note_G6(500);
		}
		
		if( get_key_press( 1<<BUTTON_6 ))
		{
			Note_A6(500);
		}
		
		if( get_key_press( 1<<BUTTON_7 ))
		{
			Note_B6(600);
		}
		
		if( get_key_press( 1<<BUTTON_8 ))
		{
			Note_C7(600);
		}
	}
	
}

//Debounce Function Definitions
unsigned char get_key_press( unsigned char key_mask )
{
	cli();           
	key_mask &= key_press;    
	key_press ^= key_mask;   
	sei();  
	          
	return key_mask;
}

void init_timers(void)
{
	cli();           
	TCCR1B |= 1<<CS10;
	TIMSK1 |= 1<<TOIE1;
	sei();          
}

void init_io(void)
{
	//Set button pins as input & enable pull-up resistors
	BUTTON_DDR &= ~((1<<BUTTON_1) | (1<<BUTTON_2) | (1<<BUTTON_3) | (1<<BUTTON_4) | (1<<BUTTON_5) | (1<<BUTTON_6) | (1<<BUTTON_7)); 
	BUTTON_PORT |= (1<<BUTTON_1) | (1<<BUTTON_2) | (1<<BUTTON_3) | (1<<BUTTON_4) | (1<<BUTTON_5) | (1<<BUTTON_6) | (1<<BUTTON_7);   
}

//Timer Interrupt Definition
ISR(TIMER1_OVF_vect)           
{
	static unsigned char ct0, ct1;
	unsigned char i;
	
	TCNT1 = 0;
	
	i = key_state ^ ~BUTTON_PIN;
	ct0 = ~( ct0 & i );         
	ct1 = ct0 ^ (ct1 & i);      
	i &= ct0 & ct1;             
	key_state ^= i;             
	key_press |= key_state & i; 
}

//Note Definitions
void Note_C6(float duration)
{
	long int i,cycles;
	float wavelength = 1.25;
	
	cycles=duration/wavelength;

	BUZZER_DDR |= (1 << BUZZER_PIN);

	for (i=0;i<cycles;i++)
	{
		_delay_ms(C6);
		BUZZER_PORT |= (1 << BUZZER_PIN);
		_delay_ms(C6);
		BUZZER_PORT &= ~(1 << BUZZER_PIN);
	}

	return;
}

void Note_D6(float duration)
{
	long int i,cycles;
	float wavelength = 1.25;
	
	cycles=duration/wavelength;

	BUZZER_DDR |= (1 << BUZZER_PIN);

	for (i=0;i<cycles;i++)
	{
		_delay_ms(D6);
		BUZZER_PORT |= (1 << BUZZER_PIN);
		_delay_ms(D6);
		BUZZER_PORT &= ~(1 << BUZZER_PIN);
	}

	return;
}

void Note_E6(float duration)
{
	long int i,cycles;
	float wavelength = 1.25;
	
	cycles=duration/wavelength;

	BUZZER_DDR |= (1 << BUZZER_PIN);

	for (i=0;i<cycles;i++)
	{
		_delay_ms(E6);
		BUZZER_PORT |= (1 << BUZZER_PIN);
		_delay_ms(E6);
		BUZZER_PORT &= ~(1 << BUZZER_PIN);
	}

	return;
}

void Note_F6(float duration)
{
	long int i,cycles;
	float wavelength = 1.25;
	
	cycles=duration/wavelength;

	BUZZER_DDR |= (1 << BUZZER_PIN);

	for (i=0;i<cycles;i++)
	{
		_delay_ms(F6);
		BUZZER_PORT |= (1 << BUZZER_PIN);
		_delay_ms(F6);
		BUZZER_PORT &= ~(1 << BUZZER_PIN);
	}

	return;
}

void Note_G6(float duration)
{
	long int i,cycles;
	float wavelength = 1.25;
	
	cycles=duration/wavelength;

	BUZZER_DDR |= (1 << BUZZER_PIN);

	for (i=0;i<cycles;i++)
	{
		_delay_ms(G6);
		BUZZER_PORT |= (1 << BUZZER_PIN);
		_delay_ms(G6);
		BUZZER_PORT &= ~(1 << BUZZER_PIN);
	}

	return;
}

void Note_A6(float duration)
{
	long int i,cycles;
	float wavelength = 1.25;
	
	cycles=duration/wavelength;

	BUZZER_DDR |= (1 << BUZZER_PIN);

	for (i=0;i<cycles;i++)
	{
		_delay_ms(A6);
		BUZZER_PORT |= (1 << BUZZER_PIN);
		_delay_ms(A6);
		BUZZER_PORT &= ~(1 << BUZZER_PIN);
	}

	return;
}

void Note_Bb6(float duration)
{
	long int i,cycles;
	float wavelength = 1.25;
	
	cycles=duration/wavelength;

	BUZZER_DDR |= (1 << BUZZER_PIN);

	for (i=0;i<cycles;i++)
	{
		_delay_ms(Bb6);
		BUZZER_PORT |= (1 << BUZZER_PIN);
		_delay_ms(Bb6);
		BUZZER_PORT &= ~(1 << BUZZER_PIN);
	}

	return;
}

void Note_B6(float duration)
{
	long int i,cycles;
	float wavelength = 1.25;
	
	cycles=duration/wavelength;

	BUZZER_DDR |= (1 << BUZZER_PIN);

	for (i=0;i<cycles;i++)
	{
		_delay_ms(B6);
		BUZZER_PORT |= (1 << BUZZER_PIN);
		_delay_ms(B6);
		BUZZER_PORT &= ~(1 << BUZZER_PIN);
	}

	return;
}

void Note_C7(float duration)
{
	long int i,cycles;
	float wavelength = 1.25;
	
	cycles=duration/wavelength;

	BUZZER_DDR |= (1 << BUZZER_PIN);

	for (i=0;i<cycles;i++)
	{
		_delay_ms(C7);
		BUZZER_PORT |= (1 << BUZZER_PIN);
		_delay_ms(C7);
		BUZZER_PORT &= ~(1 << BUZZER_PIN);
	}

	return;
}