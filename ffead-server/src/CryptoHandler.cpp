/*
 * CryptoHandler.cpp
 *
 *  Created on: Nov 24, 2010
 *      Author: sumeet
 */

#include "CryptoHandler.h"
#include "iostream"
CryptoHandler::CryptoHandler() {
	// TODO Auto-generated constructor stub

}

CryptoHandler::~CryptoHandler() {
	// TODO Auto-generated destructor stub
}

char* CryptoHandler::base64decode(unsigned char *input, int length)
{
	BIO *b64, *bmem;

	char *buffer = (char *)malloc(length);
	memset(buffer, 0, length);

	b64 = BIO_new(BIO_f_base64());
	bmem = BIO_new_mem_buf(input, length);
	bmem = BIO_push(b64, bmem);

	BIO_read(bmem, buffer, length);

	BIO_free_all(bmem);

	return buffer;
}

char* CryptoHandler::base64encode(const unsigned char *input, int length)
{
	BIO *bmem, *b64;
	BUF_MEM *bptr;

	b64 = BIO_new(BIO_f_base64());
	bmem = BIO_new(BIO_s_mem());
	b64 = BIO_push(b64, bmem);
	BIO_write(b64, input, length);
	BIO_flush(b64);
	BIO_get_mem_ptr(b64, &bptr);

	char *buff = (char *)malloc(bptr->length);
	memcpy(buff, bptr->data, bptr->length-1);
	buff[bptr->length-1] = 0;

	BIO_free_all(b64);

	return buff;
}

char* CryptoHandler::hmac_sha1(char* datain,char* keyin,bool base64)
{
	unsigned char* key = (unsigned char*) keyin;
	unsigned char* data = (unsigned char*) datain;
	unsigned char* result,*result1;
	unsigned int result_len = 20,result1_len;

	HMAC_CTX ctx;
	result = (unsigned char*) malloc(sizeof(char) * result_len);

	ENGINE_load_builtin_engines();
	ENGINE_register_all_complete();

	HMAC_CTX_init(&ctx);
	HMAC_Init_ex(&ctx, key, strlen(keyin), EVP_sha1(), NULL);
	HMAC_Update(&ctx, data, strlen(datain));
	HMAC_Final(&ctx, result, &result_len);
	HMAC_CTX_cleanup(&ctx);

	//HMAC(EVP_sha1(),key,strlen(keyin),data,strlen(datain),result,&result_len);
	if(base64)
		return base64encode(result,result_len);
	return (char*)result;
}

char* CryptoHandler::hmac_sha256(char* datain,char* keyin,bool base64)
{
	unsigned char* key = (unsigned char*) keyin;
	unsigned char* data = (unsigned char*) datain;
	unsigned char* result;
	unsigned int result_len = 32;

	HMAC_CTX ctx;
	result = (unsigned char*) malloc(sizeof(char) * result_len);

	ENGINE_load_builtin_engines();
	ENGINE_register_all_complete();

	HMAC_CTX_init(&ctx);
	HMAC_Init_ex(&ctx, key, strlen(keyin), EVP_sha256(), NULL);
	HMAC_Update(&ctx, data, strlen(datain));
	HMAC_Final(&ctx, result, &result_len);
	HMAC_CTX_cleanup(&ctx);

	if(base64)
		return base64encode(result,result_len);
	return (char*)result;
}

char* CryptoHandler::hmac_sha384(char* datain,char* keyin,bool base64)
{
	unsigned char* key = (unsigned char*) keyin;
	unsigned char* data = (unsigned char*) datain;
	unsigned char* result;
	unsigned int result_len = 48;

	HMAC_CTX ctx;
	result = (unsigned char*) malloc(sizeof(char) * result_len);

	ENGINE_load_builtin_engines();
	ENGINE_register_all_complete();

	HMAC_CTX_init(&ctx);
	HMAC_Init_ex(&ctx, key, strlen(keyin), EVP_sha384(), NULL);
	HMAC_Update(&ctx, data, strlen(datain));
	HMAC_Final(&ctx, result, &result_len);
	HMAC_CTX_cleanup(&ctx);

	if(base64)
		return base64encode(result,result_len);
	return (char*)result;
}

char* CryptoHandler::hmac_sha512(char* datain,char* keyin,bool base64)
{
	unsigned char* key = (unsigned char*) keyin;
	unsigned char* data = (unsigned char*) datain;
	unsigned char* result;
	unsigned int result_len = 64;

	HMAC_CTX ctx;
	result = (unsigned char*) malloc(sizeof(char) * result_len);

	ENGINE_load_builtin_engines();
	ENGINE_register_all_complete();

	HMAC_CTX_init(&ctx);
	HMAC_Init_ex(&ctx, key, strlen(keyin), EVP_sha512(), NULL);
	HMAC_Update(&ctx, data, strlen(datain));
	HMAC_Final(&ctx, result, &result_len);
	HMAC_CTX_cleanup(&ctx);

	if(base64)
		return base64encode(result,result_len);
	return (char*)result;
}


string CryptoHandler::urlDecode(string str)
{
	string strret = str;
	boost::replace_all(strret,"%25","%");
	boost::replace_all(strret,"%3D","=");
	boost::replace_all(strret,"%3A",":");
	boost::replace_all(strret,"%20"," ");
	boost::replace_all(strret,"%5E","^");
	boost::replace_all(strret,"%26","&");
	boost::replace_all(strret,"%60","`");
	boost::replace_all(strret,"%7B","{");
	boost::replace_all(strret,"%7D","}");
	boost::replace_all(strret,"%7C","|");
	boost::replace_all(strret,"%5D","]");
	boost::replace_all(strret,"%5B","[");
	boost::replace_all(strret,"%22","\"");
	boost::replace_all(strret,"%3C","<");
	boost::replace_all(strret,"%3E",">");
	boost::replace_all(strret,"%5C","\\");
	boost::replace_all(strret,"%23","#");
	boost::replace_all(strret,"%3F","?");
	boost::replace_all(strret,"%2F","/");
	return strret;
}

string CryptoHandler::urlEncode(string str)
{
	string strret;
	int len = str.length();
	for(int i=0; i<len; i++)
	{
		switch(str[i])
		{
		case '%':
			strret.append("%25");
			break;
		case '=':
			strret.append("%3D");
			break;
		case ':':
			strret.append("%3A");
			break;
		case ' ':
			strret.append("%20");
			break;
		case '^':
			strret.append("%5E");
			break;
		case '&':
			strret.append("%26");
			break;
		case '`':
			strret.append("%60");
			break;
		case '{':
			strret.append("%7B");
			break;
		case '}':
			strret.append("%7D");
			break;
		case '|':
			strret.append("%7C");
			break;
		case ']':
			strret.append("%5D");
			break;
		case '[':
			strret.append("%5B");
			break;
		case '"':
			strret.append("%22");
			break;
		case '<':
			strret.append("%3C");
			break;
		case '>':
			strret.append("%3E");
			break;
		case '\\':
			strret.append("%5C");
			break;
		case '#':
			strret.append("%23");
			break;
		case '?':
			strret.append("%3F");
			break;
		case '/':
			strret.append("%2F");
			break;
		default:
			strret.push_back(str[i]);
			break;
		}
	}
	return strret;
}
