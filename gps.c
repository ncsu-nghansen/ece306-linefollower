#include "msp430.h"
#include "macros.h"
#include "functions.h"

char GpsPacket[64], Lat[16], Lon[16];



void init_gps(void)
{
    PJOUT &= ~GPS_RESET;

    waitMsec(GPS_WAIT);
    PJOUT |= GPS_RESET;

    while(!(PJIN & GPS_PWRCHK))
    {
        waitMsec(GPS_WAIT);
        PJOUT |= GPS_PWRCNTL;
        waitMsec(GPS_WAIT);
        PJOUT &= ~GPS_PWRCNTL;
    }
    
    for(int i = 0; i < sizeof GpsPacket; i++)
		GpsPacket[i] = 0x00;
    for(int i = 0; i < sizeof Lat; i++)
    {
		Lat[i] = ' ';
		Lon[i] = ' ';
    }
}

/*char ReadGpsPacket(void)
{
    gpsBuf_R %= sizeof GpsPacketBuffer;
  
    if(gpsBuf_R == gpsBuf_W)
      return 0xFF;
    
    return GpsPacketBuffer[gpsBuf_R++];
}

void WriteGpsPacket(char c)
{
    gpsBuf_W %= sizeof GpsPacketBuffer;
    GpsPacketBuffer[gpsBuf_W++] = c;
}
*/
void GpsPacketChk(void)
{
    char firstChar = readSerial();
    char isGPRMC = 0, isGPGGA = 0;
  
    if(firstChar == 0xFF)
		return;
    
    if(firstChar != '$')
    {
		GpsPacketChk();
		return;
    }
    
    for(int i = 0; i < sizeof GpsPacket; GpsPacket[i++] = 0x00); //Empties GpsPacket
    
    for(int i = 0; i < sizeof GpsPacket; i++) //Fills GpsPacket
		GpsPacket[i] = readSerial();
    
    if(GpsPacket[3] == 'M' && GpsPacket[4] == 'C')
		isGPRMC = 1;
    
    if(GpsPacket[3] == 'G' && GpsPacket[4] == 'A')
		isGPGGA = 1;    
    
    if(isGPRMC)
    {
		int ci = 0;
		while(GpsPacket[ci++] != ','); //Ends after 1st comma
		while(GpsPacket[ci++] != ','); //Ends after 2nd comma
		
		if(GpsPacket[ci] != 'A')
		{
			Lat[15] = GpsPacket[ci];		  
			return;
		}
		
		for(int i = 0; i < sizeof Lat; i++) // if we get here, valid packet
		{
			Lat[i] = ' ';
			Lon[i] = ' ';
		}
                
                Lat[0] = 'L', Lat[1] = 'a', Lat[2] = 't', Lat[3] = ':';
               		
		while(GpsPacket[ci++] != ','); //Ends after 3rd comma    
		for(int i = 4; i < 6 && GpsPacket[ci] != ','; i++, ci++)
			Lat[i] = GpsPacket[ci]; 			
		Lat[6] = ' '; //degree sign
		
		for(int i = 7; i < sizeof Lat && GpsPacket[ci] != ','; i++, ci++) //ends before or on 4th comma
			Lat[i] = GpsPacket[ci];
		
		
		while(GpsPacket[ci++] != ','); //Ends after 4th comma
		Lat[15] = GpsPacket[ci];  //N or S
			
		
                Lon[0] = 'L', Lon[1] = 'o', Lon[2] = 'n', Lon[3] = ':';
		
		while(GpsPacket[ci++] != ','); //Ends after 5nd comma
		for(int i = 4; i < 7 && GpsPacket[ci] != ','; i++, ci++) 
			Lon[i] = GpsPacket[ci];
		Lon[7] = ' '; //degree sign
		
		for(int i = 8; i < sizeof Lon && GpsPacket[ci] != ','; i++, ci++)
			Lon[i] = GpsPacket[ci];		
		
    
		while(GpsPacket[ci++] != ','); //Ends after 6th comma
		Lon[15] = GpsPacket[ci]; //E or W
    }
    
    /*if(isGPGGA)
    {
    int ci = 0;
    while(GpsPacket[ci++] != ',' && GpsPacket[ci++] != 0xFF); //Ends after 1st comma
    
    if(GpsPacket[ci] == ',' || GpsPacket[ci] == 0xFF)
      return;
    
    while(GpsPacket[ci++] != ','); //Ends after 2nd comma
    
    while(GpsPacket[ci++] != ','); //Ends after 3rd comma
    
    for(int i = 0; i < sizeof Lat && GpsPacket[ci] != ','; i++, ci++) //Ends at 2nd Comma
      Lat[i] = GpsPacket[ci]; 
    
    while(GpsPacket[ci++] != ','); //Ends after 4th comma
    Lat[15] = GpsPacket[ci];  //N or S
        
    while(GpsPacket[ci++] != ','); //Ends after 5nd comma
    for(int i = 0; i < sizeof Lon && GpsPacket[ci] != ','; i++, ci++) 
      Lon[i] = GpsPacket[ci];
    
    while(GpsPacket[ci++] != ','); //Ends after 6th comma
    Lon[15] = GpsPacket[ci]; //E or W
    } */ 
}