#include <stdio.h>
#include <stdlib.h>
#include <pigpio.h>
#include <time.h>

#define PIN 21	// watch this GPIO

void gpio_perror(const char *s, int n);

static void rising( unsigned gpio, gpioISRFunc_t f ){
	int code = gpioSetISRFunc( gpio, FALLING_EDGE, 0, f );
	if( code >= 0 ) return;
	fprintf( stderr, "GPIO %u ", gpio );
	gpio_perror( "pinwatcher", code );
	exit( 1 );
}

static void timestamp( void ) {
	int seconds, micros;
	int code = gpioTime(PI_TIME_ABSOLUTE, &seconds, &micros);
	if( code != 0 ) {
		gpio_perror( "pinwatcher", code );
		exit( 1 );
	}
	printf("\t%d.%03d\t", seconds, micros/1000);
	time_t t = seconds;
	printf( "%s\n", asctime( gmtime( &t )));
	fflush( stdout );
}

static void event( int gpio, int level, uint32_t tick ) {
	printf( "EVENT" );
	timestamp();
}
	
int main( int argc, char **argv ){

	int code = gpioInitialise();
	if( code < 0 ) {
		gpio_perror( "pinwatcher", code );
		exit( 1 );
	}
	
	printf( "START" );
	timestamp();
		
	rising( PIN, event );
	
	gpioSleep(PI_TIME_RELATIVE, 1000000000, 0);   // The ISR does the work
	
	return 0;		// for fussy compiler
}
	
	
