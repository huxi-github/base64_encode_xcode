//
//  main.cpp
//  memalloc_out
//
//  Created by 胡喜 on 2018/9/10.
//  Copyright © 2018年 胡喜. All rights reserved.
//

#include <iostream>
#include "common.h"
#include "base_64.h"
using namespace std;

bool ContentDoBase64(SAM_CHAR_PTR ptextin,int lenin, SAM_CHAR_PTR ptextOut,int* strOUTlenout);
char * memcpy_s(char *dest, const char *src, size_t count);
void * memcpy_2(void *dest, const void *src, unsigned int count);
char  *memcpy_s2(char *dest, const char *src, size_t count);
void  *memcpy_s2(void *dest, const char *src, unsigned int count);
void  *memcpy_s2(void *dest, const void *src, unsigned int count);


int main(int argc, const char * argv[]) {
 
    SAM_CHAR_PTR testStr=(SAM_CHAR_PTR)"Hello, World!\n";

    int inLen=sizeof(testStr);
    
    SAM_CHAR_PTR pstrOUT=new char[50]; //(SAM_CHAR_PTR)"Hello, World!\n";   //用于接收的char * 必须事先在 堆里面 malloc 了 //直接赋值“helloworld”,让指针指向了常量区
    
    memset(pstrOUT, 0, 50);
    
    int outLen=0;
    
    ContentDoBase64(testStr, inLen, pstrOUT, &outLen);
    
    
    cout<<"base64 out is:"<<pstrOUT<<"  length is:"<<outLen <<endl;
    
    return 0;
}

bool ContentDoBase64(SAM_CHAR_PTR ptextin,int lenin , SAM_CHAR_PTR ptextOut,int * plenout){
 
   Base64 converter ;
    
   const unsigned  char * ptin =(const unsigned  char *)ptextin;
    
   std::string baseResult=converter.Encode(ptin, lenin);
    
   char * ptextOutTemp =(SAM_CHAR_PTR)baseResult.c_str();
    
//  int len=sizeof(baseResult); ==4 (const)
    
    long len2= baseResult.length();
    
    //   memcpy(ptextOut, ptextOutTemp,len2);
 
    memcpy_s(ptextOut, ptextOutTemp,len2);  //【why not??】
    
    *plenout=sizeof(ptextOut);   //problem [2]
    
    *plenout=sizeof(*ptextOut);  //problem [3]
    
    *plenout=(int)len2;          //problem [yes]

    return true;
}




char *memcpy_s(char *dest, const char *src, size_t count)
{

    if (NULL == dest || NULL == src || count <= 0)

        return NULL;
    
    char *address = dest;

    while (count--){
        
        char ct=*src++;
        
        * dest++=ct;   //message sent to dealloced object
        
    }

    return address;

}

void  *memcpy_s2(void *dest, const void *src, unsigned int count)
{
    
    if (NULL == dest || NULL == src || count <= 0)
        
        return NULL;
    
    while (count--){
        
       *(char *) dest = *(char *) src;
        
        dest = (char *) dest + 1;
        src = (char *) src + 1;
        
    }

    return dest; //逻辑有问题
}

void *memcpy_2(void *dest, const void *src, unsigned int count) //系统memcpy 的源码
{
    assert((dest != NULL) && (src != NULL));
    void *address = dest;
    while (count --)
    {
        *(char *) dest = *(char *) src;
        dest = (char *) dest + 1;
        src = (char *) src + 1;
    }
    return address;
}


