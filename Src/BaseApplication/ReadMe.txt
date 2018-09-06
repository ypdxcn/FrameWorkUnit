========================================================================
    控制台应用程序：BaseApplication 项目概述
========================================================================

应用程序向导已为您创建了此 BaseApplication 应用程序。

本文件概要介绍组成 BaseApplication 应用程序的每个文件的内容。


BaseApplication.vcxproj
    这是使用应用程序向导生成的 VC++ 项目的主项目文件，其中包含生成该文件的 Visual C++ 的版本信息，以及有关使用应用程序向导选择的平台、配置和项目功能的信息。

BaseApplication.vcxproj.filters
    这是使用“应用程序向导”生成的 VC++ 项目筛选器文件。它包含有关项目文件与筛选器之间的关联信息。在 IDE 中，通过这种关联，在特定节点下以分组形式显示具有相似扩展名的文件。例如，“.cpp”文件与“源文件”筛选器关联。

BaseApplication.cpp
    这是主应用程序源文件。

/////////////////////////////////////////////////////////////////////////////
其他标准文件:

StdAfx.h, StdAfx.cpp
    这些文件用于生成名为 BaseApplication.pch 的预编译头 (PCH) 文件和名为 StdAfx.obj 的预编译类型文件。

/////////////////////////////////////////////////////////////////////////////
其他注释:

应用程序向导使用“TODO:”注释来指示应添加或自定义的源代码部分。

/////////////////////////////////////////////////////////////////////////////
1.mongoose   webserver 支持 https的步骤
1. 创建证书
openssl genrsa -out privatekey.pem 1024
openssl req -new -x509 -key privatekey.pem -out publickey.cer -days 1825

2.拷贝privatekey.pem和publickey.cer的内容到同一个文件，并命名为key.pem
3. 在mongoose.c的顶部定义#define MONGOOSE_USE_SSL
4. 设置监听port和pem的路径
static std::string s_port = "8008r,443s";
static std::string ssl_cert_path = "/Volumes/SD/key.pem";

mg_set_option(server[i], "listening_port", s_port.c_str());
mg_set_option(server[i], "ssl_certificate", ssl_cert_path.c_str());