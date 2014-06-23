// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef STRICT
#define STRICT
#endif

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#define _ATL_APARTMENT_THREADED
#define _ATL_NO_AUTOMATIC_NAMESPACE

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit

#include "resource.h"
#include <atlbase.h>
#include <atlcom.h>
#include <atlctl.h>

using namespace ATL;

#import <AmsLog.dll> no_namespace raw_interfaces_only
#define AMSLOG_SEVERITY_INFO 0
#define AMSLOG_SEVERITY_WARNING 1
#define AMSLOG_SEVERITY_ERROR 2
#define AMSLOG_SEVERITY_CRITICAL 3

#import <msxml4.dll> 
#define DOM_CLSID	__uuidof(MSXML2::DOMDocument40)
