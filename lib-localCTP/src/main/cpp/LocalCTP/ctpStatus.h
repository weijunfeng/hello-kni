#pragma once
// coding by GB2312
#include "ThostFtdcUserApiDataType.h"
#include "stdafx.h"

namespace localCTP{

constexpr TThostFtdcErrorMsgType ErrMsgUserInfoIsEmpty = "CTP:��֤ʧ��(UserID��BrokerID����Ϊ��Ŷ)";
constexpr TThostFtdcErrorMsgType ErrMsgUserInfoNotSameAsLastTime = "CTP:��֤ʧ��(UserID��BrokerID��Ҫ���ϴε�¼ʱ��ͬŶ)";
constexpr TThostFtdcErrorMsgType ErrMsgNotAuth = "CTP:��¼ʧ��(û����֤)";
constexpr TThostFtdcErrorMsgType ErrMsgUserInfoNotSameAsAuth = "CTP:��¼ʧ��(UserID��BrokerID��Ҫ����֤ʱ��ͬŶ)";
constexpr TThostFtdcErrorMsgType ErrMsgDuplicateOrder = "CTP:�ظ��ı���(OrderRef��ȴ�ǰ�����ֵҪ��Ŷ)";
constexpr TThostFtdcErrorMsgType ErrMsg_INVALID_ORDERSIZE = "CTP:���Ϸ��ı�������(��Ϊ����)";
constexpr TThostFtdcErrorMsgType ErrMsg_EXCHANGE_ID_IS_WRONG = "CTP:�������������";
constexpr TThostFtdcErrorMsgType ErrMsg_INSTRUMENT_NOT_FOUND = "CTP:�Ҳ�����Լ";
constexpr TThostFtdcErrorMsgType ErrMsg_BAD_PRICE_VALUE = "CTP:��֧�ֵļ۸�(��Ҫ��PriceTick��������):";
constexpr TThostFtdcErrorMsgType ErrMsg_NotExistOrder = "CTP:����������Ŷ";
constexpr TThostFtdcErrorMsgType ErrMsg_AlreadyDoneOrder = "CTP:�����ѽ����޷��ٳ�Ŷ";
constexpr TThostFtdcErrorMsgType ErrMsg_NotSupportModifyOrder = "CTP:����ֻ�ܳ����޷��ĵ�Ŷ";
constexpr TThostFtdcErrorMsgType ErrMsg_PRICETYPE_NOTSUPPORT_BYEXCHANGE = "CTP:��������֧�ֵļ۸�����(OrderPriceType)";
constexpr TThostFtdcErrorMsgType ErrMsg_BAD_FIELD_ONLY_SPECULATION = "CTP:�����ֶ�����(��ϵͳֻ֧��Ͷ������)(CombHedgeFlag)";
constexpr TThostFtdcErrorMsgType ErrMsg_NotSupportContingentCondition = "CTP:��֧�������������Ŷ(ContingentCondition)";
constexpr TThostFtdcErrorMsgType ErrMsg_NotSupportTimeCondition = "CTP:��֧�ֵ���Ч������Ŷ(TimeCondition)";
constexpr TThostFtdcErrorMsgType ErrMsg_NoMarketData = "CTP:�ú�Լû����������:";
constexpr TThostFtdcErrorMsgType ErrMsg_INSTRUMENT_MARGINRATE_NOT_FOUND = "CTP:�ú�Լû�б�֤��������";
constexpr TThostFtdcErrorMsgType ERRMSG_INSTRUMENT_COMMISSIONRATE_NOT_FOUND = "CTP:�ú�Լû��������������:";// not used
constexpr TThostFtdcErrorMsgType ERRMSG_AVAILABLE_NOT_ENOUGH = "CTP:�����ʽ���";
constexpr TThostFtdcErrorMsgType ERRMSG_AVAILABLE_POSITION_NOT_ENOUGH = "CTP:ƽ��ʱ�ֲֲ���,��ǰ��ƽ������:";
constexpr TThostFtdcErrorMsgType ERRMSG_AVAILABLE_TODAY_POSITION_NOT_ENOUGH = "CTP:ƽ��ʱ�ֲֲ���,��ǰ��ƽ������:";
constexpr char CONDITIONAL_ORDER_SYSID_PREFIX[10] = "TJBD_";
constexpr char STR_YUE[10] = "��";

// ͨ��������������,�ж��Ƿ���(���ϱ�ϵͳ�����)������
inline bool isConditionalType(TThostFtdcContingentConditionType	contingentCondition)
{
    return contingentCondition == THOST_FTDC_CC_LastPriceGreaterThanStopPrice ||
        contingentCondition == THOST_FTDC_CC_LastPriceGreaterEqualStopPrice ||
        contingentCondition == THOST_FTDC_CC_LastPriceLesserThanStopPrice ||
        contingentCondition == THOST_FTDC_CC_LastPriceLesserEqualStopPrice;
}

inline std::string getStatusMsgByStatus(TThostFtdcOrderStatusType status)
{
    switch (status)
    {
        case THOST_FTDC_OST_AllTraded: // '0'
            return "ȫ���ɽ�";                
        case THOST_FTDC_OST_PartTradedQueueing: // '1'
            return "���ֳɽ�";
        case THOST_FTDC_OST_PartTradedNotQueueing: // '2'
            return "���ֳɽ����ڶ�����";
        case THOST_FTDC_OST_NoTradeQueueing: // '3'
            return "δ�ɽ�";
        case THOST_FTDC_OST_NoTradeNotQueueing: // '4'
            return "δ�ɽ����ڶ�����";
        case THOST_FTDC_OST_Canceled: // '5'
            return "�ѳ���";
        case THOST_FTDC_OST_Unknown: // 'a'
            return "δ֪";
        case THOST_FTDC_OST_NotTouched: // 'b'
            return "��δ����";
        case THOST_FTDC_OST_Touched: // 'c'
            return "�Ѵ���";
        default:
            return "δ֪";
    }
}

inline bool isTradingDay(const CLeeDateTime& date = CLeeDateTime::GetCurrentTime())
{
    const int dayOfWeek = date.GetDayOfWeek();
    if (dayOfWeek == 6 || dayOfWeek == 0)//TODO:�����жϳ��ټ���
    {
        return false;
    }
    return true;
}

inline std::string getNextTradingDay(CLeeDateTime dt)
{
    do {
        dt += CLeeDateTimeSpan(1, 0, 0, 0);
    } while (!isTradingDay(dt));
    return dt.Format("%Y%m%d");
}

inline std::string get_direction_name(const std::string& direction)
{
    static const std::map<std::string, std::string> direction_name_map{
        {std::string(1, THOST_FTDC_D_Buy), "��   "},
        {std::string(1, THOST_FTDC_D_Sell), "   ��"}
    };
    auto it_direction = direction_name_map.find(direction);
    if (it_direction != direction_name_map.end())
    {
        return it_direction->second;
    }
    else
    {
        return "δ֪";
    }
}
inline std::string get_direction_name(TThostFtdcDirectionType dir)
{
    return get_direction_name(std::string(1, dir));
}
inline std::string get_exchange_name(const std::string& ExchangeID)
{
    static const std::map<std::string, std::string> exchange_name_map{
        {"INE", "��Դ����"},
        {"SHFE", "������"},
        {"CFFEX", "�н���"},
        {"DCE", "������"},
        {"CZCE", "֣����"},
        {"GFEX", "������"},
        {"BSE", "������"},
        {"SSE", "�Ͻ���"},
        {"SHSE", "�Ͻ���"},
        {"SZSE", "���"}
    };
    auto it_exchange = exchange_name_map.find(ExchangeID);
    if (it_exchange != exchange_name_map.end())
    {
        return it_exchange->second;
    }
    else
    {
        return "δ֪";
    }
}
inline std::string get_open_close_name(const std::string& open_or_close)
{
    static const std::map<std::string, std::string> open_or_close_name_map{
        {std::string(1, THOST_FTDC_OF_Open), "��"},
        {std::string(1, THOST_FTDC_OF_Close), "  ƽ"},
        {std::string(1, THOST_FTDC_OF_CloseToday), "ƽ��"},
        {std::string(1, THOST_FTDC_OF_CloseYesterday), "ƽ��"},
        {std::string(1, THOST_FTDC_OF_ForceClose), "ǿƽ"},
        {std::string(1, THOST_FTDC_OF_ForceOff), "ǿ��"},
        {std::string(1, THOST_FTDC_OF_LocalForceClose), "����ǿƽ"}
    };
    auto it_open_or_close = open_or_close_name_map.find(open_or_close);
    if (it_open_or_close != open_or_close_name_map.end())
    {
        return it_open_or_close->second;
    }
    else
    {
        return "δ֪";
    }
}
inline std::string get_open_close_name(TThostFtdcOffsetFlagType open_or_close)
{
    return get_open_close_name(std::string(1, open_or_close));
}
//�ж��Ƿ�����ȨƷ��
inline bool isOptions(TThostFtdcProductClassType ProductClass)
{
    return ProductClass == THOST_FTDC_PC_Options ||
        ProductClass == THOST_FTDC_PC_SpotOption;
}

///ƽ����ϸ
struct CloseDetail
{
    ///���͹�˾����
    TThostFtdcBrokerIDType BrokerID;
    ///Ͷ���ߴ���
    TThostFtdcInvestorIDType InvestorID;
    ///����������
    TThostFtdcExchangeIDType ExchangeID;
    ///��Լ����
    TThostFtdcInstrumentIDType InstrumentID;
    ///��������(������)
    TThostFtdcDateType OpenDate;
    ///���ּ۸�
    TThostFtdcPriceType OpenPrice;
    ///���ֳɽ����
    TThostFtdcTradeIDType OpenTradeID;
    ///ƽ������(������)
    TThostFtdcDateType CloseDate;
    ///ƽ��ʱ��
    TThostFtdcTimeType CloseTime;
    ///ƽ�ֳɽ��۸�
    TThostFtdcPriceType ClosePrice;
    ///ƽ�ֳɽ����
    TThostFtdcTradeIDType CloseTradeID;
    ///ƽ������
    TThostFtdcVolumeType CloseVolume;
    ///ƽ�ֳɽ�����������
    TThostFtdcDirectionType Direction;
    ///������
    TThostFtdcPriceType PreSettlementPrice;
    ///ƽ��ӯ��
    TThostFtdcMoneyType CloseProfit;
    ///ʵ��ƽ������(ƽ��orƽ��)
    TThostFtdcOffsetFlagType CloseFlag;
    ///Ȩ������֧
    TThostFtdcMoneyType CashIn;
};

///���㵥
struct SettlementData
{
    ///���͹�˾����
    TThostFtdcBrokerIDType BrokerID;
    ///Ͷ���ߴ���
    TThostFtdcInvestorIDType InvestorID;
    ///���㵥����
    std::string SettlementContent;
    ///���㵥����(������)
    TThostFtdcDateType TradingDay;
    ///ȷ������
    TThostFtdcDateType ConfirmDay;
    ///ȷ��ʱ��
    TThostFtdcTimeType ConfirmTime;
};

const std::string SETTLEMENT_CONTEXT(
R"(settlement_header1=_                                            LocalCTPϵͳ                                           
settlement_header2=_                                                                    �Ʊ�ʱ�� Creation Date��%8s
settlement_header3=_----------------------------------------------------------------------------------------------------
settlement_header4=_                             ���׽��㵥(����) Settlement Statement(MTM)                             
settlement_header5=_�ͻ��� Client ID��  %-16s�ͻ����� Client Name��%s
settlement_header6=_���� Date��%8s
settlement_header7=_
settlement_header8=_
settlement_header9=_
settlement_header10=_
settlement_account_summary1=_                   �ʽ�״��  ���֣������  Account Summary  Currency��CNY 
settlement_account_summary2=_----------------------------------------------------------------------------------------------------
settlement_account_summary3=_�ڳ���� Balance b/f��               %13.2f  ������֤�� Initial Margin��        %13.2f
settlement_account_summary4=_�� �� �� Deposit/Withdrawal��        %13.2f  ��ĩ��� Balance c/f��             %13.2f
settlement_account_summary5=_ƽ��ӯ�� Realized P/L��              %13.2f  �� Ѻ �� Pledge Amount��           %13.2f
settlement_account_summary6=_�ֲֶ���ӯ�� MTM P/L��               %13.2f  �ͻ�Ȩ�� Client Equity����         %13.2f
settlement_account_summary7=_��Ȩִ��ӯ�� Exercise P/L��          %13.2f  ������Ѻ��֤��ռ�� FX Pledge Occ.��%13.2f
settlement_account_summary8=_�� �� �� Commission��                %13.2f  ��֤��ռ�� Margin Occupied��       %13.2f
settlement_account_summary9=_��Ȩ������ Exercise Fee��            %13.2f  ���֤�� Delivery Margin��       %13.2f
settlement_account_summary10=_���������� Delivery Fee��            %13.2f  ��ͷ��Ȩ��ֵ Market value(long)��  %13.2f
settlement_account_summary11=_�������� New FX Pledge��             %13.2f  ��ͷ��Ȩ��ֵ Market value(short)�� %13.2f
settlement_account_summary12=_�����ʳ� FX Redemption��             %13.2f  ��ֵȨ�� Market value(equity)��    %13.2f
settlement_account_summary13=_��Ѻ�仯��� Chg in Pledge Amt��     %13.2f  �����ʽ� Fund Avail.��             %13.2f
settlement_account_summary14=_Ȩ�������� Premium received��        %13.2f  �� �� �� Risk Degree��            %13.2f%%
settlement_account_summary15=_Ȩ����֧�� Premium paid��            %13.2f  Ӧ׷���ʽ� Margin Call��           %13.2f
settlement_account_summary16=_
settlement_deposit_withdrawal_head1=_                                        �������ϸ Deposit/Withdrawal 
settlement_deposit_withdrawal_head2=_----------------------------------------------------------------------------------------------------------------
settlement_deposit_withdrawal_head3=_|��������|       ���������       |      ���      |      ����      |                   ˵��                   |
settlement_deposit_withdrawal_head4=_|  Date  |          Type          |    Deposit     |   Withdrawal   |                   Note                   |
settlement_deposit_withdrawal_head5=_----------------------------------------------------------------------------------------------------------------
settlement_deposit_withdrawal_single_record1=_|%-8s|�����                  |%16.2f|%16.2f|%-42s|
settlement_deposit_withdrawal_end1=_----------------------------------------------------------------------------------------------------------------
settlement_deposit_withdrawal_end2=_|��%4d��|                        |%16.2f|%16.2f|                                          |
settlement_deposit_withdrawal_end3=_----------------------------------------------------------------------------------------------------------------
settlement_deposit_withdrawal_end4=_�����---Deposit/Withdrawal     ����ת��---Bank-Futures Transfer    ���ڻ���---Bank-Futures FX Exchange
settlement_deposit_withdrawal_end5=_
settlement_trade_head1=_                                                              �ɽ���¼ Transaction Record 
settlement_trade_head2=_---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
settlement_trade_head3=_|�ɽ�����| ������ |       Ʒ��       |      ��Լ      |��/��|   Ͷ/��    |  �ɽ���  | ���� |   �ɽ���   |       ��ƽ       |  ������  |  ƽ��ӯ��  |     Ȩ������֧      |  �ɽ����  |
settlement_trade_head4=_|  Date  |Exchange|     Product      |   Instrument   | B/S |    S/H     |   Price  | Lots |  Turnover  |       O/C        |   Fee    |Realized P/L|Premium Received/Paid|  Trans.No. |
settlement_trade_head5=_---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
settlement_trade_single_record1=_|%-8s|%-8s|%-18s|%-16s|%-5s|Ͷ          |%10.3f|%6d|%12.2f|%-18s|%10.2f|%12.2f|%21.2f|%-12s|
settlement_trade_end1=_---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
settlement_trade_end2=_|��%4d��|        |                  |                      |            |          |%6d|%12.2f|                  |%10.2f|%12.2f|%21.2f|            |
settlement_trade_end3=_---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
settlement_trade_end4=_��Դ����---INE  ������---SHFE   �н���---CFFEX  ������---DCE   ֣����---CZCE   ������---GFEX
settlement_trade_end5=_��---Buy   ��---Sell
settlement_trade_end6=_Ͷ---Speculation  ��---Hedge  ��---Arbitrage ��---General
settlement_trade_end7=_��---Open ƽ---Close ƽ��---Close Today ǿƽ---Forced Liquidation ƽ��---Close Prev. ǿ��---Forced Reduction ����ǿƽ---Local Forced Liquidation 
settlement_trade_end8=_
settlement_position_closed_head1=_                                                         ƽ����ϸ Position Closed 
settlement_position_closed_head2=_----------------------------------------------------------------------------------------------------------------------------------------------------------------------
settlement_position_closed_head3=_| ƽ������ | ������ |       Ʒ��       |      ��Լ      |�������� |��/��|   ����   |     ���ּ�    |     �����     |   �ɽ���   |  ƽ��ӯ��  |     Ȩ������֧      |
settlement_position_closed_head4=_|Close Date|Exchange|      Product     |   Instrument   |Open Date| B/S |   Lots   |Pos. Open Price|   Prev. Sttl   |Trans. Price|Realized P/L|Premium Received/Paid|
settlement_position_closed_head5=_----------------------------------------------------------------------------------------------------------------------------------------------------------------------
settlement_position_closed_single_record1=_|%-10s|%-8s|%-18s|%-16s|%-9s|%-5s|%10d|%15.3f|%16.3f|%12.3f|%12.2f|%21.2f|
settlement_position_closed_end1=_----------------------------------------------------------------------------------------------------------------------------------------------------------------------
settlement_position_closed_end2=_|��%6d��|        |                  |                |         |     |%10d|               |                |            |%12.2f|%21.2f|
settlement_position_closed_end3=_----------------------------------------------------------------------------------------------------------------------------------------------------------------------
settlement_position_closed_end4=_��Դ����---INE  ������---SHFE   �н���---CFFEX  ������---DCE   ֣����---CZCE   ������---GFEX
settlement_position_closed_end5=_��---Buy   ��---Sell 
settlement_position_closed_end6=_
settlement_position_detail_head1=_                                              �ֲ���ϸ Positions Detail
settlement_position_detail_head2=_-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
settlement_position_detail_head3=_| ������ |       Ʒ��       |      ��Լ      |�������� |   Ͷ/��    |��/��|�ֲ��� |    ���ּ�     |     �����     |     �����     |  ����ӯ��  |  ����ӯ�� |  ��֤��   |       ��Ȩ��ֵ       |
settlement_position_detail_head4=_|Exchange|     Product      |   Instrument   |Open Date|    S/H     | B/S |Positon|Pos. Open Price|   Prev. Sttl   |Settlement Price| Accum. P/L |  MTM P/L  |  Margin   | Market Value(Options)|
settlement_position_detail_head5=_-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
settlement_position_detail_single_record1=_|%-8s|%-18s|%-16s|%9s|Ͷ          |%-5s|%7d|%15.3f|%16.3f|%16.3f|%12.2f|%11.2f|%11.2f|                  0.00|
settlement_position_detail_end1=_-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
settlement_position_detail_end2=_|��%4d��|                  |                |         |            |     |%7d|               |                |                |%12.2f|%11.2f|%11.2f|                  0.00|
settlement_position_detail_end3=_-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
settlement_position_detail_end4=_��Դ����---INE  ������---SHFE   �н���---CFFEX  ������---DCE   ֣����---CZCE   ������---GFEX
settlement_position_detail_end5=_��---Buy   ��---Sell  
settlement_position_detail_end6=_Ͷ---Speculation  ��---Hedge  ��---Arbitrage ��---General
settlement_position_detail_end7=_
settlement_position_head1=_                                                         �ֲֻ��� Positions
settlement_position_head2=_------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
settlement_position_head3=_|       Ʒ��       |      ��Լ      |    ���     |    �����   |     ����     |    ������    |  �����  |  �����  |�ֲֶ���ӯ��|  ��֤��ռ��   |  Ͷ/��     |   ��ͷ��Ȩ��ֵ   |   ��ͷ��Ȩ��ֵ    |
settlement_position_head4=_|      Product     |   Instrument   |  Long Pos.  |Avg Buy Price|  Short Pos.  |Avg Sell Price|Prev. Sttl|Sttl Today|  MTM P/L   |Margin Occupied|    S/H     |Market Value(Long)|Market Value(Short)|
settlement_position_head5=_------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
settlement_position_single_record1=_|%-18s|%-16s|%13d|%13.3f|%14d|%14.3f|%10.3f|%10.3f|%12.2f|%15.2f|Ͷ          |              0.00|               0.00|
settlement_position_end1=_------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
settlement_position_end2=_|��%6d��        |                |%13d|             |%14d|              |          |          |%12.2f|%15.2f|            |              0.00|               0.00|
settlement_position_end3=_------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
settlement_position_end4=_
settlement_position_end5=_
settlement_position_end6=_
settlement_position_end7=_
settlement_position_end8=_)");


} // end namespace localCTP
