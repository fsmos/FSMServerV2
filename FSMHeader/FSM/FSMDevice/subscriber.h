#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H 

///������������ ���������� ����� � ������
#define MAX_BOARD_NUMBER	8
///������������ ����� ����� SIP-��������
#define MAX_SIP_NAME	5
///������������ ����� ������ ����������� ��������
#define MAX_SIZE_SUBSCIBER_FOR_CALL	16
///���-�� ����������� �����
#define CIRCULAR_NUMBER	4
///���-�� ���������-�����
#define CONFERENCE_NUMBER	4
///����. ���-�� ���������� � �����������
#define MAX_SUBSCRIBER_CONFERENCE	10
///����. ���-�� ���������� � �����������
#define MAX_SUBSCRIBER_CIRCULAR	10

#define MAGIC_WORD	"ASALIA"
/*! ������ ����� ����� � �������
* BOARD_NONE - ���������� ������\n
* BOARD_MN825 - ������ ���� �N825(2 �������� �/� �-168)\n
* BOARD_MN921 - ������ ���� �N921(2 ������������� �������� ��/���/��)\n
*/
typedef enum{BOARD_NONE, BOARD_MN825, BOARD_MN921}TYPE_BOARD;
typedef enum{TYPEPO_PO06, TYPEPO_PO07, TYPEPO_PO08, TYPEPO_VPO}TYPE_PO;

/*! ������ ����� ��������� � �������
* CHANNEL_MB - ������� ���� ����� � ���������� ��������� ��\n
* CHANNEL_CB - ������� ���� ����� � ���������� ��������� ��\n
* CHANNEL_ATS - ������� ���� ����� � ������ ���\n
* CHANNEL_R168 - ������� ���� ����� � ������������� �-168\n
* CHANNEL_TCH - ������� ���� ����� � ������ ��\n
*/
typedef enum{CHANNEL_MB, CHANNEL_CB, CHANNEL_ATS, CHANNEL_R168, CHANNEL_TCH}TYPE_CHANNEL;

typedef enum{TWO_WIRE, FOUR_WIRE_FL, FOUR_WIRE_TCH}TYPE_LINE_TCH;

/** 
  * @brief ��������� ����������� ��������� ����� � ��������� ��
  */
typedef struct{
	unsigned int ToneOutputCallPulse;///����� ���������� ������ � ����� (1��� = 8000 �����)
}CMB;

/** 
  * @brief ��������� ����������� ��������� ����� � ��������� ��
  */
typedef struct{
	unsigned int ToneOutputCallPulse;///����� ���������� ������ � ����� (1��� = 8000 �����)	
}CCB;

/** 
  * @brief ��������� ����������� ��������� ����� � ������ ���
  */
typedef struct{
	unsigned int TypeATS;///��� ���, 0 - ����������, 1 - �������, 2 - �2
	char SelfNumber[16];///���� ���������� ����� (�������� ��� ��� ���� �2 - ��������� ��� ������������� ������)
	char SelfNumberLength;///����� ������ ����������� ������
	char TargetNumber[16];///���������� ����� �� ������� ������ ����� 
	char TargetNumberLength;///����� ����������� ������ �� ������� ������ ����� 
	char Priority;///��������� (�������� ��� ��� ���� �2)
	unsigned char SNRLin;///��������� ������/��� ��� �������� ��������
	unsigned char SNRDtmf;///��������� ������/��� ��� �������� DTMF
}CATS;

/** 
  * @brief ��������� ����������� ��������� ����� � ������ ��
  */
