#ifndef __USBTRANSMIT_H__
#define __USBTRANSMIT_H__

// Device endpoint(s)
#define EP0     0x00
#define EP1_IN  0x81    //wMaxPacketSize:   512	Bulk
#define EP1_OUT 0x01    //wMaxPacketSize:   512	Bulk

int USBScanDevice(int usb_pid,int usb_vid);
bool USBOpenDevice(int DevIndex);
bool USBCloseDevice(int DevIndex);
bool USBCheckDevice(int DevIndex);

bool USBBulkWriteData(int DevIndex,int pipenum,char *sendbuffer,int len,int waittime);
int USBBulkReadData(int DevIndex,int pipenum,char *readbuffer,int len,int waittime);
bool USBIntWriteData(int DevIndex,int pipenum,char *sendbuffer,int len,int waittime);
int USBIntReadData(int DevIndex,int pipenum,char *readbuffer,int len,int waittime);
bool USBCtrlData(int DevIndex,int requesttype,int request,int value, int index, char *bytes, int size,int waittime);
#endif