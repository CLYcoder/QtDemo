#ifndef DATA_H
#define DATA_H

// 数据结构定义
#include "define.h"

#define g_dataBufferSize 100 //数据长度

class DATA
{
public:
    DATA(int type ,int length,char *data)
    {
        data = (char *)malloc((g_dataBufferSize<length?g_dataBufferSize:(length+10)));
        m_dataType = type;
        m_length = length;
        memcpy(m_data,data,length);
    }
    ~DATA(){
        if(m_data != NULL){
            free(m_data);
            m_data = NULL;
        }
    }

    char  *m_data;
    int   m_length;

    // 获取数据类型
    int dataType(){
        return m_dataType;
    }
    // 设置数据
    void setData(int type,int length,char *data){
        m_dataType = type;
        m_length = length;
        if(length > g_dataBufferSize){
            free(m_data);
            m_data = (char *)malloc(length + 10);
        }else{
            int len = sizeof(m_data);
            memset(m_data,0,len);
        }
        memcpy(m_data,data,length);
    }
    // 获取数据内容
    int getData(char* tmp){
        int ret = 0;
        int len = sizeof(tmp);
        if(len < m_length)
            ret = -1;

        memcpy(tmp,m_data,m_length);
        return ret;
    }

    virtual void handleData() = 0;  // 处理数据的接口
#if 0
    char * data(){
        char tmp[m_length] = {0};
        memcpy();
    }
#endif
private:
    int   m_dataType;  // 数据类型 -- 报文类型
    bool  m_dataValid;  // 数据是否有效

};


#endif // DATA_H
