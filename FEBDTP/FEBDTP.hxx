//#include <vector>

#include <array>
#include <functional>
#include <net/if.h>
#include <unistd.h>

// Ethernet switch register r/w
#define FEB_RD_SR 0x0001
#define FEB_WR_SR 0x0002
#define FEB_RD_SRFF 0x0003
#define FEB_WR_SRFF 0x0004
#define FEB_OK_SR 0x0000
#define FEB_ERR_SR 0x00FF

// Broadcast receiver MAC and general reset (init)
#define FEB_SET_RECV 0x0101
#define FEB_GEN_INIT 0x0102
#define FEB_GEN_HVON 0x0103
#define FEB_GEN_HVOF 0x0104
#define FEB_GET_RATE 0x0105 //get event rate
#define FEB_OK 0x0100
#define FEB_ERR 0x01FF

//CITIROC slow control register
#define FEB_RD_SCR 0x0201
#define FEB_WR_SCR 0x0202
#define FEB_OK_SCR 0x0200
#define FEB_ERR_SCR 0x02FF

//CITIROC probe MUX register
#define FEB_RD_PMR 0x0401
#define FEB_WR_PMR 0x0402
#define FEB_OK_PMR 0x0400
#define FEB_ERR_PMR 0x04FF

//CITIROC Data control register
#define FEB_RD_CDR 0x0301
#define FEB_WR_CDR 0x0302
#define FEB_DATA_CDR 0x0300
#define FEB_EOF_CDR 0x0303
#define FEB_ERR_CDR 0x03FF

//Firmware read-write transmission
#define FEB_RD_FW 0x0501
#define FEB_WR_FW 0x0502
#define FEB_OK_FW 0x0500
#define FEB_ERR_FW 0x05FF
#define FEB_EOF_FW 0x0503
#define FEB_DATA_FW 0x0504

//FPGA input logic configuration register
#define FEB_RD_FIL 0x0601
#define FEB_WR_FIL 0x0602
#define FEB_OK_FIL 0x0600
#define FEB_ERR_FIL 0x06FF

#define MAXPACKLEN 1500
#define MAXPAYLOAD (1500 - 14 - 4)
// Ethernet L2 Packets
typedef struct
{
  unsigned char dst_mac[6];       /*!< Destination MAC address */
  unsigned char src_mac[6];       /*!< Source MAC address */
  unsigned short iptype;          /*!< IP type*/
  unsigned short CMD;             /*!< FEBDTP command field*/
  unsigned short REG;             /*!< FEBDTP register field*/
  // unsigned char Data[MAXPAYLOAD]; /*!< FEBDTP data field, 50-8=42 bytes*/
  std::array<unsigned char, MAXPAYLOAD> Data;

} FEBDTP_PKT; // packet total length 64 bytes, 42 useful data

/*typedef struct {
	unsigned char flags; //flags defining event type, 1=T0 reset, 2=T1 reset or 4=scintillator trigger
	UInt_t T0;
	UInt_t T1;
	unsigned short adc[32]; //adc data on 32 channels
} Event_t;
*/

class FEBDTP
{
public:
  FEBDTP_PKT gpkt;
  unsigned char srcmac[6] = {0, 0, 0, 0, 0, 0};
  // unsigned char dstmac[6] = {0x00, 0x60, 0x37, 0x12, 0x34, 0x00}; //base mac for FEBs, last byte 0->255
  std::array<unsigned char, 6> dstmac = {0x00, 0x60, 0x37, 0x12, 0x34, 0x00}; //base mac for FEBs, last byte 0->255
  unsigned char brcmac[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  int nclients = 0;
  // unsigned char macs[256][6]; //list of detected clients
  // modification to this 2D array.
  // ref: https://stackoverflow.com/questions/60950999/how-to-bind-c-structure-with-an-array-of-another-structre-as-a-member-using-pyb
  std::array<std::array<unsigned char, 6>, 256> macs;
  int Verbose = 0;

  unsigned short VCXO = 500;
  char ifName[IFNAMSIZ];
  int sockfd_w = -1;
  int sockfd_r = -1;
  struct timeval tv;
  // void (*fPacketHandler)(int) = 0;
  std::function<void(int)> fPacketHandler;

  FEBDTP(){};                                 // default constructor
  FEBDTP(const char *iface) { Init(iface); }; //main constructor
  ~FEBDTP()
  {
    close(sockfd_w);
    close(sockfd_r);
  } //destructor
  int Init(const char *iface);

  void Init_FEBDTP_pkt(FEBDTP_PKT *pkt, unsigned char *src, unsigned char *dst);
  void Init_FEBDTP_pkt(FEBDTP_PKT *pkt);
  void Init_FEBDTP_pkt();
  int Send_pkt(FEBDTP_PKT *pkt, int len, int timeout_us = 50000);
  int SendCMD(unsigned char *mac, unsigned short cmd, unsigned short reg, unsigned char *buf);
  //unsigned short RecvAnsw(Int_t timeout); //wait for <timeout> ms, returns either reply code, or FFFF in case of timeout
  void Print_gpkt(int truncat = MAXPACKLEN);
  void Print_gpkt_evts(int truncat = MAXPACKLEN);
  void CMD_stoa(unsigned short cmd, char *str);                                     //convert CMD code to name string
  int ScanClients();                                                          // Scan MAC addresses of FEBs within reach
  int ReadBitStream(const char *fname, unsigned char *buf);                         // read CITIROC SC bitstream into the buffer
  int WriteBitStream(const char *fname, unsigned char *buf, int bitlen);            // write CITIROC SC bitstream into file
  int WriteBitStreamAnnotated(const char *fname, unsigned char *buf, int bitlen);   // write CITIROC SC bitstream into file
  void WriteLVBitStream(const char *fname, unsigned char *buf, bool rev = false); // write CITIROC SC bitstream from the buffer, buf[MAXPACKLEN], to LabView setup file
  void ReadLVBitStream(const char *fname, unsigned char *buf, bool rev = false);  // write CITIROC SC bitstream from the buffer, buf[MAXPACKLEN], to LabView setup file
  // void setPacketHandler(void (*fhandler)(int) = 0);
  void setPacketHandler(const std::function<void(int)> fhandler);
  void PrintMacTable();

};
