#ifndef _Processor_H_
#define _Processor_H_

#include <util/tc_singleton.h>
#include "login.pb.h"
#include "LoginProto.h"
#include <curl/curl.h>
#include <json/json.h>
#include "UserInfoProto.h"
#include "CommonStruct.pb.h"
//
using namespace tars;

/**
 *请求处理类
 *
 */
class Processor
{
public:
    Processor();
    ~Processor();

public:
    //
    int checkWhiteList(const long lPlayerID);
    //查询
    int SelectUserAccount(long uid, userinfo::GetUserResp &rsp);
    //查询
    int SelectUserInfo(long uid, userinfo::GetUserBasicResp &rsp);
    //更新用户第三方信息
    int UpdateUserThirdInfo(const userinfo::UpdateUserInfoReq &req, userinfo::UpdateUserInfoResp &rsp);
    //账号登录
    int UserLogin(const LoginProto::UserLoginReq &req, LoginProto::UserLoginResp &rsp, const map<string, string> &extraInfo);
    int UserLogin(long uid, const std::string& password, LoginProto::UserLoginResp &rsp, const map<string, string> &extraInfo);
    //登出
    int UserLogout(const LoginProto::LogoutReq &req, LoginProto::LogoutResp &rsp, bool sysOp = false, string ip = "");
    //游客登录
    int DeviceLogin(const LoginProto::DeviceLoginReq &req, LoginProto::DeviceLoginResp &rsp, const map<string, string> &extraInfo);
    //快速登录
    int QuickLogin(const LoginProto::QuickLoginReq &req, LoginProto::QuickLoginResp &rsp, const map<string, string> &extraInfo);
    //第三方登录
    int ThirdPartyLogin(const LoginProto::ThirdPartyLoginReq &req, LoginProto::ThirdPartyLoginResp &rsp, const map<string, string> &extraInfo);
    //账号注册处理
    int UserRegister(const LoginProto::RegisterReq req, LoginProto::RegisterResp &rsp, const string &ip);
    //账号注册处理
    int UserRegister2( const std::string& username, const LoginProto::RegisterReq req, LoginProto::RegisterResp &rsp, const map<std::string, std::string> &extraInfo, login::E_Register_Type userType);
    //账号注册处理
    int ThirdRegister(const LoginProto::RegisterReq req, LoginProto::RegisterResp &rsp, userinfo::UpdateUserInfoReq &userInfo, const int regType, const string &ip);
    //账号注册处理
    int UserRegister(const login::RegisterReq req, login::RegisterResp &rsp, int areaID, string ip);
    //手机号注册
    int PhoneRegister(const LoginProto::PhoneRegisterReq &req, LoginProto::PhoneRegisterResp &rsp, const map<std::string, std::string> &extraInfo);
    //手机号码登录
    int PhoneLogin(const LoginProto::PhoneLoginReq &req, LoginProto::PhoneLoginResp &rsp, const map<string, string> &extraInfo);
    //重置手机账号密码
    int PhoneResetPassword(const LoginProto::PhoneModifyPasswordReq &req, LoginProto::PhoneModifyPasswordResp &rsp);
    //发送手机验证码
    int PhoneMsgCode(const LoginProto::SendPhoneMessageCodeReq &req, LoginProto::SendPhoneMessageCodeResp &rsp);
    //邮箱注册
    int EmailRegister(const LoginProto::EmailRegisterReq &req, LoginProto::EmailRegisterResp &rsp, const map<std::string, std::string> &extraInfo);
    //邮箱登录
    int EmailLogin(const LoginProto::UserLoginReq &req, LoginProto::UserLoginResp &rsp, const map<string, string> &extraInfo, const int iVer);
    //发送邮箱验证码
    int EmailMsgCode(const LoginProto::SendEmailMessageCodeReq &req, LoginProto::SendEmailMessageCodeResp &rsp);
    //邮箱账号重置密码
    int EmailResetPassword(const LoginProto::EmailModifyPasswordReq &req, LoginProto::EmailModifyPasswordResp &rsp);
    //发送网关信息
    int UserRounter(const LoginProto::UserRounterInfoReq &req, LoginProto::UserRounterInfoResp &rsp);
    //绑定三方账号
    int BindThirdPartyAccount(const login::BindThirdPartyAccountReq &req, login::BindThirdPartyAccountResp &rsp);
    //
    long getAccountUid(const string username);

private:
    //产生uuid串
    string generateUUIDStr();
    //
    int httpGet(const char *url, std::string &resJson);
    //
    int httpPost(const char *url, const std::string &postParams, std::string &resJson);
    //
    int getUserInfoFromGoogle(const std::string &tokenid, const std::string &openid, userinfo::UpdateUserInfoReq &req);
    //
    int getUserInfoFromApple(const std::string &tokenid, userinfo::UpdateUserInfoReq &req);
    //
    int getUserInfoFromFacebook(const std::string &tokenid, userinfo::UpdateUserInfoReq &req);
    //
    int checkFacebookAuth(const std::string &input_token);
    //
    int sendAuthCode(const std::string &phone, const tars::Int32 &smsCode);
    //
    int setAuthData(const std::string &phone, const tars::Int32 &smsCode);
    //
    int getAuthData(const std::string &phone, std::string &ret);
    //
    int delAuthData(const std::string &phone);
    //
    int setUserPhonePassword(const std::string& username, const std::string& password);
    int setUserEmailPassword(const std::string& username, const std::string& password);
    int setUserPassword(long uid, const std::string& password);
    
    int VerifyCaptcha(const std::string& token);

public:
    //
    bool ConvertJwkToPem(const std::string &strnn, const std::string &stree, std::string &strPubKey);
};

//singleton
typedef TC_Singleton<Processor, CreateStatic, DefaultLifetime> ProcessorSingleton;

#endif