typedef struct{
	TYPE_LINE_TCH type_line;/*!< \b 0 - 2-� ��������� ����� ��
								\b 1 - 4-� ��������� ����� �� \n
								\b 2- 4-� ��������� ����� ��
							*/
	unsigned int ToneOutputCallPulse;///����� ���������� ������ � ����� (1��� = 8000 �����)
	unsigned int MinToneCallPulse;/// ����������� ����� ���������� ������, ������� ����� ���������� ��� �����, � �����(8000=1�) 
	unsigned int MaxToneCallPulse;/// ������������ ����� ���������� ������, ������� ����� ���������� ��� �����, � �����(8000=1�) 
	unsigned int OutputCallFreq;///������� ��������� �������
}CTCH;

/** 
  * @brief ��������� ����������� ��������� ����� �� �������� �-168
  */
typedef struct{
	unsigned int TimeCall;///����� ���������� ������ � �168. ����
}CR168;

/** 
  * @brief ��������� ����������� ��������� ������ ������ ���� ��825
  */
typedef struct{
	///��� SIP-�������� ������ ������
	char self_sip_description[MAX_SIP_NAME];
	///����� ��������� ����� ��� ������ ������
	unsigned int audio_port;
	// ����� sip-����� ��� ������
	unsigned int self_port;
	///����� ����������� �������� ��� ������ ������
	char SubscriberForCall[4][MAX_SIP_NAME];
	///������������ ����� ����� � ������������� ���� �-168 ��� ������� ������
	CR168 R168;
}CMN825ChannelConfig;

/** 
  * @brief ��������� ����������� ������������ ������ ���� ��925
  */
typedef struct{
	///UDP ���� ��� ������ ��������� ����������/���������������� �-168 ��� ������ ������
	unsigned int rcv_port_control_r168;
	///������������ ����� ��� ������� ������
	CMN825ChannelConfig ChannelConfig[2];
}CMN825;

/** 
  * @brief ��������� ����������� ��������� ������ ������ ���� ��921
  */
typedef struct{
	///��� SIP-�������� ������ ������
	char self_sip_description[MAX_SIP_NAME];
	///����� ����������� �������� ��� ������ ������
	char SubscriberForCall[4][MAX_SIP_NAME];
	///����� ��������� ����� ��� ������ ������
	unsigned int audio_port;
	// ����� sip-����� ��� ������
	unsigned int self_port;
	///�������� ���� ������
	TYPE_CHANNEL type_channel;
	///�������� �������� ������
	union CHANNEL{
		CMB		MB;
		CCB		CB;
		CATS	ATS;
		CTCH	TCH;
	}Channel_settings;
}CMN921ChannelConfig;

/** 
  * @brief ��������� ����������� ������������ ������ ���� ��927
  */
typedef struct{
	///������������ ����� ��� ������ ������
	CMN921ChannelConfig ChannelConfig[2];
}CMN921;

/** 
  * @brief ��������� ����������� ����� ��������� ������ �������
  */
typedef struct{
	unsigned int position;
	unsigned int server_ip;
	unsigned int server_sip_port;
	unsigned int self_ip;
	unsigned int self_mask;			//++++++
	unsigned int self_gateway;
	char name_sip_domen[MAX_SIP_NAME];//+++++++
	TYPE_BOARD type_board;
	union TypeBoard{
		CMN825 MN825;
		CMN921 MN921;
	}BoardSettings;
}CBoardConfiguration;

/** 
  * @brief ��������� ����������� IP-��������� ����� � ��������
*/
typedef struct{
	unsigned int server_ip;
	unsigned int self_ip;
	unsigned int subnet_mask;
	unsigned int gateway;
	unsigned int server_sip_port;
	unsigned char mac[6];
} CServerInfo;

/** 
  * @brief ��������� ����������� SIP-��������� ����� � ��������
*/
typedef struct{
	unsigned int self_port;
	char SipName[MAX_SIP_NAME];
	unsigned int RTP_port;
} CSIPInfo;

/** 
  * @brief ��������� ����������� SIP-��������� ����. �� ����� � ��������
*/
typedef struct{
	unsigned int server_listen_port;
	char SipName[MAX_SIP_NAME];
	char DisplayName[MAX_SIP_NAME];
} CSIPInfoVPO;

