#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>

void display_version(void);		// Read and display USB-ISS module information
void set_i2c_mode(void);		// Set the USB-ISS into I2C mode, 400KHz clock		
void waccel(void);
void wmagne(void);
void wgyro(void);
void rsensors(void);

int fd;	
unsigned char sbuf[20];			// serial buffer for r/w
unsigned char bot[1];
unsigned char error = 0x00;		// Byte used to indicate errors

int main(int argc, char *argv[])
{
	if(argc != 1)
		printf("** Incorrect input! **\n\n");
	else
	{
		struct termios defaults;							// to store innitial default port settings
		struct termios config;								// These will be our new settings
		const char *device = "/dev/ttyACM0";
		fd = open(device, O_RDWR | O_NOCTTY);
		if(fd == -1) {
  			printf( "failed to open port\n" );
		} else {
			if (tcgetattr(fd, &defaults) < 0) perror("tcgetattr");  		// Grab snapshot of current settings  for port
			cfmakeraw(&config);							// make options for raw data
			if (tcsetattr(fd, TCSANOW, &config) < 0) perror("tcsetattr config");   	// Set options for port
		
	 		display_version();
			set_i2c_mode();
			waccel();
			wmagne();
			wgyro();
			rsensors();
			if (tcsetattr(fd, TCSANOW, &defaults) < 0) perror("tcsetattr default");	// Restore port default before closing
		}
		close(fd);
	}
	return 0;
}	

void display_version(void)
{
	sbuf[0] = 0x5A; 						// USB_ISS byte
	sbuf[1] = 0x01;							// Software return byte

	if (write(fd, sbuf, 2) < 0) perror("display_version write");	// Write data to USB-ISS
	if (tcdrain(fd) < 0) perror("display_version tcdrain");
	if (read(fd, sbuf, 3) < 0) perror("display_version read");	// Read data back from USB-ISS, module ID and software version

	printf("USB-ISS Module ID: %u \n", sbuf[0]);
	printf("USB-ISS Software v: %u \n\n", sbuf[1]);
}

void set_i2c_mode(void)
{
	sbuf[0] = 0x5A;							// USB_ISS command
	sbuf[1] = 0x02;							// Set mode
	sbuf[2] = 0x70;							// Set mode to 400KHz I2C
	sbuf[3] = 0x0A;							// Spare pins set to Digital Output

	if (write(fd, sbuf, 4) < 0) perror("set_i2c_mode write");	// Write data to USB-ISS
	if (tcdrain(fd) < 0) perror("set_i2c_mode tcdrain");
	if (read(fd, sbuf, 2) < 0) perror("set_i2c_mode read");		// Read back error byte
	if(sbuf[0] != 0xFF)						// If first returned byte is not 0xFF then an error has occured
	{
		printf("**set_i2c_mode: Error setting I2C mode!**\n\n");
		error = 0xFF;						// Set error byte
	}
}
void waccel(void){
	sbuf[0] = 0x55;
	sbuf[1] = 0x32;
	sbuf[2] = 0x20;
	sbuf[3] = 0x01;
	sbuf[4] = 0x47;

	if (write(fd, sbuf, 5) < 0) perror("do_range write");		// Write data to USB-ISS
	if (tcdrain(fd) < 0) perror("do_range tcdrain");
	if (read(fd,  sbuf, 1) < 0) perror("accel read");		// Read back error byte	

}

void wmagne(void){
	sbuf[0] = 0x55;
	sbuf[1] = 0x3C;
	sbuf[2] = 0x0;
	sbuf[3] = 0x01;
	sbuf[4] = 0x98;

	if (write(fd, sbuf, 5) < 0) perror("do_range write");		// Write data to USB-ISS
	if (tcdrain(fd) < 0) perror("do_range tcdrain");
	if (read(fd,  sbuf, 1) < 0) perror("accel read");		// Read back error byte	

	sbuf[0] = 0x55;
	sbuf[1] = 0x3C;
	sbuf[2] = 0x01;
	sbuf[3] = 0x01;
	sbuf[4] = 0x80;

	if (write(fd, sbuf, 5) < 0) perror("do_range write");		// Write data to USB-ISS
	if (tcdrain(fd) < 0) perror("do_range tcdrain");
	if (read(fd,  sbuf, 1) < 0) perror("accel read");		// Read back error byte	

	sbuf[0] = 0x55;
	sbuf[1] = 0x3C;
	sbuf[2] = 0x02;
	sbuf[3] = 0x01;
	sbuf[4] = 0x0;

	if (write(fd, sbuf, 5) < 0) perror("do_range write");		// Write data to USB-ISS
	if (tcdrain(fd) < 0) perror("do_range tcdrain");
	if (read(fd,  sbuf, 1) < 0) perror("accel read");		// Read back error byte		

}

void wgyro(void){
	sbuf[0] = 0x55;
	sbuf[1] = 0xD6;
	sbuf[2] = 0x20;
	sbuf[3] = 0x01;
	sbuf[4] = 0xF;

	if (write(fd, sbuf, 5) < 0) perror("do_range write");		// Write data to USB-ISS
	if (tcdrain(fd) < 0) perror("do_range tcdrain");
	if (read(fd,  sbuf, 1) < 0) perror("accel read");		// Read back error byte


}

