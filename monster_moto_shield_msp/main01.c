typedef signed   char     int8_t;
typedef unsigned char     uint8_t;

typedef signed   short    int16_t;
typedef unsigned short    uint16_t;

typedef signed   int      int32_t;
typedef unsigned int      uint32_t;


  #define ACC 1
  #define MAG 1
  #define GYRO 1
  #define BARO 1
  #define GPS 0
  #define SONAR 1
 
    #define QUADX
    #define VBAT              // uncomment this line to activate the vbat code


#define  VERSION  220


  #define RC_CHANS 8

static int16_t rcData[RC_CHANS];    // interval [1000;2000]
static int16_t rcCommand[4];        // interval [1000;2000] for THROTTLE and [-500;+500] for ROLL/PITCH/YAW 


volatile uint16_t serialRcValue[RC_CHANS] = {1502, 1502, 1502, 1502, 1502, 1502, 1502, 1502}; 
float alpha = 0.95;
uint8_t paramList[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int16_t absolutedAccZ = 0;
uint8_t flightState = 0;

enum rc {
  ROLL,
  PITCH,
  YAW,
  THROTTLE,
  AUX1,
  AUX2,
  AUX3,
  AUX4
};

enum pid {
  PIDROLL,
  PIDPITCH,
  PIDYAW,
  PIDALT,
  PIDPOS,
  PIDPOSR,
  PIDNAVR,
  PIDLEVEL,
  PIDMAG,
  PIDVEL,     // not used currently
  PIDITEMS
};











/**************************************************************************************/
/***************             test configurations                   ********************/
/**************************************************************************************/
#if COPTERTEST == 1
#elif COPTERTEST == 2
  #define FLYING_WING
  #define BMA020
  #define LCD_TEXTSTAR
  #define VBAT
  #define POWERMETER_SOFT
#elif COPTERTEST == 3
  #define TRI
  #define FREEIMUv035_MS
  #define BUZZER
  #define VBAT
  #define POWERMETER_HARD
  #define LCD_VT100
  #define LCD_TELEMETRY
  #define LCD_TELEMETRY_STEP "01245"
  #define LOG_VALUES 1
  #define SUPPRESS_BARO_ALTHOLD
  #define VARIOMETER 12
#elif COPTERTEST == 4
  #define QUADX
  #define CRIUS_SE
  #define SPEKTRUM 2048
  #define LED_RING
  #define GPS_SERIAL 2
  #define LOG_VALUES 2
  #define CYCLETIME_FIXATED 9000
  #define LOG_PERMANENT 1023
  #define LOG_PERMANENT_SERVICE_LIFETIME 36000
#elif COPTERTEST == 5
  #define HELI_120_CCPM
  #define CRIUS_LITE
  #undef DISABLE_POWER_PIN
  #define RCAUXPIN8
  #define OLED_I2C_128x64
  #define LCD_TELEMETRY
  #define LOG_VALUES 3
  #define DEBUG
  #define SERVO_RFR_160HZ
  #define VBAT
  #define POWERMETER_SOFT
  #define MMGYRO 10
  #define MMGYROVECTORLENGTH 15
  #define GYRO_SMOOTHING {45, 45, 50}
  #define INFLIGHT_ACC_CALIBRATION
  #define LOG_PERMANENT 1023
  #define LOG_PERMANENT_SHOW_AT_STARTUP
  #define LOG_PERMANENT_SHOW_AT_L
  #define LOG_PERMANENT_SERVICE_LIFETIME 36000
#elif defined(COPTERTEST)
  #error "*** this test is not yet defined"
#endif


/**************************************************************************************/
/***************             Proc specific definitions             ********************/
/**************************************************************************************/
// Proc auto detection


  #define PROMICRO


/**************************************************************************************/
/***************             motor and servo numbers               ********************/
/**************************************************************************************/


  #define NUMBER_MOTOR     4


/**************************   atmega328P (Promini)  ************************************/


/**************************  atmega32u4 (Promicro)  ***********************************/
#if defined(PROMICRO)
 
  #if !defined(TEENSY20)
    #define LEDPIN_PINMODE             //
    #define LEDPIN_TOGGLE              PIND |= 1<<5;     //switch LEDPIN state (Port D5)
    #if !defined(PROMICRO10)
      #define LEDPIN_OFF                 PORTD |= (1<<5);
      #define LEDPIN_ON                  PORTD &= ~(1<<5);  
    #endif
  #endif
  
 
    #define BUZZERPIN_PINMODE          DDRD |= (1<<3);
   
      #define BUZZERPIN_ON               PORTD |= 1<<3;
      #define BUZZERPIN_OFF              PORTD &= ~(1<<3); 
    
 
  
  #define USB_CDC_TX                 3
  #define USB_CDC_RX                 2
  
  
  #if !defined(TEENSY20)
    #define PSENSORPIN                A2    // Analog PIN 2 
  #endif
#endif

/**************************  all the Mega types  ***********************************/



// special defines for the Mongose IMU board 
// note: that may be moved to the IMU Orientations because this are board defines .. not Proc

/**********************   Sort the Servos for the most ideal SW PWM     ************************/
// this define block sorts the above slected servos to be in a simple order from 1 - (count of total servos)
// its pretty fat but its the best way i found to get less compiled code and max speed in the ISR without loosing its flexibility


/**************************************************************************************/
/***************      IMU Orientations and Sensor definitions      ********************/
/**************************************************************************************/


//please submit any correction to this list.

  #define MPU6050
  
  
  #define MPU6050_EN_I2C_BYPASS // MAG connected to the AUX I2C bus of MPU6050 
  #undef INTERNAL_I2C_PULLUPS
  #define EXT_MOTOR_RANGE


/**************************************************************************************/
/***************      Multitype decleration for the GUI's          ********************/
/**************************************************************************************/

#if defined(QUADX)
  #define MULTITYPE 3
#endif

/**************************************************************************************/
/***************          Some unsorted "chain" defines            ********************/
/**************************************************************************************/






  #define UART_NUMBER 2

  #define RX_BUFFER_SIZE 256


#define TX_BUFFER_SIZE 128
#define INBUF_SIZE 64

static volatile uint8_t serialHeadRX[UART_NUMBER],serialTailRX[UART_NUMBER];
static uint8_t serialBufferRX[RX_BUFFER_SIZE][UART_NUMBER];
static volatile uint8_t serialHeadTX[UART_NUMBER],serialTailTX[UART_NUMBER];
static uint8_t serialBufferTX[TX_BUFFER_SIZE][UART_NUMBER];
static uint8_t inBuf[INBUF_SIZE][UART_NUMBER];

#define BIND_CAPABLE 0;  //Used for Spektrum today; can be used in the future for any RX type that needs a bind and has a MultiWii module. 

// Multiwii Serial Protocol 0 
#define MSP_VERSION              0

//to multiwii developpers/committers : do not add new MSP messages without a proper argumentation/agreement on the forum
#define MSP_IDENT                100   //out message         multitype + multiwii version + protocol version + capability variable
#define MSP_STATUS               101   //out message         cycletime & errors_count & sensor present & box activation & current setting number
#define MSP_RAW_IMU              102   //out message         9 DOF
#define MSP_SERVO                103   //out message         8 servos
#define MSP_MOTOR                104   //out message         8 motors
#define MSP_RC                   105   //out message         8 rc chan and more
#define MSP_RAW_GPS              106   //out message         fix, numsat, lat, lon, alt, speed, ground course
#define MSP_COMP_GPS             107   //out message         distance home, direction home
#define MSP_ATTITUDE             108   //out message         2 angles 1 heading
#define MSP_ALTITUDE             109   //out message         altitude, variometer
#define MSP_ANALOG               110   //out message         vbat, powermetersum, rssi if available on RX
#define MSP_RC_TUNING            111   //out message         rc rate, rc expo, rollpitch rate, yaw rate, dyn throttle PID
#define MSP_PID                  112   //out message         P I D coeff (9 are used currently)
#define MSP_BOX                  113   //out message         BOX setup (number is dependant of your setup)
#define MSP_MISC                 114   //out message         powermeter trig
#define MSP_MOTOR_PINS           115   //out message         which pins are in use for motors & servos, for GUI 
#define MSP_BOXNAMES             116   //out message         the aux switch names
#define MSP_PIDNAMES             117   //out message         the PID names
#define MSP_WP                   118   //out message         get a WP, WP# is in the payload, returns (WP#, lat, lon, alt, flags) WP#0-home, WP#16-poshold
#define MSP_BOXIDS               119   //out message         get the permanent IDs associated to BOXes

#define MSP_SET_RAW_RC_TINY      150   //in message          4 rc chan
#define MSP_ARM                  151
#define MSP_DISARM               152
#define MSP_TRIM_UP              153
#define MSP_TRIM_DOWN            154
#define MSP_TRIM_LEFT            155
#define MSP_TRIM_RIGHT           156
#define MSP_TRIM_UP_FAST         157
#define MSP_TRIM_DOWN_FAST       158
#define MSP_TRIM_LEFT_FAST       159
#define MSP_TRIM_RIGHT_FAST      160

#define MSP_READ_TEST_PARAM      189
#define MSP_SET_TEST_PARAM       190

#define MSP_READ_TEST_PARAM      189
#define MSP_HEX_NANO             199

#define MSP_SET_RAW_RC           200   //in message          8 rc chan
#define MSP_SET_RAW_GPS          201   //in message          fix, numsat, lat, lon, alt, speed
#define MSP_SET_PID              202   //in message          P I D coeff (9 are used currently)
#define MSP_SET_BOX              203   //in message          BOX setup (number is dependant of your setup)
#define MSP_SET_RC_TUNING        204   //in message          rc rate, rc expo, rollpitch rate, yaw rate, dyn throttle PID
#define MSP_ACC_CALIBRATION      205   //in message          no param
#define MSP_MAG_CALIBRATION      206   //in message          no param
#define MSP_SET_MISC             207   //in message          powermeter trig + 8 free for future use
#define MSP_RESET_CONF           208   //in message          no param
#define MSP_SET_WP               209   //in message          sets a given WP (WP#,lat, lon, alt, flags)
#define MSP_SELECT_SETTING       210   //in message          Select Setting Number (0-2)
#define MSP_SET_HEAD             211   //in message          define a new heading hold direction

#define MSP_BIND                 240   //in message          no param

#define MSP_EEPROM_WRITE         250   //in message          no param

#define MSP_DEBUGMSG             253   //out message         debug string buffer
#define MSP_DEBUG                254   //out message         debug1,debug2,debug3,debug4

static uint8_t checksum[UART_NUMBER];
static uint8_t indRX[UART_NUMBER];
static uint8_t cmdMSP[UART_NUMBER];

  static uint8_t CURRENTPORT=0;


uint8_t SerialRead(uint8_t port) {
#if 0
    
  if(port == 0) USB_Flush(USB_CDC_TX);
  if(port == 0) return USB_Recv(USB_CDC_RX);      
  uint8_t t = serialTailRX[port];
  uint8_t c = serialBufferRX[t][port];
  if (serialHeadRX[port] != t) {
    if (++t >= RX_BUFFER_SIZE) t = 0;
    serialTailRX[port] = t;
  }
  return 0/*c*/;
#endif
    return (char) *(volatile unsigned long *) 0x40004804;
}



uint8_t SerialAvailable(uint8_t port) {

    if( !((*(volatile unsigned long *) 0x40004800) & 0x20) )
        return 0;
    else
    	  return 1;
//      //if(port == 0) return USB_Available(USB_CDC_RX);
//  return (serialHeadRX[port] - serialTailRX[port])%RX_BUFFER_SIZE;
}

void SerialWrite(uint8_t port,uint8_t c){
 
    while( !((*(volatile unsigned long *) 0x40004800) & 0x80) ) ;
    *(volatile unsigned long *) 0x40004804 = c;
//  serialize8(c);UartSendData();
}




uint8_t read8()  {
  return inBuf[indRX[CURRENTPORT]++][CURRENTPORT]&0xff;
}

uint16_t read16() {
  uint16_t t = read8();
  t+= (uint16_t)read8()<<8;
  return t;
}

uint32_t read32() {
  uint32_t t = read16();
  t+= (uint32_t)read16()<<16;
  return t;
}

void headSerialResponse(uint8_t err, uint8_t s) {
  serialize8('$');
  serialize8('M');
  serialize8(err ? '!' : '>');
  checksum[CURRENTPORT] = 0; // start calculating a new checksum
  serialize8(s);
  serialize8(cmdMSP[CURRENTPORT]);
}

void headSerialReply(uint8_t s) {
  headSerialResponse(0, s);
}

void inline headSerialError(uint8_t s) {
  headSerialResponse(1, s);
}

void tailSerialReply() {
  serialize8(checksum[CURRENTPORT]);
  UartSendData();
}

#if 0
void serializeNames(PGM_P s) {
  for (PGM_P c = s; pgm_read_byte(c); c++) {
    serialize8(pgm_read_byte(c));
  }
}
#endif

void serialCom() {
  uint8_t c,n;  
  static uint8_t offset[UART_NUMBER];
  static uint8_t dataSize[UART_NUMBER];
  static enum _serial_state {
    IDLE,
    HEADER_START,
    HEADER_M,
    HEADER_ARROW,
    HEADER_SIZE,
    HEADER_CMD,
  } c_state[UART_NUMBER];// = IDLE;

      CURRENTPORT=0;
    
    //while (SerialAvailable(CURRENTPORT) GPS_COND SPEK_COND) {
    while (SerialAvailable(CURRENTPORT)) {
      uint8_t bytesTXBuff = ((uint8_t)(serialHeadTX[CURRENTPORT]-serialTailTX[CURRENTPORT]))%TX_BUFFER_SIZE; // indicates the number of occupied bytes in TX buffer
      if (bytesTXBuff > TX_BUFFER_SIZE - 50 ) return; // ensure there is enough free TX buffer to go further (50 bytes margin)
      c = SerialRead(CURRENTPORT);
      //Serial.write(c);
     
        // regular data handling to detect and handle MSP and other data
        if (c_state[CURRENTPORT] == IDLE) {
          c_state[CURRENTPORT] = (c=='$') ? HEADER_START : IDLE;
          if (c_state[CURRENTPORT] == IDLE) evaluateOtherData(c); // evaluate all other incoming serial data
        } else if (c_state[CURRENTPORT] == HEADER_START) {
          c_state[CURRENTPORT] = (c=='M') ? HEADER_M : IDLE;
        } else if (c_state[CURRENTPORT] == HEADER_M) {
          c_state[CURRENTPORT] = (c=='<') ? HEADER_ARROW : IDLE;
        } else if (c_state[CURRENTPORT] == HEADER_ARROW) {
          if (c > INBUF_SIZE) {  // now we are expecting the payload size
            c_state[CURRENTPORT] = IDLE;
            continue;
          }
          dataSize[CURRENTPORT] = c;
          offset[CURRENTPORT] = 0;
          checksum[CURRENTPORT] = 0;
          indRX[CURRENTPORT] = 0;
          checksum[CURRENTPORT] ^= c;
          c_state[CURRENTPORT] = HEADER_SIZE;  // the command is to follow
        } else if (c_state[CURRENTPORT] == HEADER_SIZE) {
          cmdMSP[CURRENTPORT] = c;
          checksum[CURRENTPORT] ^= c;
          c_state[CURRENTPORT] = HEADER_CMD;
        } else if (c_state[CURRENTPORT] == HEADER_CMD && offset[CURRENTPORT] < dataSize[CURRENTPORT]) {
          checksum[CURRENTPORT] ^= c;
          inBuf[offset[CURRENTPORT]++][CURRENTPORT] = c;
        } else if (c_state[CURRENTPORT] == HEADER_CMD && offset[CURRENTPORT] >= dataSize[CURRENTPORT]) {
          if (checksum[CURRENTPORT] == c) {  // compare calculated and transferred checksum
            evaluateCommand();  // we got a valid packet, evaluate it
          }
          c_state[CURRENTPORT] = IDLE;
        }
     
    }

}

void evaluateCommand() {

  unsigned char auxChannels;
  unsigned char aux;
  
  switch(cmdMSP[CURRENTPORT]) {
   case MSP_SET_RAW_RC:
     for(uint8_t i=0;i<8;i++) {
       rcData[i] = read16();
     }
     
     //failsafeCnt = 0;
     
     headSerialReply(0);
     break;
 
   case MSP_READ_TEST_PARAM:
     headSerialReply(12);
     
     //blinkLED(15,20,1);
    
     //paramList[0] = alpha * 250.f;
     //paramList[1] = conf.P8[PIDALT] * 250.f / 200;
     //paramList[2] = conf.I8[PIDALT];
     //paramList[3] = conf.D8[PIDALT] * 250.f / 100;
     
     for(int idx = 0; idx < 12; idx++){
       //serialize8(paramList[idx]);
     } 
     
     break;
   case MSP_SET_TEST_PARAM:
     //for(int idx = 0; idx < 12; idx++){
     //  paramList[idx] = read8();
     //}
     
     //blinkLED(15,20,1);
     
     //alpha = paramList[0] / 250.f;
     //conf.P8[PIDALT] = paramList[1] / 250.f * 200;   //0~200
     //conf.I8[PIDALT] = paramList[2];                 //0~250
     //conf.D8[PIDALT] = paramList[3] / 250.f * 100;   //0~100
//     writeParams(0);
     return;
     break;
   case MSP_SET_RAW_RC_TINY:
     for(uint8_t i = 0;i < 4;i++) {
       serialRcValue[i] = 1000 + read8() * 4;
     }
     
     auxChannels = read8();
     
     aux = (auxChannels & 0xc0) >> 6;
     
     if(aux == 0){
       serialRcValue[4] = 1000;
     }
     else if(aux == 1){
       serialRcValue[4] = 1500;
     }
     else{
       serialRcValue[4] = 2000;
     }
     
     
     aux = (auxChannels & 0x30) >> 4;
     
     if(aux == 0){
       serialRcValue[5] = 1000;
     }
     else if(aux == 1){
       serialRcValue[5] = 1500;
     }
     else{
       serialRcValue[5] = 2000;
     }
     
     
     aux = (auxChannels & 0x0c) >> 2;
     
     if(aux == 0){
       serialRcValue[6] = 1000;
     }
     else if(aux == 1){
       serialRcValue[6] = 1500;
     }
     else{
       serialRcValue[6] = 2000;
     }
     
     aux = (auxChannels & 0x03);
     
     if(aux == 0){
       serialRcValue[7] = 1000;
     }
     else if(aux == 1){
       serialRcValue[7] = 1500;
     }
     else{
       serialRcValue[7] = 2000;
     }
     
     //failsafeCnt = 0;
     
          
     return;
     
     /*
     headSerialReply(8);
     
     for(uint8_t i = 0; i < 4; i++) {
       serialize16(serialRcValue[i]);
     }*/
     break;
   case MSP_ARM:
     //go_arm();
     break;
   case MSP_DISARM:
     //go_disarm();
     break;
   case MSP_TRIM_UP:
     //if(conf.angleTrim[PITCH] < 120){
     //  conf.angleTrim[PITCH]+=1;  
//       writeParams(1);
       
     //}
     break;
   case MSP_TRIM_DOWN:
     //if(conf.angleTrim[PITCH] > -120){
     //  conf.angleTrim[PITCH]-=1; 
//       writeParams(1);
      
     //}
     break;
   case MSP_TRIM_LEFT:
     //if(conf.angleTrim[ROLL] > -120){
     //  conf.angleTrim[ROLL]-=1; 
//       writeParams(1);
      
     //}
     break;
   case MSP_TRIM_RIGHT:
     //if(conf.angleTrim[ROLL] < 120){
     //  conf.angleTrim[ROLL]+=1; 
//       writeParams(1);
      
     //}
     break;
   case MSP_TRIM_UP_FAST:
     //if(conf.angleTrim[PITCH] < 120){
     //  conf.angleTrim[PITCH]+=10;  
//       writeParams(1);
       
     //}
     break;
   case MSP_TRIM_DOWN_FAST:
     //if(conf.angleTrim[PITCH] > -120){
     //  conf.angleTrim[PITCH]-=10; 
//       writeParams(1);
       
     //}
     break;
   case MSP_TRIM_LEFT_FAST:
     //if(conf.angleTrim[ROLL] > -120){
     //  conf.angleTrim[ROLL]-=10; 
//       writeParams(1);
       
     //}
     break;
   case MSP_TRIM_RIGHT_FAST:
     //if(conf.angleTrim[ROLL] < 120){
     //  conf.angleTrim[ROLL]+=10; 
//       writeParams(1);

     //}
     break;
   case MSP_HEX_NANO:
     headSerialReply(14);
     serialize8(flightState);
     serialize16(absolutedAccZ);
     //serialize32(EstAlt);
     //serialize16((int16_t)EstAlt);
     //for(uint8_t i=0;i<2;i++) serialize16(angle[i]);
     //serialize16((int16_t)AltHold);
     //serialize8(vbat);
     //serialize8((int8_t)(conf.angleTrim[PITCH]));
     //serialize8((int8_t)(conf.angleTrim[ROLL]));
     break;



   case MSP_SET_PID:
     //for(uint8_t i=0;i<PIDITEMS;i++) {
       //conf.P8[i]=read8();
       //conf.I8[i]=read8();
       //conf.D8[i]=read8();
     //}
     headSerialReply(0);
     break;
   case MSP_SET_BOX:
     for(uint8_t i=0;i<10/*CHECKBOXITEMS*/;i++) {
       //conf.activate[i]=read16();
     }
     headSerialReply(0);
     break;
   case MSP_SET_RC_TUNING:
     //conf.rcRate8 = read8();
     //conf.rcExpo8 = read8();
     //conf.rollPitchRate = read8();
     //conf.yawRate = read8();
     //conf.dynThrPID = read8();
     //conf.thrMid8 = read8();
     //conf.thrExpo8 = read8();
     headSerialReply(0);
     break;
   case MSP_SET_MISC:
    
     headSerialReply(0);
     break;
     
   case MSP_SET_HEAD:
     //magHold = read16();
     headSerialReply(0);
     break;
   case MSP_IDENT:
     headSerialReply(7);
     serialize8(VERSION);   // multiwii version
     serialize8(MULTITYPE); // type of multicopter
     serialize8(MSP_VERSION);         // MultiWii Serial Protocol Version
     //serialize32(pgm_read_dword(&(capability)));        // "capability"
     break;
   case MSP_STATUS:
     headSerialReply(11);
     //serialize16(cycleTime);
     //serialize16(i2c_errors_count);
     serialize16(ACC|BARO<<1|MAG<<2|GPS<<3|SONAR<<4);
     //serialize32(
                   //f.ANGLE_MODE<<BOXANGLE|
                   //f.HORIZON_MODE<<BOXHORIZON|
                 
                   //f.MAG_MODE<<BOXMAG|f.HEADFREE_MODE<<BOXHEADFREE|rcOptions[BOXHEADADJ]<<BOXHEADADJ|
                 
                   //rcOptions[BOXBEEPERON]<<BOXBEEPERON|
                 
                 
       //          f.ARMED<<BOXARM);
       //serialize8(global_conf.currentSet);   // current setting
     break;
   case MSP_RAW_IMU:
     headSerialReply(18);
     //for(uint8_t i=0;i<3;i++) serialize16(accSmooth[i]);
     //for(uint8_t i=0;i<3;i++) serialize16(gyroData[i]);
     //for(uint8_t i=0;i<3;i++) serialize16(magADC[i]);
     break;
   case MSP_SERVO:
     headSerialReply(16);
     for(uint8_t i=0;i<8;i++)
      
       serialize16(0);
       
     break;
   case MSP_MOTOR:
     headSerialReply(16);
     //for(uint8_t i=0;i<8;i++) {
     //  serialize16( (i < NUMBER_MOTOR) ? motor[i] : 0 );
     //}
     break;
   case MSP_RC:
     headSerialReply(RC_CHANS * 2);
     for(uint8_t i=0;i<RC_CHANS;i++) serialize16(rcData[i]);
     break;
   
   case MSP_ATTITUDE:
     headSerialReply(8);
     //for(uint8_t i=0;i<2;i++) serialize16(angle[i]);
     //serialize16(heading);
     //serialize16(headFreeModeHold);
     break;
   case MSP_ALTITUDE:
     headSerialReply(6);
     //serialize32(EstAlt);
     //serialize16(vario);                  // added since r1172
     break;
   case MSP_ANALOG:
     headSerialReply(5);
     //serialize8(vbat);
     //serialize16(intPowerMeterSum);
     //serialize16(rssi);
     break;
   case MSP_RC_TUNING:
     headSerialReply(7);
     //serialize8(conf.rcRate8);
     //serialize8(conf.rcExpo8);
     //serialize8(conf.rollPitchRate);
     //serialize8(conf.yawRate);
     //serialize8(conf.dynThrPID);
     //serialize8(conf.thrMid8);
     //serialize8(conf.thrExpo8);
     break;
   case MSP_PID:
     //headSerialReply(3*PIDITEMS);
     //for(uint8_t i=0;i<PIDITEMS;i++) {
       //serialize8(conf.P8[i]);
       //serialize8(conf.I8[i]);
       //serialize8(conf.D8[i]);
     //}
     break;
   case MSP_PIDNAMES:
     //headSerialReply(strlen_P(10/*pidnames*/));
     //serializeNames(10/*pidnames*/);
     break;
   case MSP_BOX:
     headSerialReply(2*10/*CHECKBOXITEMS*/);
     for(uint8_t i=0;i<10/*CHECKBOXITEMS*/;i++) {
       //serialize16(conf.activate[i]);
     }
     break;
   case MSP_BOXNAMES:
     //headSerialReply(strlen_P(10/*boxnames*/));
     //serializeNames(10/*boxnames*/);
     break;
   case MSP_BOXIDS:
     headSerialReply(10/*CHECKBOXITEMS*/);
     for(uint8_t i=0;i<10/*CHECKBOXITEMS*/;i++) {
     //  serialize8(pgm_read_byte(&(boxids[i])));
     }
     break;
   case MSP_MISC:
     headSerialReply(2);
     //serialize16(intPowerTrigger1);
     break;
   case MSP_MOTOR_PINS:
     headSerialReply(8);
     for(uint8_t i=0;i<8;i++) {
//       serialize8(PWM_PIN[i]);
     }
     break;
     
   case MSP_RESET_CONF:
//     if(!f.ARMED) LoadDefaults();
     headSerialReply(0);
     break;
   case MSP_ACC_CALIBRATION:
     //if(!f.ARMED) calibratingA=512;
     headSerialReply(0);
     break;
   case MSP_MAG_CALIBRATION:
     //if(!f.ARMED) f.CALIBRATE_MAG = 1;
     headSerialReply(0);
     break;

   case MSP_EEPROM_WRITE:
//     writeParams(0);
     headSerialReply(0);
     break;
   case MSP_DEBUG:
     headSerialReply(8);
     for(uint8_t i=0;i<4;i++) {
       //serialize16(debug[i]); // 4 variables are here for general monitoring purpose
     }
     break;
     
   default:  // we do not know how to handle the (valid) message, indicate error MSP $M!
     headSerialError(0);
     break;
  }
  tailSerialReply();
}

// evaluate all other incoming serial data
void evaluateOtherData(uint8_t sr) {
    switch (sr) {
    // Note: we may receive weird characters here which could trigger unwanted features during flight.
    //       this could lead to a crash easily.
    //       Please use if (!f.ARMED) where neccessary
      
    }
}

// *******************************************************
// For Teensy 2.0, these function emulate the API used for ProMicro
// it cant have the same name as in the arduino API because it wont compile for the promini (eaven if it will be not compiled)
// *******************************************************


// *******************************************************
// Interrupt driven UART transmitter - using a ring buffer
// *******************************************************

void serialize32(uint32_t a) {
  serialize8((a    ) & 0xFF);
  serialize8((a>> 8) & 0xFF);
  serialize8((a>>16) & 0xFF);
  serialize8((a>>24) & 0xFF);
}

void serialize16(int16_t a) {
  serialize8((a   ) & 0xFF);
  serialize8((a>>8) & 0xFF);
}

void serialize8(uint8_t a) {
  uint8_t t = serialHeadTX[CURRENTPORT];
  if (++t >= TX_BUFFER_SIZE) t = 0;
  serialBufferTX[t][CURRENTPORT] = a;
  checksum[CURRENTPORT] ^= a;
  serialHeadTX[CURRENTPORT] = t;
}

#if 0
  ISR(USART1_UDRE_vect) { // Serial 1 on a MEGA or on a PROMICRO
    uint8_t t = serialTailTX[1];
    if (serialHeadTX[1] != t) {
      if (++t >= TX_BUFFER_SIZE) t = 0;
      //UDR1 = serialBufferTX[t][1];  // Transmit next byte in the ring
      serialTailTX[1] = t;
    }
    if (t == serialHeadTX[1]) UCSR1B &= ~(1<<UDRIE1);
  }
#endif

void UartSendData() {
        while(serialHeadTX[0] != serialTailTX[0]) {
           if (++serialTailTX[0] >= TX_BUFFER_SIZE) serialTailTX[0] = 0;
         }
}



static void  SerialOpen(uint8_t port, uint32_t baud) {
//  uint8_t h = ((F_CPU  / 4 / baud -1) / 2) >> 8;
//  uint8_t l = ((F_CPU  / 4 / baud -1) / 2);
  switch (port) {
    
//        case 0: UDIEN &= ~(1<<SOFE); break;// disable the USB frame interrupt of arduino (it causes strong jitter and we dont need it)
//      case 1: UCSR1A  = (1<<U2X1); UBRR1H = h; UBRR1L = l; UCSR1B |= (1<<RXEN1)|(1<<TXEN1)|(1<<RXCIE1); break;
  }
}

static void inline SerialEnd(uint8_t port) {
  switch (port) {
//      case 1: UCSR1B &= ~((1<<RXEN1)|(1<<TXEN1)|(1<<RXCIE1)|(1<<UDRIE1)); break;
    
  }
}

static void inline store_uart_in_buf(uint8_t data, uint8_t portnum) {

  uint8_t h = serialHeadRX[portnum];
  if (++h >= RX_BUFFER_SIZE) h = 0;
  if (h == serialTailRX[portnum]) return; // we did not bite our own tail?
  serialBufferRX[serialHeadRX[portnum]][portnum] = data;  
  serialHeadRX[portnum] = h;
}

//  ISR(USART1_RX_vect)  { store_uart_in_buf(UDR1, 1); }



//======================================================================================
//
//	DC Motor Control by PWM
//
//										 by GroundZero   2014. 1. 22.
//
//======================================================================================
#include "stm32md_reg.c"
#include "_printf.c"
#include "_delay.c"

#define MAX 400
#define MIN 260

void init_TIM2(void)
{								// CNF[1:0]=10(AF output), MODE[1:0]=11(Max output 50MHz) 1011
	GPIOA_CRL	|= ( 0xb<<0)	// set PA0 as AF output (0xb = 1011)	TIM2_CH1
				|  ( 0xb<<4)	// set PA1 as AF output (0xb = 1011)	TIM2_CH2
				|  ( 0xb<<8)	// set PA2 as AF output (0xb = 1011)	TIM2_CH2
				|  ( 0xb<<12);	// set PA3 as AF output (0xb = 1011)	TIM2_CH2
	

//	RCC_APB1ENR	|= ( 0x1<< 0);	// bit0 - TIM2 Clock Enable bit
	
	TIM2_PSC	 = 8;			// 72000000 / (8+1) = 8000000 =  8MHz, T = 1/8000000 = 0.000000125 = 0.125us
							
	TIM2_ARR	 = 400-1;		// 0.000000125 * 400 = 0.00005, F = 1 / 0.00005 = 20000Hz = 20KHz
	
	TIM2_CR1	|= ( 0x1<< 4);	// set DIR (Direction - down count)
				
	TIM2_CCMR1	|= ( 0x1<< 3)	// ch1: preload enable
				|  ( 0x6<< 4)	// ch1: OC Mode = PWM mode1 ( 110 )
				|  ( 0x1<<11)	// ch2: preload enable
				|  ( 0x6<<12);	// ch2: OC Mode = PWM mode1 ( 110 )

	TIM2_CCMR2	|= ( 0x1<< 3)	// ch3: compare fast & preload enable(11)
				|  ( 0x6<< 4)	// ch3: OC Mode = PWM mode1 ( 110 )
				|  ( 0x1<<11)	// ch4: compare fast & preload enable(11)
				|  ( 0x6<<12);	// ch4: OC Mode = PWM mode1 ( 110 )

	TIM2_CCER	|= ( 0x1<< 0)	// ch1: output enable
				|  ( 0x1<< 4)	// ch2: output enable
				|  ( 0x1<< 8)	// ch3: output enable
				|  ( 0x1<<12);	// ch4: output enable
	
	TIM2_CCR1	 = (280-1);		// ch1: 65% duty
	TIM2_CCR2	 = (280-1);		// ch2: 65% duty
	TIM2_CCR3	 = (280-1);		// ch3: 65% duty
	TIM2_CCR4	 = (280-1);		// ch3: 65% duty
	
	TIM2_CR1	|= ( 0x1<< 7)	// set APRE(Auto Reload Preload Enable)
				|  ( 0x1<< 0);	// TIM3 Counter Enable
}

void init_TIM3(void)
{								// CNF[1:0]=10(AF output), MODE[1:0]=11(Max output 50MHz) 1011
	GPIOA_CRL	|= ( 0xb<<24)	// set PA6 as AF output (0xb = 1011)	TIM3_CH1
				|  ( 0xb<<28);	// set PA7 as AF output (0xb = 1011)	TIM3_CH2
	
	GPIOB_CRL	|= ( 0xb<< 0)	// set PB0 as AF output (0xb = 1011)	TIM3_CH3
				|  ( 0xb<< 4);	// set PB1 as AF output (0xb = 1011)	TIM3_CH4

//	RCC_APB1ENR	|= ( 0x1<< 1);	// bit1 - TIM3 Clock Enable bit
	
	TIM3_PSC	 = 8;			// 72000000 / (8+1) = 8000000 =  8MHz, T = 1/8000000 = 0.000000125 = 0.125us
							
	TIM3_ARR	 = 400-1;		// 0.000000125 * 400 = 0.00005, F = 1 / 0.00005 = 20000Hz = 20KHz
	
	TIM3_CR1	|= ( 0x1<< 4);	// set DIR (Direction - down count)
				
	TIM3_CCMR1	|= ( 0x1<< 3)	// ch1: preload enable
				|  ( 0x6<< 4)	// ch1: OC Mode = PWM mode1 ( 110 )
				|  ( 0x1<<11)	// ch2: preload enable
				|  ( 0x6<<12);	// ch2: OC Mode = PWM mode1 ( 110 )

	TIM3_CCMR2	|= ( 0x1<< 3)	// ch3: compare fast & preload enable(11)
				|  ( 0x6<< 4)	// ch3: OC Mode = PWM mode1 ( 110 )
				|  ( 0x1<<11)	// ch4: compare fast & preload enable(11)
				|  ( 0x6<<12);	// ch4: OC Mode = PWM mode1 ( 110 )

	TIM3_CCER	|= ( 0x1<< 0)	// ch1: output enable
				|  ( 0x1<< 4)	// ch2: output enable
				|  ( 0x1<< 8)	// ch3: output enable
				|  ( 0x1<<12);	// ch4: output enable
	
	TIM3_CCR1	 = (280-1);		// ch1: 65% duty
	TIM3_CCR2	 = (280-1);		// ch2: 65% duty
	TIM3_CCR3	 = (280-1);		// ch3: 65% duty
	TIM3_CCR4	 = (280-1);		// ch3: 65% duty
	
	TIM3_CR1	|= ( 0x1<< 7)	// set APRE(Auto Reload Preload Enable)
				|  ( 0x1<< 0);	// TIM3 Counter Enable
}

void init_TIM4(void)
{								// CNF[1:0]=10(AF output), MODE[1:0]=11(Max output 50MHz) 1011
//	GPIOB_CRL	|= ( 0xb<<24)	// set PA6 as AF output (0xb = 1011)	TIM4_CH1
//				|  ( 0xb<<28);	// set PA7 as AF output (0xb = 1011)	TIM4_CH2
	
	GPIOB_CRH	|= ( 0xb<< 0)	// set PB8 as AF output (0xb = 1011)	TIM4_CH3
				|  ( 0xb<< 4);	// set PB9 as AF output (0xb = 1011)	TIM4_CH4

//	RCC_APB1ENR	|= ( 0x1<< 2);	// bit2 - TIM4 Clock Enable bit
	
	TIM4_PSC	 = 8;			// 72000000 / (8+1) = 8000000 =  8MHz, T = 1/8000000 = 0.000000125 = 0.125us
							
	TIM4_ARR	 = 400-1;		// 0.000000125 * 400 = 0.00005, F = 1 / 0.00005 = 20000Hz = 20KHz
	
	TIM4_CR1	|= ( 0x1<< 4);	// set DIR (Direction - down count)
				
//	TIM4_CCMR1	|= ( 0x1<< 3)	// ch1: preload enable
//				|  ( 0x6<< 4)	// ch1: OC Mode = PWM mode1 ( 110 )
//				|  ( 0x1<<11)	// ch2: preload enable
//				|  ( 0x6<<12);	// ch2: OC Mode = PWM mode1 ( 110 )

	TIM4_CCMR2	|= ( 0x1<< 3)	// ch3: compare fast & preload enable(11)
				|  ( 0x6<< 4)	// ch3: OC Mode = PWM mode1 ( 110 )
				|  ( 0x1<<11)	// ch4: compare fast & preload enable(11)
				|  ( 0x6<<12);	// ch4: OC Mode = PWM mode1 ( 110 )

	TIM4_CCER	|= ( 0x1<< 0)	// ch1: output enable
				|  ( 0x1<< 4)	// ch2: output enable
				|  ( 0x1<< 8)	// ch3: output enable
				|  ( 0x1<<12);	// ch4: output enable
	
	TIM4_CCR1	 = (280-1);		// ch1: 65% duty
	TIM4_CCR2	 = (280-1);		// ch2: 65% duty
//	TIM4_CCR3	 = (280-1);		// ch3: 65% duty
//	TIM4_CCR4	 = (280-1);		// ch4: 65% duty
	
	TIM4_CR1	|= ( 0x1<< 7)	// set APRE(Auto Reload Preload Enable)
				|  ( 0x1<< 0);	// TIM3 Counter Enable
}


void change_duty31(unsigned short duty)
{
	TIM3_CCR1	 = duty-1;		// change duty of TIM3_CH1
}

void change_duty32(unsigned short duty)
{
	TIM3_CCR2	 = duty-1;		// change duty of TIM3_CH2
}


#if 0
void change_duty33(unsigned short duty)
{
	TIM3_CCR3	 = duty-1;		// change duty of TIM3_CH3
}

void change_duty34(unsigned short duty)
{
	TIM3_CCR4	 = duty-1;		// change duty of TIM3_CH4
}
#endif


int main(void)
{
	unsigned short duty = MAX;



    	/* USART3 configuration ------------------------------------------------------*/
    	/* USART3 configured as follow:
    	 - BaudRate = 115200 baud
    	 - Word Length = 8 Bits
    	 - One Stop Bit
    	 - No parity
    	 - Hardware flow control disabled (RTS and CTS signals)
    	 - Receive and transmit enabled
    	*/
    *(volatile unsigned long *) 0x40004810 = 0x0;           // 1 stop bit
    *(volatile unsigned long *) 0x4000480C = 0x200C;        // 8bit no parity
    *(volatile unsigned long *) 0x40004814 = 0x0;
    //*(volatile unsigned long *) 0x40004808 = 19 << 4 | 8;   // 내부 OSC 32Mhz인 경우 115200bps로 통신 속도 설정
	  *(volatile unsigned long *) 0x40004808 = 39 << 4 | 1;	// 115,200 bps (ext OSC 72Mhz) : DIV_Mantisa=39, DIV_Fraction=1
    *(volatile unsigned long *) 0x4000480C |= 0x2000;

    while(0)
    {
      while( !((*(volatile unsigned long *) 0x40004800) & 0x80) ) ;
         *(volatile unsigned long *) 0x40004804 = 'A';

      while( !((*(volatile unsigned long *) 0x40004800) & 0x80) ) ;
         *(volatile unsigned long *) 0x40004804 = 'T';

    }


  serialCom();    //MSP 사용


	printf("Moror_Ctrl\n");

//	init_TIM2();
//	init_TIM3();
//	init_TIM4();
	GPIOB_ODR	|= ( 0xf << 4 );	// PA5,4,3,2 = 1111 = 0xf

	while(1)
	{
		switch(get_byte())
		{
			case'a':
				printf("turn left\n");
//				GPIOA_ODR	&= ~(0xf << 2 );	// PA5,4,3,2 = 0000 = 0x0
//				GPIOA_ODR	|= ( 0x6 << 2 );	// PA5,4,3,2 = 1001 = 0x9
				GPIOB_ODR	&= ~(0xf << 4 );	// PB4,5,6,7 = 0000 = 0x0
				GPIOB_ODR	|= ( 0x6 << 4 );	// PB4,5,6,7 = 0110 = 0x6
        GPIOB_ODR	|= ( 0x3 << 8 );	// PB8,9
				break;

			case'b':
				printf("turn right\n");
//				GPIOA_ODR	&= ~(0xf << 2 );	// PA5,4,3,2 = 0000 = 0x0
//				GPIOA_ODR	|= ( 0x9 << 2 );	// PA5,4,3,2 = 0110 = 0x6				
				GPIOB_ODR	&= ~(0xf << 4 );	// PB4,5,6,7 = 0000 = 0x0
				GPIOB_ODR	|= ( 0x9 << 4 );	// PB4,5,6,7 = 1001 = 0x9
        GPIOB_ODR	|= ( 0x3 << 8 );	// PB8,9
				break;

			case'c':
				printf("forward\n");
//				GPIOA_ODR	&= ~(0xf << 2 );	// PA5,4,3,2 = 0000 = 0x0
//				GPIOA_ODR	|= ( 0x5 << 2 );	// PA5,4,3,2 = 0101 = 0x5
				GPIOB_ODR	&= ~(0xf << 4 );	// PB4,5,6,7 = 0000 = 0x0
				GPIOB_ODR	|= ( 0x3 << 4 );	// PB4,5,6,7 = 0011 = 0x3
        GPIOB_ODR	|= ( 0x3 << 8 );	// PB8,9
				break;

			case'd':
				printf("back\n");
//				GPIOA_ODR	&= ~(0xf << 2 );	// PA5,4,3,2 = 0000 = 0x0
//				GPIOA_ODR	|= ( 0xa << 2 );	// PA5,4,3,2 = 1010 = 0xa
				GPIOB_ODR	&= ~(0xf << 4 );	// PB4,5,6,7 = 0000 = 0x0
				GPIOB_ODR	|= ( 0xc << 4 );	// PB4,5,6,7 = 1100 = 0xc
        GPIOB_ODR	|= ( 0x3 << 8 );	// PB8,9
				break;

			case('i'):
				printf("stop\n");
//				GPIOA_ODR	|= ( 0xf << 2 );	// PA5,4,3,2 = 1111 = 0xf
				GPIOC_ODR	&= ~( 0x3 << 14 );	// PC14,15
				GPIOB_ODR	|= ( 0xf << 4 );	// PB4,5,6,7 = 1111 = 0xf
				
				break;

/*			case('>'):
				if(duty <= MAX)
				{
					duty = duty + 10;
					change_duty31(duty);
					change_duty32(duty);
//					printf("increase\n");
//					printf("duty=%d\n",duty);
				}
				else
				{
					duty = MAX;
//					printf("duty=%d\n",duty);
//					printf("MAX duty!\n");
				}
				break;
				
			case('<'):
				if(duty >= MIN)
				{
					duty = duty - 10;
					change_duty31(duty);
					change_duty32(duty);
//					printf("decrease\n");
//					printf("duty=%d\n",duty);
				}
				else
				{
					duty = MIN;
//					printf("duty=%d\n",duty);
//					printf("MIN duty!\n");
				}
				break;
				
			case('x'):
				duty = MAX;
				change_duty31(duty);
				change_duty32(duty);		
				printf("duty=%d\n",duty);
				printf("MAX duty!\n");
				break;

			case('n'):
				duty = MIN;
				change_duty31(duty);
				change_duty32(duty);
				printf("duty=%d\n",duty);
				printf("MIN duty!\n");
				break;
*/
			default:
				break;
		}
	}
}