/** 
  * @brief ��������� ����������� �����-��������� ����� ������������ ��
*/
typedef struct{
	char alsa_dev_name[64];
	unsigned int MinPort;
	unsigned int MaxPort;
} CMediaInfo;

/** 
  * @brief ��������� ����������� ���������������� ����������� ����� ��
*/
typedef struct{
	char dynamic_sip_name[MAX_SIP_NAME];
	char SipNameGroupList[CIRCULAR_NUMBER][MAX_SUBSCRIBER_CIRCULAR][MAX_SIP_NAME];
} CCircularInfo;

/** 
  * @brief ��������� ����������� ���������������� ���������-����� ��
*/
typedef struct{
	char dynamic_sip_name[MAX_SIP_NAME];
	char SipNameGroupList[CONFERENCE_NUMBER][MAX_SUBSCRIBER_CONFERENCE][MAX_SIP_NAME];
} CConferenceInfo;

/** 
  * @brief ��������� ����������� ��������� ����� �� ������ ���������� ��-�� �-168
*/
typedef struct{
	unsigned int ip_addr[4];
	unsigned int port[4];
} CConfigR168;

/** 
  * @brief ��������� ����������� ������ �������� ����� � ��-06, ��-07, ��-08
*/
typedef struct{
	char sip_name[MAX_SIP_NAME];
	unsigned char exclusive;
	unsigned char autoconnection;
} CSubscriberInfo;

/** 
  * @brief ��������� ����������� ������ �������� ������������ ��
*/
typedef struct{
	CSubscriberInfo SubscriberInfo;
	char display_name[9];
} CSubscriberVPOInfo;

/** 
  * @brief ��������� ����������� ���� ����� ����� ��
*/
typedef struct{
	CSIPInfo sip_info;
	CSubscriberInfo SubscriberInfo[12];
	unsigned int Volume;
} CLineInfo;

/** 
  * @brief ��������� ����������� ��������� ��-06
*/
typedef struct{
	CServerInfo server_info;
	CLineInfo LineInfo[2];
	CConfigR168 ConfigR168;
	CCircularInfo CircularInfo;
	CConferenceInfo ConferenceInfo;
	char sip_name_ats[MAX_SIP_NAME];
} CPO06_Config __attribute__((aligned(4)));

/** 
  * @brief ��������� ����������� ��������� ��-07
*/
typedef struct{
	CServerInfo server_info;
	CLineInfo LineInfo[2];
	CCircularInfo CircularInfo;
	CConferenceInfo ConferenceInfo;
	char sip_name_ats[MAX_SIP_NAME];
} CPO07_Config;

/** 
  * @brief ��������� ����������� ��������� ��-08
*/
typedef struct{
	CServerInfo server_info;
	CSIPInfo sip_info;
	CSubscriberInfo SubscriberInfo[9];
	CConfigR168 ConfigR168;
	CCircularInfo CircularInfo;
	CConferenceInfo ConferenceInfo;
	char sip_name_ats[MAX_SIP_NAME];
	unsigned int Volume;
} CPO08_Config;

/** 
  * @brief ��������� ����������� ��������� ����������� ������ �� ����� ��������
*/
typedef struct{
	char Key[4];
	unsigned char Modif;
}CXK_TANG;

/** 
  * @brief ��������� ����������� ��������� ������������ ��
*/
typedef struct{
	CServerInfo server_info;
	CSIPInfoVPO SIPInfoVPO;
	CConfigR168 ConfigR168;
	CMediaInfo MediaInfo;
	CCircularInfo CircularInfo;
	CConferenceInfo ConferenceInfo;
	unsigned int PortExchangeRLK;
	char sip_name_ats[MAX_SIP_NAME];
	CSubscriberVPOInfo SubscriberVPOInfo[16];
	CXK_TANG XK_TANG;
} CVPO_Config;

#endif