void rsensors(void){
	float xaxis, yaxis, zaxis, x_acc0, x_acc1, y_acc0, y_acc1, z_acc0, z_acc1;		//Accelerometer data decl.
	int mxaxis0, mxaxis1, myaxis0, myaxis1, mzaxis0, mzaxis1;				//Magnetometer data decl.
	int gxaxis0, gxaxis1, gxaxisR, gyaxis0, gyaxis1, gyaxisR, gzaxis0, gzaxis1, gzaxisR;	//Gyroscope data decl. 

	printf(" \n >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   DATOS DE LOS SENSORES   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> \n");
	printf("\n    Acelerómetro			    Magnetómetro		              Giroscopio		  Botones \n");
	printf("\n  X        Y        Z			 X        Y        Z			 X        Y        Z		  B1   B2 \n");
	usleep(700000);
	while(1){
		//Acelerómetro
		//Acc X axis		
		sbuf[0] = 0x55;
		sbuf[1] = 0x33;
		sbuf[2] = 0x29;
		sbuf[3] = 0x01;

		usleep(10000);
		if (write(fd, sbuf, 4) < 0) perror("raccel write");		// Write data to USB-ISS
		if (tcdrain(fd) < 0) perror("raccel tcdrain");
		if (read(fd,  sbuf, 3) < 0) perror("raccel read");		// Read back error byte	
	
		xaxis = sbuf[0] - 256;
		if(sbuf[0] > 127){
			x_acc0 = xaxis/64;	
			printf("%.3f ", x_acc0);
		}
		else{
			x_acc1 = sbuf[0]/64;
			printf("%.3f ", x_acc1);
		}

		//Acc Y axis
		sbuf[0] = 0x55;
		sbuf[1] = 0x33;
		sbuf[2] = 0x2B;
		sbuf[3] = 0x01;

		usleep(10000);
		if (write(fd, sbuf, 4) < 0) perror("raccel write");		// Write data to USB-ISS
		if (tcdrain(fd) < 0) perror("raccel tcdrain");
		if (read(fd,  sbuf, 3) < 0) perror("raccel read");		// Read back error byte	
	
		yaxis = sbuf[0] - 256;
		if(sbuf[0] > 127){
			y_acc0 = yaxis/64;	
			printf(" %.3f ", y_acc0);
		}
		else{
			y_acc1 = sbuf[0]/64;
			printf(" %.3f ", y_acc1);
		}

		//Acc Z axis
		sbuf[0] = 0x55;
		sbuf[1] = 0x33;
		sbuf[2] = 0x2D;
		sbuf[3] = 0x01;

		usleep(10000);
		if (write(fd, sbuf, 4) < 0) perror("raccel write");		// Write data to USB-ISS
		if (tcdrain(fd) < 0) perror("raccel tcdrain");
		if (read(fd,  sbuf, 3) < 0) perror("raccel read");		// Read back error byte	
	
		zaxis = sbuf[0] - 256;
		if(sbuf[0] > 127){
			z_acc0 = zaxis/64;	
			printf(" %.3f ", z_acc0);
		}
		else{
			z_acc1 = sbuf[0]/64;
			printf(" %.3f ", z_acc1);
		}

		
		usleep(100000);

		//Magnetómetro
		//Mag X axis
		sbuf[0] = 0x55;
		sbuf[1] = 0x3D;
		sbuf[2] = 0x03;
		sbuf[3] = 0x02;

		usleep(10000);
		if (write(fd, sbuf, 4) < 0) perror("raccel write");		// Write data to USB-ISS
		if (tcdrain(fd) < 0) perror("raccel tcdrain");
		if (read(fd,  sbuf, 3) < 0) perror("raccel read");		// Read back error byte

		mxaxis0 = (sbuf[0] * 256) + sbuf[1];
		mxaxis1 = mxaxis0 - 65536;

		if(sbuf[0] > 127){	
			printf("\t\t\t%d", mxaxis1);
		}
		else{
			printf("\t\t\t%d", mxaxis0);
		}

		//Mag Y axis
		sbuf[0] = 0x55;
		sbuf[1] = 0x3D;
		sbuf[2] = 0x05;
		sbuf[3] = 0x02;

		usleep(10000);
		if (write(fd, sbuf, 4) < 0) perror("raccel write");		// Write data to USB-ISS
		if (tcdrain(fd) < 0) perror("raccel tcdrain");
		if (read(fd,  sbuf, 3) < 0) perror("raccel read");		// Read back error byte

		myaxis0 = (sbuf[0] * 256) + sbuf[1];
		myaxis1 = myaxis0 - 65536;

		if(sbuf[0] > 127){	
			printf("\t%d", myaxis1);
		}
		else{
			printf("\t%d", myaxis0);
		}

		//Mag Z axis
		sbuf[0] = 0x55;
		sbuf[1] = 0x3D;
		sbuf[2] = 0x07;
		sbuf[3] = 0x02;

		usleep(10000);
		if (write(fd, sbuf, 4) < 0) perror("raccel write");		// Write data to USB-ISS
		if (tcdrain(fd) < 0) perror("raccel tcdrain");
		if (read(fd,  sbuf, 3) < 0) perror("raccel read");		// Read back error byte

		mzaxis0 = (sbuf[0] * 256) + sbuf[1];
		mzaxis1 = mzaxis0 - 65536;

		if(sbuf[0] > 127){	
			printf(" \t%d", mzaxis1);
		}
		else{
			printf(" \t%d", mzaxis0);
		}

		//Giroscopio	
		usleep(100000);

		//Gyro X axis
		sbuf[0] = 0x55;
		sbuf[1] = 0xD7;
		sbuf[2] = 0x29;
		sbuf[3] = 0x01;

		usleep(10000);
		if (write(fd, sbuf, 4) < 0) perror("raccel write");		// Write data to USB-ISS
		if (tcdrain(fd) < 0) perror("raccel tcdrain");
		if (read(fd,  sbuf, 3) < 0) perror("raccel read");		// Read back error byte	
	
		gxaxis0 = sbuf[0];

		sbuf[0] = 0x55;
		sbuf[1] = 0xD7;
		sbuf[2] = 0x28;
		sbuf[3] = 0x01;
		
		usleep(10000);
		if (write(fd, sbuf, 4) < 0) perror("raccel write");		// Write data to USB-ISS
		if (tcdrain(fd) < 0) perror("raccel tcdrain");
		if (read(fd,  sbuf, 3) < 0) perror("raccel read");		// Read back error byte	
	
		gxaxis1 = sbuf[0];
	
		gxaxisR = (gxaxis0 * 256 + gxaxis1);
		if(gxaxisR > 32767){
			gxaxisR -= 65536;
			printf("\t\t\t%d", gxaxisR);
		}
		else{
			printf("\t\t\t%d", gxaxisR);
		}

		//Gyro Y axis
		sbuf[0] = 0x55;
		sbuf[1] = 0xD7;
		sbuf[2] = 0x2B;
		sbuf[3] = 0x01;

		usleep(10000);
		if (write(fd, sbuf, 4) < 0) perror("raccel write");		// Write data to USB-ISS
		if (tcdrain(fd) < 0) perror("raccel tcdrain");
		if (read(fd,  sbuf, 3) < 0) perror("raccel read");		// Read back error byte	
	
		gyaxis0 = sbuf[0];
	
		sbuf[0] = 0x55;
		sbuf[1] = 0xD7;
		sbuf[2] = 0x2A;
		sbuf[3] = 0x01;
	
		usleep(10000);
		if (write(fd, sbuf, 4) < 0) perror("raccel write");		// Write data to USB-ISS
		if (tcdrain(fd) < 0) perror("raccel tcdrain");
		if (read(fd,  sbuf, 3) < 0) perror("raccel read");		// Read back error byte	
	
		gyaxis1 = sbuf[0];
	
		gyaxisR = (gyaxis0 * 256 + gyaxis1);
		if(gyaxisR > 32767){
			gyaxisR -= 65536;
			printf("\t%d", gyaxisR);
		}
		else{
			printf("\t%d", gyaxisR);
		}

	
		//Gyro Z axis
		sbuf[0] = 0x55;
		sbuf[1] = 0xD7;
		sbuf[2] = 0x2D;
		sbuf[3] = 0x01;
		
		usleep(10000);
		if (write(fd, sbuf, 4) < 0) perror("raccel write");		// Write data to USB-ISS
		if (tcdrain(fd) < 0) perror("raccel tcdrain");
		if (read(fd,  sbuf, 3) < 0) perror("raccel read");		// Read back error byte	
	
		gzaxis0 = sbuf[0];
	
		usleep(700000);
		sbuf[0] = 0x55;
		sbuf[1] = 0xD7;
		sbuf[2] = 0x2C;
		sbuf[3] = 0x01;
	
		usleep(10000);
		if (write(fd, sbuf, 4) < 0) perror("raccel write");		// Write data to USB-ISS
		if (tcdrain(fd) < 0) perror("raccel tcdrain");
		if (read(fd,  sbuf, 3) < 0) perror("raccel read");		// Read back error byte	
	
		gzaxis1 = sbuf[0];

		gzaxisR = (gzaxis0 * 256 + gzaxis1);
		if(gzaxisR > 32767){
			gzaxisR -= 65536;
			printf("      %d", gzaxisR);
		}
		else{
			printf("      %d", gzaxisR);
		}
		
		usleep(30000);

		//Botones
		bot[0] = 0x64;
		bot[1] = 0x01;
		if (write(fd, bot, 4) < 0) perror("do_range write");		// Write data to USB-ISS
		if (read(fd,  bot, 3) < 0) perror("do_range read");		// Read back error byte	
		int boton = bot[0];
		if(boton == 12){
			printf("\t\t OFF   OFF\n \n");	
		}
		else if(boton == 13){
			printf("\t\t ON   OFF\n \n");
		}
		else if(boton == 14){
			printf("\t\t OFF   ON\n \n");
		}
		else {
			printf("\t\t ON   ON\n \n");
		}
		
	}
}

