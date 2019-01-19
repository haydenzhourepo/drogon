/**
 *
 *  HttpRequest.h
 *  An Tao
 *
 *  Copyright 2018, An Tao.  All rights reserved.
 *  https://github.com/an-tao/drogon
 *  Use of this source code is governed by a MIT license
 *  that can be found in the License file.
 *
 *  Drogon
 *
 */

#pragma once

#include <drogon/Session.h>
#include <trantor/net/InetAddress.h>
#include <trantor/utils/Date.h>
#include <json/json.h>
#include <unordered_map>
#include <string>
#include <memory>
namespace drogon
{
class HttpRequest;
typedef std::shared_ptr<HttpRequest> HttpRequestPtr;
enum HttpMethod
{
    Get = 0,
    Post,
    Head,
    Put,
    Delete,
    Invalid
};

/// Abstract class for webapp developer to get or set the Http request;
class HttpRequest
{
  public:
    enum Version
    {
        kUnknown = 0,
        kHttp10 = 1,
        kHttp11 = 2
    };
    /// Returns the method string of the request, such as GET, POST, etc.
    virtual const char *methodString() const = 0;

    /// Return the enum type method of the request.
    virtual HttpMethod method() const = 0;

    /// Get the header string identified by the @param field
    virtual const std::string &getHeader(const std::string &field, const std::string &defaultVal = std::string()) const = 0;
    virtual const std::string &getHeader(std::string &&field, const std::string &defaultVal = std::string()) const = 0;

    /// Set the header string identified by the @param field
    virtual void addHeader(const std::string &field, const std::string &value) = 0;

    /// Get the cookie string identified by the @param field
    virtual const std::string &getCookie(const std::string &field, const std::string &defaultVal = std::string()) const = 0;

    /// Get all headers of the request
    virtual const std::unordered_map<std::string, std::string> &headers() const = 0;

    /// Get all cookies of the request
    virtual const std::unordered_map<std::string, std::string> &cookies() const = 0;

    /// Get the query string of the request.
    /**
     * If the http method is GET, the query string is the substring after the '?' in the URL string.
     * If the http method is POST, the query string is the content string of the HTTP request. 
     */
    virtual const std::string &query() const = 0;

    /// Get the path of the request.
    virtual const std::string &path() const = 0;

    /// Return the enum type version of the request.
    /**
     * kHttp10 means Http version is 1.0
     * kHttp11 means Http verison is 1.1
     */
    virtual Version getVersion() const = 0;

    /// Get the session to which the request belongs.
    virtual SessionPtr session() const = 0;

    /// Get parameters of the request.
    virtual const std::unordered_map<std::string, std::string> &getParameters() const = 0;

    /// Return the remote IP address and port
    virtual const trantor::InetAddress &peerAddr() const = 0;

    /// Return the local IP address and port
    virtual const trantor::InetAddress &localAddr() const = 0;

    /// Returns the receive timestamp set by the framework.
    virtual const trantor::Date &receiveDate() const = 0;

    /// Get the Json object of the request
    virtual const std::shared_ptr<Json::Value> getJsonObject() const = 0;

    /// Set the Http method
    virtual void setMethod(const HttpMethod method) = 0;

    /// Set the path of the request
    virtual void setPath(const std::string &path) = 0;

    /// Set the parameter of the request
    virtual void setParameter(const std::string &key, const std::string &value) = 0;

    /// Create a request object.
    static HttpRequestPtr newHttpRequest();

    virtual ~HttpRequest() {}
};

} // namespace drogon
